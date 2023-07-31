/*用于生成控制指令，自动生成双压缩篡改训练集和测试集*/
#include <cstdio>
//#include<iostream>
#include <cstdlib>
using namespace std;
int n = 100;
int main()
{
    char fn[100];
    scanf("%s",fn);
    freopen("./control_toolkit/antijpeg/command.bat", "w", stdout);
    int j=0;
    while(fn[j])
	    j+=1;
  fn[j]='.';j++;
  fn[j]='j';j++;
  fn[j]='p';j++;
  fn[j]='g';j++;
  fn[j]=0;
 // cout<<j<<"\n";
    // for (int i = 0; i <10000; i++)
    // {
    //     printf("djpeg -rgb -outfile b/%012d.bmp -bmp 0/%012d.jpg\n", i, i);
    //     printf("cjpeg -dct fast -quality 35 -outfile 1/%012d.jpeg b/%012d.bmp\n", i, i);
    //     printf("djpeg -rgb -outfile b1/%012d.bmp -bmp 1/%012d.jpeg\n", i, i);
    //     printf("./sjpeg b/%012d.bmp text/%012d.txt\n", i, i);
    //     printf("./sjpeg b1/%012d.bmp text1/%012d.txt\n", i, i);
    // }
    printf("cp ./antiedit/from/%s ./antiedit/from/display.jpg\n",fn);
    printf("./jpeg-6b/djpeg -bmp -outfile ./antiedit/from/display.bmp ./antiedit/from/display.jpg\n");
    // printf("cjpeg -dct fast -quality 35 -outfile 1/display.jpeg b/display.bmp\n");
    // printf("djpeg -rgb -outfile b1/display.bmp -bmp 1/display.jpeg\n");
    // printf("./sjpeg b/display.bmp text/display.txt\n");
    
    printf("./control_toolkit/antijpeg/sjpeg ./antiedit/from/display.bmp ./antiedit/from/display.txt\n");

    printf("mv ./antiedit/from/display.txt ./control_toolkit/antijpeg/TEST_1/display.txt\n");
    printf("./control_toolkit/antijpeg/realanti\n");//sget change.txt
    printf("./control_toolkit/antijpeg/changebmp\n");
    fclose(stdout);
}
