#include<stdio.h>
#include<arm_neon.h>
#include<stdlib.h>
void neon_mat_mul_int32(int *a,int *b,int *c,int m,int n,int k)
{
    int i,j,t;
    for(i=0;i<m*k;i++)
        c[i]=0;
    for(i=0;i<m;i++)
    for(t=0;t<n;t++)
    {
        int s1=a[i*n+t];
        for(j=0;j<k-3;j+=4)
        {
            
            int32x4_t s2=vld1q_s32(b+t*k+j);
            int32x4_t ans=vld1q_s32(c+i*k+j);
            ans=ans+s2*s1;
            vst1q_s32(c+i*k+j,ans);
        }
        for(j;j<k;++j)
        {
            c[i*k+j]+=s1*b[t*k+j];
        }
    }    
}
void neon_mat_mul_int16(int16_t *a,int16_t *b,int16_t *c,int m,int n,int k)
{
    int i,j,t;
    for(i=0;i<m*k;i++)
        c[i]=0;
    for(i=0;i<m;i++)
    for(t=0;t<n;t++)
    {
        int16_t s1=a[i*n+t];
        for(j=0;j<k-7;j+=8)
        {
            
            int16x8_t s2=vld1q_s16(b+t*k+j);
            int16x8_t ans=vld1q_s16(c+i*k+j);
            ans=ans+s2*s1;
            vst1q_s16(c+i*k+j,ans);
        }
        for(j;j<k;++j)
        {
            c[i*k+j]+=s1*b[t*k+j];
        }
    }    
}

void neon_mat_mul_flt32(float *a,float *b,float *c,int m,int n,int k)
{
    int i,j,t;
    for(i=0;i<m*k;i++)
        c[i]=0;
    for(i=0;i<m;i++)
    for(t=0;t<n;t++)
    {
        float s1=a[i*n+t];
        for(j=0;j<k-3;j+=4)
        {
            
            float32x4_t s2=vld1q_f32(b+t*k+j);
            float32x4_t ans=vld1q_f32(c+i*k+j);
            ans=ans+s2*s1;
            vst1q_f32(c+i*k+j,ans);
        }
        for(j;j<k;++j)
        {
            c[i*k+j]+=s1*b[t*k+j];
        }
    }    
}

void neon_mat_mul_int8(int8_t *a,int8_t *b,int8_t *c,int m,int n,int k)
{
    int i,j,t;
    for(i=0;i<m*k;i++)
        c[i]=0;
    for(i=0;i<m;i++)
    for(t=0;t<n;t++)
    {
        int8_t s1=a[i*n+t];
        for(j=0;j<k-15;j+=16)
        {
            
            int8x16_t s2=vld1q_s8(b+t*k+j);
            int8x16_t ans=vld1q_s8(c+i*k+j);
            ans=ans+s2*s1;
            vst1q_s8(c+i*k+j,ans);
        }
        for(j;j<k;++j)
        {
            c[i*k+j]+=s1*b[t*k+j];
        }
    }    
}

void neon_mat_mul(void *a,void *b,void *c,int m,int n,int k,int w,int type)
{
    if(type==0)//integer
    {
        if(w==32)
            neon_mat_mul_int32((int*)a,(int *)b,(int *)c,m,n,k);
        else if(w==16)
            neon_mat_mul_int16((int16_t*)a,(int16_t *)b,(int16_t *)c,m,n,k);
        else if(w==8)
            neon_mat_mul_int8((int8_t*)a,(int8_t *)b,(int8_t *)c,m,n,k);
        else 
            printf("Unsupported type!\n");
    }   
    else if(type==1)
    {
        if(w==32)
            neon_mat_mul_flt32((float*)a,(float*)b,(float*)c,m,n,k);
        else 
            printf("Unsupported type!\n");
    }
    else
        printf("Error!\n");
}
