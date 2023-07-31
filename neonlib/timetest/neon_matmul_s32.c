#include<stdio.h>
#include "../neoncal.h"
#include "test.h"
int a[mat_m][mat_n],b[mat_n][mat_k],c[mat_m][mat_k];
void init()
{
    int i,j;
    for(i=0;i<mat_m;i++)
        for(j=0;j<mat_n;j++)
            a[i][j]=i;
    for(i=0;i<mat_n;i++)
        for(j=0;j<mat_k;j++)
            b[i][j]=1;
}
int main()
{
    int i,j,t,num;
    init();
    
    for(num=0;num<2;num++)
    {
        neon_mat_mul(a,b,c,mat_m,mat_n,mat_k,32,0);
    }  
    
}