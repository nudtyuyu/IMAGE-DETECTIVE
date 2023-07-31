#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<time.h>
using namespace std;
int n;
int main(int argc,char**argv)
{
    time_t begin,end;
    
    printf("Input the number of test pictures, 216 in default:\n");
    scanf("%d",&n);
    begin = time(NULL);
    if(!strcmp(argv[1],"2"))
    {

    	 freopen("./control_toolkit/command2.bat","w",stdout);
   	 char command1[500];
   	 char command2[500];
   	 snprintf(command1,500,"./jpeg-pthread/cjpeg -num %d -dct int -outfile ./bmp2jpeg/b ./bmp2jpeg/frames",n);
   	 snprintf(command2,500,"./jpeg-pthread/djpeg -num %d -bmp -outfile ./bmp2jpeg/a ./bmp2jpeg/b",n-4);
    	printf("%s\n",command1);
    	printf("%s\n",command2);
    }
    else if(!(strcmp(argv[1],"1")))
    {
	    freopen("./control_toolkit/command1.bat","w",stdout);
	    int x =1;
    	    for(int i=1;i<=n;i++)
    	    {
        
       		 printf("(time ./jpeg-6b/cjpeg -dct int -outfile ./bmp2jpeg/b/%d.jpg ./bmp2jpeg/frames-jpeg/%d.bmp) >& ./bmp2jpeg/time/time_usage%d\n",x,x,x);
        	 printf("./jpeg-6b/djpeg -outfile ./bmp2jpeg/a/%d.bmp -bmp ./bmp2jpeg/b/%d.jpg\n",x,x);
                 x++;
   	    }
	    printf("python3 ./control_toolkit/view.py\n");


	    
    }
    else if(!strcmp(argv[1],"3"))
    {
	    freopen("./control_toolkit/command3.bat","w",stdout);
            int x =1;
            for(int i=1;i<=n;i++)
            {

                 printf("(time ./jpeg2-6b/build/cjpeg -dct int -outfile ./bmp2jpeg-optimized/b/%d.jpg ./bmp2jpeg-optimized/frames/%d.bmp) >& ./bmp2jpeg-optimized/time/time_usage%d\n",x,x,x);
                 printf("./jpeg2-6b/build/djpeg -outfile ./bmp2jpeg-optimized/a/%d.bmp -bmp ./bmp2jpeg-optimized/b/%d.jpg\n",x,x);
                 x++;
            }
	    printf("python3 ./control_toolkit/3/view.py");
    }
    else if(!strcmp(argv[1],"4"))
    {
	    freopen("./control_toolkit/command4.bat","w",stdout);
	    char command1[500];
            char command2[500];
	    //printf("num: %d",n)
            snprintf(command1,500,"./jpeg-neon-pthread/build/cjpeg -num %d -dct int -outfile ./bmp2jpeg-optimized/b ./bmp2jpeg-optimized/frames-jpeg",n);
            snprintf(command2,500,"./jpeg-neon-pthread/build/djpeg -num %d -bmp -outfile ./bmp2jpeg-optimized/a ./bmp2jpeg-optimized/b",n-4);
            printf("%s\n",command1);
            printf("%s\n",command2);

    } 
    else
    {
	    fclose(stdout);
	    printf("error!no such function!\n");
	    exit(0);
    }
    fclose(stdout);
    end = time(NULL);
    return 0;
}
