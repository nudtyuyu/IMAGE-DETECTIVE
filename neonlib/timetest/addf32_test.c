#include<stdio.h>
#include "test.h"
float a[N],b[N],c[N];
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
    for(j=0;j<M;j++)
    for(i=0;i<N;i++)
    {
        c[i]=a[i]+b[i];
    }
}