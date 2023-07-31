#include<stdio.h>
#include "../neoncal.h"
#include "test.h"
float a[N],b[N],c[N];
void init()
{
    int i;
    for(i=0;i<N;i++)
    {
        a[i]=b[i]=1.5;
    }
}
int main()
{
    int i,j;
    init();
    for(j=0;j<M;j++)
        neon_exp(a,c,10);
}