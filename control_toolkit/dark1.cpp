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



void DealDark(char filename[],char path[])
{
	Mat src = imread(filename,CV_LOAD_IMAGE_COLOR);
	imshow("src",src);

	int size = src.cols * src.rows;
	uchar r=0,g=0,b=0,g_alpha=0;
	uchar*pSrcData = src.data;
	for(int i=0;i<size;i++,pSrcData +=3)
	{
		g_alpha = 255 - pSrcData[GREEN];
		b = pSrcData[BLUE]*g_alpha>>8;
		g = pSrcData[GREEN]*g_alpha>>8;
		r = pSrcData[RED]*g_alpha>>8;
		for(int j=0;j<5;j++)
		{
			pSrcData[BLUE]=SCREEN_XY(pSrcData[BLUE],b);
			pSrcData[GREEN]=SCREEN_XY(pSrcData[GREEN],g);
			pSrcData[RED]=SCREEN_XY(pSrcData[RED],r);
		}
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
                //printf(childFile);
                //printf(path);
                DealDark(childFile,path);
        }
}
