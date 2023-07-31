#include<stdio.h>
#include "../neoncal.h"
#include "test.h"
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
    for(j=0;j<M;j++)
        neon_mul(a,b,c,N,32,0);
}