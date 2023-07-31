/*低照度图像处理函数neon版本*/
/**************************************************
* File name：dark_neon.cpp
* Author: Healer(胡玉),Banish(李剑锋)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 
* 描述：本文件是低照度图像增强NEON加速版本
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

#ifndef SCREEN_XY
#define SCREEN_XY(x,y) (255-((255-x))*(255-(y))>>8)
#endif


/*对低照度图像进行处理*/
void DealDark(char filename[],char path[])
{
	Mat src = imread(filename,CV_LOAD_IMAGE_COLOR);
//	imshow("src",src);
//	cout<<path<<endl;
	int size = src.cols * src.rows;
	uchar r=0,g=0,b=0,g_alpha=0;
	uchar*pSrcData = src.data;
	//cout<<size<<endl;
	//for(int i=0;i<size*3;i++)
	//	color[i]=src.data[i];
	for(int i=0;i<size;i+=2,pSrcData +=6)
	{
		g_alpha = 255 - pSrcData[GREEN];
		uint16x8_t a={pSrcData[0],pSrcData[1],pSrcData[2],0,pSrcData[3],pSrcData[4],pSrcData[5],0},b;/*将两个像素的rgb通道整合入向量*/
		b=(a*g_alpha>>8);
		for(int j=0;j<5;j++)/*5次滤色混合*/
			a=255-((255-a)*(255-b)>>8);
		
		/*更新滤波后的颜色*/
		pSrcData[0]=a[0];
		pSrcData[1]=a[1];
		pSrcData[2]=a[2];
		pSrcData[3]=a[4];
		pSrcData[4]=a[5];
		pSrcData[5]=a[6];
	}
//	imshow("dst",src);
	imwrite(path,src);
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
