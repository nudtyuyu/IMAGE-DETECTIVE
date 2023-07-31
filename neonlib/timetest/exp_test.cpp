#include<stdio.h>
#include<math.h>
#include "test.h"
float a[N],b[N],c[N];
void init()
{
    int i;
    for(i=0;i<N;i++)
    {
        a[i]=b[i]=2.23131231;
    }
}
int main()
{
    // printf("%f",expf(1.5));
    int i,j;
    init();
    a[0]=2;
    for(j=0;j<M;j++)
    {
        for(i=1;i<N;i++){
            c[i]=exp(a[i]);
            // c[i]=a[i]*a[i];
            // printf("%f\n",c[i]);
            // break;
        }
    }
}