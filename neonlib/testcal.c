#include "neoncal.h"
#include<stdio.h>
#include<stdlib.h>
int a32[32][32],b32[32][32],c32[32][32],cc32[32][32];
int m,n;
void testadd_int32()
{
    int *a=(int *)a32,*b=(int *)b32,*c=(int *)c32,*cc=(int *)cc32;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]+b[i];
    }
    neon_add((void *)a,(void *)b,(void *)c,m*n,32,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("add_int32 error!");
            exit(0);
        }
    }
}

void testmul_int32()
{
    int *a=(int *)a32,*b=(int *)b32,*c=(int *)c32,*cc=(int *)cc32;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]*b[i];
    }
    neon_mul((void *)a,(void *)b,(void *)c,m*n,32,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("mul_int32 error!");
            exit(0);
        }
    }
}

int16_t a16[32][32],b16[32][32],c16[32][32],cc16[32][32];
void testadd_int16()
{
    int16_t *a=(int16_t *)a16,*b=(int16_t *)b16,*c=(int16_t *)c16,*cc=(int16_t *)cc16;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]+b[i];
    }
    neon_add((void *)a,(void *)b,(void *)c,m*n,16,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("add_int16 error!");
            exit(0);
        }
    }
}
void testmul_int16()
{
    int16_t *a=(int16_t *)a16,*b=(int16_t *)b16,*c=(int16_t *)c16,*cc=(int16_t *)cc16;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]*b[i];
    }
    neon_mul((void *)a,(void *)b,(void *)c,m*n,16,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("mul_int16 error!");
            exit(0);
        }
    }
}


int8_t a8[32][32],b8[32][32],c8[32][32],cc8[32][32];
void testadd_int8()
{
    int8_t *a=(int8_t *)a8,*b=(int8_t *)b8,*c=(int8_t *)c8,*cc=(int8_t *)cc8;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]+b[i];
    }
    neon_add((void *)a,(void *)b,(void *)c,m*n,8,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("add_int8 error!");
            exit(0);
        }
    }
}
void testmul_int8()
{
    int8_t *a=(int8_t *)a8,*b=(int8_t *)b8,*c=(int8_t *)c8,*cc=(int8_t *)cc8;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]*b[i];
    }
    neon_mul((void *)a,(void *)b,(void *)c,m*n,8,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("mul_int8 error!");
            exit(0);
        }
    }
}




int64_t a64[32][32],b64[32][32],c64[32][32],cc64[32][32];
void testadd_int64()
{
    int64_t *a=(int64_t *)a64,*b=(int64_t *)b64,*c=(int64_t *)c64,*cc=(int64_t *)cc64;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]+b[i];
    }
    neon_add((void *)a,(void *)b,(void *)c,m*n,64,0);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("add_int64 error!");
            exit(0);
        }
    }
}

float a_f32[32][32],b_f32[32][32],c_f32[32][32],cc_f32[32][32];
int m,n;
void testadd_flt32()
{
    float *a=(float *)a_f32,*b=(float *)b_f32,*c=(float *)c_f32,*cc=(float *)cc_f32;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]+b[i];
    }
    neon_add((void *)a,(void *)b,(void *)c,m*n,32,1);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("add_flt32 error!");
            exit(0);
        }
    }
}

void testmul_flt32()
{
    float *a=(float *)a_f32,*b=(float *)b_f32,*c=(float *)c_f32,*cc=(float *)cc_f32;
    for(int i=0;i<m*n;i++)
    {
        a[i]=i,b[i]=i,cc[i]=a[i]*b[i];
    }
    neon_mul((void *)a,(void *)b,(void *)c,m*n,32,1);
    for(int i=0;i<m*n;i++)
    {
        if(c[i]!=cc[i])
        {
            printf("mul_flt32 error!");
            exit(0);
        }
    }
}


int main()
{
    // printf("1");
    m=n=30;
    testadd_int32();
    testadd_int16();
    testadd_int8();
    testadd_int64();
    testadd_flt32();

    testmul_int32();
    testmul_int16();
    testmul_int8();
    testmul_flt32();
}