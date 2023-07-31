/**************************************************
* File name: control_camera/gcommand.cpp
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 
* 描述：本文件实现将命令写入控制脚本,控制摄像头
**************************************************/







#include<cstdio>
#include<cstdlib>
using namespace std;
int n;
int main()
{
    
    freopen("./control_toolkit/control_camera/command.bat","w",stdout);
    int x=1;
    n=50;
   /* for(int i=1;i<=n;i++)
    {
	    printf("touch ./camera/time/time_usage%d\n",x);
	    x++;
    }*/
    x = 1;
    int i=1;
    for(i=1;i<=n;i++)
    {
	
        printf("(time ./jpeg-6b/cjpeg -dct int -outfile ./camera/b/%d.jpg ./camera/frames/%d.bmp) >& ./camera/time/time_usage%d\n",x,x,x);
	printf("./jpeg-6b/djpeg -outfile ./camera/a/%d.bmp -bmp ./camera/b/%d.jpg\n",x,x);
        x++;
    }
    fclose(stdout);
}
