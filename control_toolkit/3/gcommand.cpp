/**************************************************
* File name: 3/gcommand.cpp
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 
* 描述：本文件实现将命令写入控制脚本,控制JPEG压缩解压缩的NEON加速
**************************************************/








#include<cstdio>
#include<cstdlib>
using namespace std;
int n;
int main()
{
    printf("Input the number of test pictures, 216 in default:\n");
    scanf("%d",&n);

    freopen("./control_toolkit/3/command.bat","w",stdout);
    int x=1;
    /*for(int i=1;i<=n;i++)
    {
	    printf("touch ./bmp2jpeg/time/time_usage%d\n",x);
	    x++;
    }*/
    x = 1;
    for(int i=1;i<=n;i++)
    {
	
        printf("(time ./jpeg2-6b/cjpeg -dct int -outfile ./bmp2jpeg-optimized/b/%d.jpg ./bmp2jpeg-optimized/frames/%d.bmp) >& ./bmp2jpeg-optimized/time/time_usage%d\n",x,x,x);
	printf("./jpeg2-6b/djpeg -outfile ./bmp2jpeg-optimized/a/%d.bmp -bmp ./bmp2jpeg-optimized/b/%d.jpg\n",x,x);
        x++;
    }
    fclose(stdout);
}
