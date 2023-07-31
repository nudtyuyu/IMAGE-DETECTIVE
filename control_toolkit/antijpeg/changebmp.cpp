/**************************************************
* File name: changebmp.cpp
* Author: Banish(李剑锋)
* Author's blog: 
* Date: Aug 20th, 2022
*
*描述：这是我们实现的jpeg压缩和解压缩的简单版，这里用其中部分功能来标记检测出的篡改区域
**************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<time.h>
#define len_line 8
using namespace std;
unsigned char TMPBUF[256];
unsigned char *buffer,*r,*g,*b;
unsigned char *y,*u,*v;
char *finy,*finu,*finv;
char *cy,*cu,*cv;
double res[8][8],res2[8][8];
unsigned char weneed[100];
int num_col,num_row,ss;
class jpeg
{
    private:
        //用于dct变换的矩阵
        double dctA[8][8];
        int cnty,cntu,cntv;
        //亮度量化矩阵
        unsigned short int lq[8][8]={
            {16, 11, 10, 16, 24, 40, 51, 61},
            {12, 12, 14, 19, 26, 58, 60, 55},
            {14, 13, 16, 24, 40, 57, 69, 56},
            {14, 17, 22, 29, 51, 87, 80, 62},
            {18, 22, 37, 56, 68, 109, 103, 77},
            {24, 35, 55, 64, 81, 104, 113, 92},
            {49, 64, 78, 87, 103, 121, 120, 101},
            {72, 92, 95, 98, 112, 100, 103, 99}
        };

        //色度量化矩阵
        unsigned short int cq[8][8]={
            {17, 18, 24, 47, 99, 99, 99, 99},
            {18, 21, 26, 66, 99, 99, 99, 99},
            {24, 26, 56, 99, 99, 99, 99, 99},
            {47, 66, 99, 99, 99, 99, 99, 99},
            {99, 99, 99, 99, 99, 99, 99, 99},
            {99, 99, 99, 99, 99, 99, 99, 99},
            {99, 99, 99, 99, 99, 99, 99, 99},
            {99, 99, 99, 99, 99, 99, 99, 99}
        };
        //标记矩阵类型
        unsigned short int lt=0,ct=1;
        //zig编码表
        unsigned short int zig[8][8]={
            {0, 1, 8, 16, 9, 2, 3, 10},
            {17, 24, 32, 25, 18, 11, 4, 5},
            {12, 19, 26, 33, 40, 48, 41, 34},
            {27, 20, 13, 6, 7, 14, 21, 28,},
            {35, 42, 49, 56, 57, 50, 43, 36},
            {29, 22, 15, 23, 30, 37, 44, 51},
            {58, 59, 52, 45, 38, 31, 39, 46},
            {53, 60, 61, 54, 47, 55, 62, 63}
        };
        unsigned short int zag[8][8]={
            {0, 1, 5, 6, 14, 15, 27, 28},
            {2, 4, 7, 13, 16, 26, 29, 42},
            {3, 8, 12, 17, 25, 30, 41, 43},
            {9, 11, 18, 24, 31, 40, 44, 53},
            {10, 19, 23, 32, 39, 45, 52, 54},
            {20, 22, 33, 38, 46, 41, 55, 60},
            {21, 34, 37, 47, 50, 56, 59, 61},
            {35, 36, 48, 49, 57, 58, 62, 63}
        };
        unsigned short int width,height,relwidth,relheight;
    public:
        jpeg()
        {
            //初始化DCT变换的A矩阵
            // for(int i=0;i<8;i++)
            // {
            //     // for(int j=0;j<8;j++)
            //     // lq[i][j]=min((i+1)*20,(j+1)*20);
            //     // lq[i][j]=min();
            //     for(int j=0;j<8;j++)
            //     cq[i][j]=j+15;
            //     // cq[i][j]=min((i+1)*20,(j+1)*20);
            // }
            for(int i=0;i<8;i++)
            {
                double c=i?0.5:sqrt(0.125);
                for(int j=0;j<8;j++)
                {
                    dctA[i][j]=c*cos(M_PI *i*(2*j+1)/(2*8));
                    // printf("%lf ",dctA[i][j]);
                }
            }
        }
        void Compress(char * filename)
        {
            //根据路径读取图片，并存储为RGB矩阵
            FILE *fp_bitmap = fopen(filename, "rb");					//打开bmp文件
	        // cout<<filename;
			fread(TMPBUF, 1, 54, fp_bitmap);							//读入位图的bmp文件头(bmp file header)、位图信息头(bitmap information)
	        for(int i=0;i<54;i++)
            {
                weneed[i]=TMPBUF[i];
            }
            width = (unsigned short int)TMPBUF[19] * 256 + TMPBUF[18];	//获得图像的宽度
	        height = (unsigned short int)TMPBUF[23] * 256 + TMPBUF[22];	//获得图像的高度
            unsigned short int w=(TMPBUF[29] * 256 + TMPBUF[28]);       //获得图像的位图信息
            // cout<<width<<" "<<height<<" "<<w<<"\n";
            if(w!=24&&w!=32)                                            //如果不是24位或32位图就退出
            {
                printf("terrible!");
                exit(0);
            }
            //位图数据在文件中的排列顺序是从左下角到右上角，以行为主序排列的。
            r=(unsigned char *)(malloc(width * height));
            g=(unsigned char *)(malloc(width * height));
            b=(unsigned char *)(malloc(width * height));
            // cout<<"ss";
            //读出r,g,b信息
            if(w/8==4)
            {
                buffer = (unsigned char *)(malloc(4 * width * height));
                fread(buffer,1,w/8*width*height,fp_bitmap);
                for(int i=0;i<height;i++)
                {
                    for(int j=0;j<width;j++)
                    {
                        b[i*width+j]=buffer[i*width*4+j*4];
                        g[i*width+j]=buffer[i*width*4+j*4+1];
                        r[i*width+j]=buffer[i*width*4+j*4+2];
                    }
                }

            }
            else
            {
                int ww=(3*width+3)/4*4,twidth=ww-3*width;//用来解决24位bmp的对齐规则
                buffer = (unsigned char *)(malloc(ww*height));
                fread(buffer,1,ww*height,fp_bitmap);
                for(int i=0;i<height;i++)
                {
                    for(int j=0;j<width;j++)
                    {
                        b[i*width+j]=buffer[i*ww+j*3];
                        g[i*width+j]=buffer[i*ww+j*3+1];
                        r[i*width+j]=buffer[i*ww+j*3+2];
                    }
                }
            }
            relwidth=(width+15)/16*16;
            relheight=(height+15)/16*16;
            fclose(fp_bitmap);
            //change
            freopen("./control_toolkit/antijpeg/change.txt","r",stdin);
            int x;
	    int flag=0;
            scanf("%d%d%d",&ss,&num_row,&num_col);
            for(int i=0;i<num_row;i++)
            {
                for(int j=0;j<num_col;j++)
                {
                    scanf("%d",&x);
		 
                    if(x==1)
                    {
			flag=1;
                        int start_row=height-i*ss*8,end_row=height-(i+1)*ss*8;
                        int start_col=j*ss*8,end_col=start_col+ss*8;
                        //cout<<start_row<<" "<<end_row<<" "<<start_col<<" "<<end_col<<endl;
			if(num_col==1)
				start_col=0,end_col=width;
			if(num_row==1)
				start_row=height,end_row=0;
			if(j==num_col-1)
                            end_col=width;
                        if(i==num_row-1)
                            end_row=0;
                        for(int ii=start_row-1;ii>=start_row-len_line;ii--)
			{   for(int jj=start_col;jj<end_col;jj++)
				r[ii*width+jj]=255,g[ii*width+jj]=b[ii*width+jj]=0;
			}
			for(int ii=end_row;ii<end_row+len_line;ii++)
			{
			    for(int jj=start_col;jj<end_col;jj++)
				r[ii*width+jj]=255,g[ii*width+jj]=b[ii*width+jj]=0;
			}
			for(int jj=start_col;jj<start_col+len_line;jj++)
			{
			   for(int ii=start_row-1;ii>=end_row;ii--)
				r[ii*width+jj]=255,g[ii*width+jj]=b[ii*width+jj]=0;
			}
			for(int jj=end_col-1;jj>=end_col-len_line;jj--)
			{
			   for(int ii=start_row-1;ii>=end_row;ii--)
				r[ii*width+jj]=255,g[ii*width+jj]=b[ii*width+jj]=0;
			}
		    }
                }
            }
            fclose(stdin);
            printf("%d\n",flag);
            
        }
        void writebmp(char *filename)
        {
            char x=0;
            FILE *fp_bitmap = fopen(filename, "wb");
            weneed[28]=24;
            for(int i=0;i<54;i++)
                fwrite(weneed+i,1,1,fp_bitmap);
            unsigned char s=0;
            for(int i=0;i<height;i++)
            {
                for(int j=0;j<width;j++)
                {
                    // fwrite(&s,1,1,fp_bitmap);
                    fwrite(b+i*width+j,1,1,fp_bitmap);
                    // fwrite(&s,1,1,fp_bitmap);
                    fwrite(g+i*width+j,1,1,fp_bitmap);
                    // fwrite(&s,1,1,fp_bitmap);
                    fwrite(r+i*width+j,1,1,fp_bitmap);
                    
                    
                }
                for(int j=0;j<(4-(3*width%4))%4;j++)
                {
                    fwrite(&x,1,1,fp_bitmap);
                    // fwrite(&x,1,1,fp_bitmap);
                    // fwrite(&x,1,1,fp_bitmap);
                }
            }
            fclose(fp_bitmap);    
            free(r);free(g);free(b);
        }
        
};
int main()
{
    clock_t  clockBegin, clockEnd;
    clockBegin = clock();
    char bmp_filename[100]="./antiedit/from/display.bmp";
    char bmp2_filename[100]="./antiedit/result/result.bmp";
    jpeg a=jpeg();//初始化
    a.Compress(bmp_filename);//压缩bmp
    a.writebmp(bmp2_filename);
    // a.writeinto(gpj_filename);//将压缩信息写入gpj
    // a.Decompress(gpj_filename);//解压缩，并写入result.bmp文件
    clockEnd = clock();
    printf("tim->%dms\n",clockEnd-clockBegin);
}
