
/*
* 这是我们实现的简单版jpeg压缩和解压缩函数，这里使用其中的部分功能实现dct系数的获取
*/


#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<time.h>
using namespace std;
unsigned char TMPBUF[256];
unsigned char *buffer,*r,*g,*b;
unsigned char *y,*u,*v;
char *finy,*finu,*finv;
char *cy,*cu,*cv;
double res[8][8],res2[8][8];
unsigned char weneed[100];
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
        void Compress(char * filename,char *argv[])
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
            y=(unsigned char *)(malloc(relwidth * relheight));
            u=(unsigned char *)(malloc(relwidth * relheight));
            v=(unsigned char *)(malloc(relwidth * relheight));

            fclose(fp_bitmap);
            //获得y,u,v
            for(int i=0;i<height;i++)
            {
                for(int j=0;j<width;j++)
                {
                    y[(height-i-1)*relwidth+j]=(r[i*width+j]*0.299+g[i*width+j]*0.587+b[i*width+j]*0.114);
                    u[(height-i-1)*relwidth+j]=(r[i*width+j]*(-0.1687)+g[i*width+j]*(-0.3313)+b[i*width+j]*0.5+128);
                    v[(height-i-1)*relwidth+j]=(r[i*width+j]*0.5+g[i*width+j]*(-0.4187)+b[i*width+j]*(-0.0813)+128);
                }
                for(int j=width;j<relwidth;j++)
                {
                    y[(height-i-1)*relwidth+j]=0;
                    u[(height-i-1)*relwidth+j]=128;
                    v[(height-i-1)*relwidth+j]=128;
                }
            }
            for(int i=height;i<relheight;i++)
            {
                for(int j=0;j<relwidth;j++)
                {
                    y[i*relwidth+j]=0;
                    u[i*relwidth+j]=128;
                    v[i*relwidth+j]=128;
                }
            }
            free(r); //释放内存
            free(g);
            free(b);
            finy=(char *)(malloc(relwidth * relheight));
            finu=(char *)(malloc(relwidth * relheight));
            finv=(char *)(malloc(relwidth * relheight));
            int cnt=-1;
            // cout<<relwidth<<" "<<relheight<<" \n";
            // cout<<relwidth-16<<" "<<relheight-16<<"\n";
            freopen(argv[2],"w",stdout);
            cout<<(relheight-16)/8<<" "<<(relwidth-16)/8<<"\n";
            for(int s=0;s<relheight-16;s+=8)
            {
                for(int t=0;t<relwidth-16;t+=8)
                {
                    
                    for(int i=0;i<8;i++)//离散余弦变化，矩阵乘法
                    {
                        for(int j=0;j<8;j++)
                        {
                            res[i][j]=0;
                            for(int k=0;k<8;k++)
                            {
                                res[i][j]+=dctA[i][k]*y[(s+k)*relwidth+t+j];
                                // cout<<res[i][j]<<" ";
                            }
                            // cout<<"\n";
                        }
                    }
                    for(int i=0;i<8;i++)//离散余弦变化2
                    {
                        for(int j=0;j<8;j++)
                        {
                            res2[i][j]=0;
                            for(int k=0;k<8;k++)
                            {
                                res2[i][j]+=res[i][k]*dctA[j][k];//省掉了矩阵转置操作
                            }
                        }
                    }
                    for(int i=0;i<8;i++)//量化
                    {
                        for(int j=0;j<8;j++)
                        {
                            // finy[++cnt]=res2[i][j]/lq[i][j]+0.5;
                            int l1=zig[i][j]/8,l2=zig[i][j]%8;
                            // cout<<res2[l1][l2]/lq[l1][l2]+0.5<<" ";
                            finy[++cnt]=res2[l1][l2]/lq[l1][l2];
                            // cout<<cnt<<" "<<finy[cnt]<<endl;
                            // res2[l1][l2]/=lq[l1][l2];
                        }
                    }
                    for(int k=1;k<10;k++)
                    {
                        // for(int j=0;j<8;j++)
                        // {
                            // cout<<res[i][j]<<" ";
                            cout<<(short int)finy[cnt-63+k]<<" ";
                        // }
                        // cout<<"\n";
                    }
                    int num=0;
                    // for(int k=0;k<8;k++)
                    // {
                    //     for(int j=0;j<8;j++)
                    //     {
                    //         num++;
                    //         if(num>=2&&num<=10)
                    //         // cout<<res[i][j]<<" ";
                    //             cout<<(short int)res2[k][j]<<" ";
                            
                    //     }
                    //     // cout<<"\n";
                    // }
                    // cout<<t<<endl;
                    cout<<"\n";
                }
                // cout<<s;
            }
            fclose(stdout);
            exit(0);
            
            
        }

        
};

int main(int argc,char* argv[])
{
    clock_t  clockBegin, clockEnd;
    clockBegin = clock();
    char bmp_filename[100]="./control_toolkit/antijpeg/bmp/frames_0000000001.bmp";
    char gpj_filename[100]="c.gpj";
    jpeg a=jpeg();//初始化
    a.Compress(argv[1],argv);//压缩bmp
    // a.writeinto(gpj_filename);//将压缩信息写入gpj
    free(cy);
    free(cu);
    free(cv);
    free(buffer);
    free(finu);
    free(finv);
    free(finy);
    // a.Decompress(gpj_filename);//解压缩，并写入result.bmp文件
    clockEnd = clock();
    printf("tim->%dms",clockEnd-clockBegin);
}
