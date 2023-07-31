
/*
* 这里用来判断neonmath库的正确性
*/
#include<iostream>
#include "./neonlib/neoncal.h"
using namespace std;
int a[100],b[100],c[100];
int main()
{
    a[0]=2,b[0]=2;
    neon_add((void*)a,(void *)b,(void *)c,100,32,0);
    cout<<c[0];
}
