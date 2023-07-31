#include<stdio.h>
#include "neoncal.h"
#define N 1000000
int a[N],b[N],c[N];
void init()
{
    int i;
    for(i=0;i<N;i++)
    {
        a[i]=b[i]=i;
    }
}
int main()
{
    int i,j;
    init();
    for(j=0;j<100;j++)
    for(i=0;i<N;i++)
    {
        c[i]=a[i]+b[i];
    }
}