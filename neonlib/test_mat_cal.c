#include "neoncal.h"
#include<stdio.h>
#include<stdlib.h>
int a32[32][32],b32[32][32],c32[32][32],cc32[32][32];
int m,n,k;
void testmatmul_int32()
{
    int *a=(int *)a32,*b=(int *)b32,*c=(int *)c32,*cc=(int *)cc32;
    int i,j,t;
    // printf("%d %d %d\n",m,n,k);
    for(i=0;i<m*n;i++)
        a[i]=i;
     
    for(i=0;i<n*k;i++)
        b[i]=1;
    for(i=0;i<m*k;i++)
        cc[i]=0;
    
    for(i=0;i<m;i++)
        for(t=0;t<n;t++)
            for(j=0;j<k;j++)    
                cc[i*k+j]+=a[i*n+t]*b[t*k+j];    
    neon_mat_mul((void*)a,(void*)b,(void*)c,m,n,k,32,0);
    for(i=0;i<m*k;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("matmul_int32 error!\n");
            printf("%d %d %d %d\n",i/m,i%m,c[i],cc[i]);
            exit(0);
        }
    }
}

int main()
{
    // printf("1");

    m=n=k=32;
    // k=31;
    // n=29;
    // m=18;
    // m=n=k=10;
    testmatmul_int32();

}