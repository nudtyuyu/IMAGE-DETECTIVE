#include<stdio.h>
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
        for(i=0;i<mat_m;i++)
            for(j=0;j<mat_k;j++)
                c[i][j]=0;
        for(i=0;i<mat_m;i++)
            for(t=0;t<mat_n;t++)
                for(j=0;j<mat_k;j++)    
                    c[i][j]+=a[i][t]*b[t][j]; 
    }  
    
}