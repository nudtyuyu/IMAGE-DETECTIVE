
/**************************************************
* File name: dark0.cpp
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 
* 描述：本文件依据论文，实现邻域信息综合法的低照度图像处理
**************************************************/




#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>

using namespace cv;
using namespace std;

#define BLUE 0
#define GREEN 1
#define RED 2

void DealDark(char filename[],char path[]);


void DealDark(char filename[],char path[])
{
        /*将图像转为灰度图，并进行标准化和线性变换*/
       	Mat src = imread(filename,CV_LOAD_IMAGE_COLOR);
	Mat src64_color;
        Mat normalized,gray0,gray1;
        Mat src_g,src64;
	src.convertTo(src64_color,CV_64FC3,1.0);
       	cvtColor(src,src_g,COLOR_BGR2GRAY);
	
	src_g.convertTo(src64,CV_64FC1,1.0/255);
       	//normalize(src_g,normalized,255,0,NORM_MINMAX);
        src_g.convertTo(gray0,CV_64FC1,1.0/255);
        src_g.convertTo(gray1,CV_64FC1,1.0/255);
        double*pGray1 = (double*)gray1.data;
        double*pGray0 = (double*)gray0.data;
        int size = gray0.rows*gray0.cols;
        for(int i =0;i<size;pGray0++,i++)
        {
                double I = *pGray0;
                double In = (pow(I,0.24)+(1-I)*1/2+I*I)/2;
                *pGray1= In;
                pGray1++;
        }
        double sigma = 5;
        Mat gauss1;
        uint8_t window_1 = (uint8_t(3*sigma)*2+1);
        //Mat G1 = getGaussianKernel(window_1,sigma,CV_64F);
	//filter2D(src64,gauss1,CV_64F,G1);


        /*进行Gaussian滤波，以不同的高斯核*/
        GaussianBlur(gray0,gauss1,Size(window_1,window_1),sigma,sigma);
        Mat r1(src64.rows,src64.cols,CV_64F);
        Mat R1(src64.rows,src64.cols,CV_64F);
        double*pGauss1 = (double*)gauss1.data;
        double*pr1 = (double*)r1.data;
	double*p64 = (double*)src64.data;
        pGray0 = (double*)gray0.data;
        for(int i =0;i<size;pr1++,pGauss1++,pGray0++,i++)
        {
                *pr1 = ((*pGauss1)/(*pGray0));
        }
        pr1 = (double*)r1.data;
        double*pR1 = (double*)R1.data;
        pGray1 = (double*)gray1.data;
        for(int i =0;i<size;pr1++,pGray1++,pR1++,i++)
        {
                *pR1 = (pow(*pGray1,*pr1));
        }

        double sigma2 = 20;
        Mat gauss2;
        uint8_t window_2 = (uint8_t(3*sigma2)*2+1);
        //Mat G2 = getGaussianKernel(window_2,sigma2,CV_64F);
	GaussianBlur(gray0,gauss2,Size(window_2,window_2),sigma2,sigma2);
        //GaussianBlur(src64,gauss2,Size(window_2,window_2),0,0);
	//filter2D(src64,gauss2,CV_64F,G2);
        Mat r2(src64.rows,src64.cols,CV_64F);
        Mat R2(src64.rows,src64.cols,CV_64F);
        double*pGauss2 = (double*)gauss2.data;
        double*pr2 = (double*)r2.data;
	p64 = (double*)src64.data;
        pGray0 = (double*)gray0.data;
        for(int i =0;i<size;pr2++,pGauss2++,pGray0++,i++)
        {
                *pr2 = ((*pGauss2)/(*pGray0));
        }
        pr2 = (double*)r2.data;
        double*pR2 = (double*)R2.data;
        pGray1 = (double*)gray1.data;
        for(int i =0;i<size;pr2++,pGray1++,pR2++,i++)
        {
                *pR2 = (pow(*pGray1,*pr2));
        }

        double sigma3 = 240;
        Mat gauss3;
        uint8_t window_3 = (uint8_t(3*sigma3)*2+1);
        //Mat G3 = getGaussianKernel(window_3,sigma3,CV_64F);
        //GaussianBlur(src64,gauss3,Size(G3.rows,G3.rows),0,0);
	//filter2D(src64,gauss3,CV_64F,G3);
	GaussianBlur(gray0,gauss3,Size(window_3,window_3),sigma3,sigma3);
        Mat r3(src64.rows,src64.cols,CV_64F);
        Mat R3(src64.rows,src64.cols,CV_64F);
        double*pGauss3 = (double*)gauss3.data;
        double*pr3 = (double*)r3.data;
	p64 = (double*)src64.data;
        pGray0 = (double*)gray0.data;
        for(int i =0;i<size;pr3++,pGauss3++,pGray0++,i++)
        {
                *pr3 = ((*pGauss3)/(*pGray0));
        }
        pr3 = (double*)r3.data;
        double*pR3 = (double*)R3.data;
        pGray1 = (double*)gray1.data;
        for(int i =0;i<size;pr3++,pGray1++,pR3++,i++)
        {
                *pR3 = (pow(*pGray1,*pr3));
        }


        /*对上述高斯滤波结果进行线性组合*/
        Mat R(src64.rows,src64.cols,CV_64F);
        pR1 = (double*)R1.data;
        pR2 = (double*)R2.data;
        pR3 = (double*)R3.data;
        double*pR = (double*)R.data;
        for(int i =0;i<size;pR1++,pR2++,pR3++,i++)
        {
                *pR = 1.0/3*(*pR1+*pR2+*pR3);
		//printf("%lf %lf %lf %lf\n",*pR1,*pR2,*pR3,*pR);
		pR++;
        }

        Mat R_8(src64.rows,src64.cols,CV_8UC3);
	uchar*pR8b = R_8.data;
        uchar*p64u = src.data;
        pR = (double*)R.data;
        p64 = (double*)gray0.data;
        uint8_t lambda = 1;


        /*恢复图片颜色*/
        for(int i =0;i<size;pR8b+=3,p64u+=3,p64++,pR++,i++)
        {
                pR8b[BLUE]=(uint8_t)((*pR)*(p64u[BLUE])/(*p64)*lambda);
                pR8b[GREEN]=(uint8_t)((*pR)*(p64u[GREEN])/(*p64)*lambda);
                pR8b[RED]=(uint8_t)((*pR)*(p64u[RED])/(*p64)*lambda);
        }
	//imshow("re",R_8);
        imwrite(path,R_8);
	//imshow("R1",R1);
	//imshow("R2",R2);
	//imshow("R3",R3);
	//imshow("R",R);
	//imshow("gray0",gray0);
	//imshow("gray1",gray1);
}



int main()
{
        char dir1[256] = "./bmp2jpeg/pic";
        DIR* dp = opendir(dir1);
        if(dp == NULL){
        printf("opendir %s fail\n", dir1);
        exit(-1);
        }
        struct dirent *dtp; 
        while(dtp = readdir(dp)){
                if(strcmp(dtp->d_name, ".") == 0 || strcmp(dtp->d_name, "..") == 0){//exclude "." and ".."
                    continue;
                }
                char childFile[FILENAME_MAX]={0};
                strcpy(childFile, dir1);
                strcat(childFile, "/");
                strcat(childFile, dtp->d_name);
                char path[256]={0};
                strcpy(path,"./bmp2jpeg/frames-boost/");
                strcat(path,dtp->d_name);
                DealDark(childFile,path);
        }
}
