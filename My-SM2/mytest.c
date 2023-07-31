/**************************************************
* File name: test_demo.c
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* Description: implement test demo program for
    SM2 encrypt data and decrypt ciphertext
*描述：本文件实现了支持多线程的SM2文件加密解密，将加密后的文件存入./camera/encrypt中,解密后的文件存入./camera/decrypt中
**************************************************/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <sched.h>
#include <ctype.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include "test_sm2_encrypt_and_decrypt.h"
#include "sm2_create_key_pair.h"

/*********************************************************/
int encrypt_decrypt(char * srcfile,char * dstfile,char * defile);
void * do_thread(void*arg);
int NUM;

int main()
{
        char dir1[256] = "./camera/b";
        DIR* dp = opendir(dir1);
        int cpu_num = sysconf(_SC_NPROCESSORS_CONF)-2;//获取机器CPU数量
        pthread_t thread[cpu_num];
        int i=1;
        int filenum=0;
        if(dp == NULL){
        printf("opendir %s fail\n", dir1);
        exit(-1);
        }
        struct dirent *dtp;
        while(dtp = readdir(dp)){
                if(strcmp(dtp->d_name, ".") == 0 || strcmp(dtp->d_name, "..") == 0){//exclude "." and ".."
                    continue;
                }
                filenum++;
        }
        NUM=filenum/cpu_num;
        for(i=0;i<cpu_num;i++)
        {
        	int * id=(int*)malloc(sizeof(int));
        	*id=i;
        	pthread_create(&thread[i],NULL,do_thread,id);//创建线程
        }
        for (i = 0; i < cpu_num; i++) 
        {
        	pthread_join(thread[i], NULL);
        }
        return 0;
}
void * do_thread(void*arg)
{
	int i;
	int id=*(int*)arg;
	
	char dir1[256] = "./camera/b";
	for(i=1+id*NUM;i<id*NUM+NUM+1;i++)
	{	 
                char c[5];
                sprintf(c,"%d",i);
                char childFile[FILENAME_MAX]={0};
                strcpy(childFile, dir1);
                strcat(childFile, "/");
                strcat(childFile,c);
                strcat(childFile,".jpg");
                char path[256]={0};
                strcpy(path,"./camera/encrypt/");
                strcat(path,"en-");
                strcat(path,c);
                char path2[256]={0};
                strcpy(path2,"./camera/decrypt/");
                strcat(path2,"de-");
                strcat(path2,c);
                encrypt_decrypt(childFile,path,path2);//进行文件加密解密
        }
}




int encrypt_decrypt(char * srcfile,char * dstfile,char * defile)
{
	int error_code;
	
	FILE *p=fopen(srcfile,"rb");//原始文件
	FILE *enP = fopen(dstfile,"wb");//加密文件
	FILE *deP = fopen(defile,"w");//解密文件
	
	/*获取原始文件字节数*/
	int srcbyte = 0;
	fseek(p,0,SEEK_END);	
	srcbyte = ftell(p);		
	fseek(p,0,SEEK_SET);			
	int readbyte = 0;
	int msg_len;
	int write=0;

	/*加密*/
	while(!feof(p))
	{
		void *buffer =  malloc(sizeof(char)*4096);//每次读取4096个字节
		void *encrpy =  malloc(sizeof(char)*(4193+sizeof(SM2_KEY_PAIR)));//加密文件除了密文外还有其他部分，长度大于4096
		int count = fread(buffer,1,4096,p);
		if ( error_code = test_sm2_encrypt(buffer,encrpy,count) )
		{
			printf("Test create SM2 key pair, encrypt data and decrypt ciphertext failed!\n");
			return error_code;
		}
		else
		{
			;//printf("Test create SM2 key pair, encrypt data and decrypt ciphertext succeeded!\n");
		}
		
		write+=fwrite(encrpy,1,count+C1_LENGTH+C3_LENGTH+sizeof(SM2_KEY_PAIR),enP);
		readbyte += count;
		
		if(readbyte >= srcbyte) 
			break;
	}


	/*解密*/
	fclose(enP);
	fseek(p,0,SEEK_SET);
	enP = fopen(dstfile,"rb");
	srcbyte = 0;
	fseek(enP,0,SEEK_END);	
	srcbyte = ftell(enP);		
	fseek(enP,0,SEEK_SET);			
	readbyte = 0;
	write=0;
	while(!feof(enP))
	{
		void *origin =  malloc(sizeof(char)*4096);//每次读取4096个字节
		void *buffer =  malloc(sizeof(char)*(4193+sizeof(SM2_KEY_PAIR)));//加密文件除了密文外还有其他部分，长度大于4096
		void *decrpy =  malloc(sizeof(char)*4096);//解密文件与原始文件大小相同
		int count = fread(buffer,1,4193+sizeof(SM2_KEY_PAIR),enP);
		//printf("\n\n%d\n\n",count);
		fread(origin,1,4096,p);
		if ( error_code = test_sm2_decrypt(origin,buffer,decrpy,count) )
		{
			printf("Test create SM2 key pair, encrypt data and decrypt ciphertext failed!\n");
			return error_code;
		}
		else
		{
			;
		}
		//printf("\n\n%d\n\n",count);
		write+=fwrite(decrpy,1,count-sizeof(SM2_KEY_PAIR)-C1_LENGTH-C3_LENGTH,deP);
		//printf("\n\n%d\n\n",write);
		readbyte += count;
		//printf("\n\n%d\t\t%d\n\n",srcbyte,readbyte);
		if(readbyte >= srcbyte) 
			break;
	}
	fclose(p);
	fclose(enP);
	fclose(deP);
	printf("Test create SM2 key pair, encrypt data and decrypt ciphertext succeeded!\n");//加密解密成功
	

#if defined(_WIN32) || defined(_WIN64)
  system("pause");
#endif
	return 0;
}
