/**************************************************
* File name: run.c
* Author: Healer(Yu Hu)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 20th, 2022
*
*Description: This file implements the functional interface of the user interface. When integrating functions into the user interface, it is necessary to modify this file and use the command line option ID to distinguish different functions
**************************************************/

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<pthread.h>
#include<semaphore.h>



int Empty(const char* dirname);
void dealCamera();
sem_t empty,full;

void main(int argc,char*argv[])
{
	printf("Welcome to The Demo\n");
	sem_init(&empty,0,1);
	sem_init(&full,0,0);
	
	if(argc<2)
	{
		printf("Usage: ./run <opt>\n");
		printf("<opt>:\n");
		printf("1:   test the pictures in bmp2jpeg\n");
		printf("2:   test the pictures from camera\n");
		printf("3:   test the pictures in bmp2jpeg-optimized\n");
		printf("5:   deal with the picture with low illumination\n");
		printf("     <way>   --neighbour ; --inverse  ; --neon");
		exit(0);
	}
	
	//DIR * dir = opendir("bmp2jpeg/frames");
	if(!strcmp("1",argv[1]) && Empty("./bmp2jpeg/frames") && Empty("./bmp2jpeg/frames-jpeg"))
	{
		printf("Empty Fold!!\n");//文件夹为空！
		exit(0);
	}
	else if(!strcmp("1",argv[1]) && (!Empty("./bmp2jpeg/frames")||!Empty("./bmp2jpeg/frames-jpeg")))//图像压缩解压缩功能
	{
		if(argc<3)
		{
			printf("Args are less than 3!!\n");
			exit(0);
		}
		printf("Compress the pictures in frames\n");
		if(!strcmp("--normal",argv[2]) && !Empty("./bmp2jpeg/frames-jpeg"))//普通版本
		{
			system("./control_toolkit/control1.bat");
			exit(0);
		}
		else if(!strcmp("--pthread",argv[2]) && !Empty("./bmp2jpeg/frames"))//多线程版本
		{
			system("./control_toolkit/control2.bat");
			exit(0);
		}
		else
			printf("We have not implemented this function OR Frames are empty!\n");
		exit(0);
	}
	else if(!strcmp("3",argv[1]) && Empty("./bmp2jpeg-optimized/frames")&&Empty("./bmp2jpeg-optimized/frames-jpeg"))//NEON图像压缩解压缩功能
	{
		printf("Empty Fold!!\n");
		exit(0);
	}
	else if(!strcmp("3",argv[1]) && (!Empty("./bmp2jpeg-optimized/frames")||!Empty("./bmp2jpeg-optizied/frames-jpeg")))
	{
		
		printf("Compress the pictures in frames\n");
		if(argc==3 && !strcmp("--neon_pthread",argv[2]) && !Empty("./bmp2jpeg-optimized/frames-jpeg"))
		{
			printf("JPEG-NEON-PTHREAD\n");
			system("./control_toolkit/control4.bat");
			exit(0);
		}
		if(!Empty("./bmp2jpeg-optimized/frames"))
		{
			system("./control_toolkit/control3.bat");
			exit(0);
		
		}
		else
		{
			printf("Error!");
			exit(0);
		}
	}
	else if(!strcmp("2",argv[1]))//低照度图像增强
	{
		
		system("./control_toolkit/control_camera/mkD.bat");
		sleep(1);
		pthread_t id;
		pthread_create(&id,NULL,dealCamera,NULL);
		sem_wait(&full);
		system("./control_toolkit/control_camera/control.bat");
		sem_post(&empty);
		pthread_join(id,NULL);
		
		exit(0);	
	}
	else if(!strcmp("5",argv[1]) &&  !Empty("./bmp2jpeg/pic"))
	{
		
		printf("boost pic with dark lightness\n");
		if(!strcmp("--neighbour",argv[2]))//综合邻域信息法
		{
			system("./control_toolkit/boost1.bat");
			exit(0);
		}
		else if(!strcmp("--inverse",argv[2]))//滤色混合法
		{
			system("./control_toolkit/boost2.bat");
			exit(0);
		}
		else if(!strcmp("--neon",argv[2]))//NEON加速的图像增强
		{
			system("./control_toolkit/boost3.bat");
			exit(0);
		}
		else
			printf("We have not implemented this function\n");
		exit(0);
		
	}
}



int Empty(const char* dirname){
    //与文件一样，读目录前也要先打开目录
    DIR* dir = opendir(dirname);
    if(dir == NULL){
        return 1;
    }
    struct dirent *ptr = NULL;
    while((ptr=readdir(dir)) != NULL){
        if(strcmp(".",ptr->d_name)!=0 && strcmp("..",ptr->d_name)!= 0)
        {
            return 0;
            break;
        }
    }
    if(ptr == NULL){
        return 1;
    }
}

void dealCamera()
{
	
		sem_wait(&empty);
		printf("Open Camera\n");
		system("./control_toolkit/control_camera/control_camera.bat");
		sem_post(&full);
}


