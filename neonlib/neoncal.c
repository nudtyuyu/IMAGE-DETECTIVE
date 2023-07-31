#include<stdio.h>
#include<arm_neon.h>
#include<stdlib.h>
void neon_add_int64(int64_t *a,int64_t *b,int64_t *c,int num)
{
    int i;
    
    for(i=0;i<num-1;i+=2)
    {
        int64x2_t s1=vld1q_s64(a+i);
        int64x2_t s2=vld1q_s64(b+i);
        
        s1=vaddq_s64(s1,s2);

        vst1q_s64(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]+b[i];
    }
}

void neon_add_int32(int *a,int *b,int *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        int32x4_t s1=vld1q_s32(a+i);
        int32x4_t s2=vld1q_s32(b+i);
        
        s1=vaddq_s32(s1,s2);

        vst1q_s32(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]+b[i];
    }
}


void neon_add_flt32(float *a,float *b,float *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        float32x4_t s1=vld1q_f32(a+i);
        float32x4_t s2=vld1q_f32(b+i);
        
        s1=vaddq_f32(s1,s2);

        vst1q_f32(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]+b[i];
    }
}
void neon_add_int16(int16_t *a,int16_t *b,int16_t *c,int num)
{
    int i;
    
    for(i=0;i<num-7;i+=8)
    {
        int16x8_t s1=vld1q_s16(a+i);
        int16x8_t s2=vld1q_s16(b+i);
        
        s1=vaddq_s16(s1,s2);

        vst1q_s16(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]+b[i];
    }
}

void neon_add_int8(int8_t *a,int8_t *b,int8_t *c,int num)
{
    int i;
    
    for(i=0;i<num-15;i+=16)
    {
        int8x16_t s1=vld1q_s8(a+i);
        int8x16_t s2=vld1q_s8(b+i);
        
        s1=vaddq_s8(s1,s2);

        vst1q_s8(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]+b[i];
    }
}

void neon_sub_int64(int64_t *a,int64_t *b,int64_t *c,int num)
{
    int i;
    
    for(i=0;i<num-1;i+=2)
    {
        int64x2_t s1=vld1q_s64(a+i);
        int64x2_t s2=vld1q_s64(b+i);
        
        s1=vsubq_s64(s1,s2);

        vst1q_s64(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]-b[i];
    }
}

void neon_sub_int32(int *a,int *b,int *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        int32x4_t s1=vld1q_s32(a+i);
        int32x4_t s2=vld1q_s32(b+i);
        
        s1=vsubq_s32(s1,s2);

        vst1q_s32(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]-b[i];
    }
}


void neon_sub_flt32(float *a,float *b,float *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        float32x4_t s1=vld1q_f32(a+i);
        float32x4_t s2=vld1q_f32(b+i);
        
        s1=vsubq_f32(s1,s2);

        vst1q_f32(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]-b[i];
    }
}
void neon_sub_int16(int16_t *a,int16_t *b,int16_t *c,int num)
{
    int i;
    
    for(i=0;i<num-7;i+=8)
    {
        int16x8_t s1=vld1q_s16(a+i);
        int16x8_t s2=vld1q_s16(b+i);
        
        s1=vsubq_s16(s1,s2);

        vst1q_s16(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]-b[i];
    }
}

void neon_sub_int8(int8_t *a,int8_t *b,int8_t *c,int num)
{
    int i;
    
    for(i=0;i<num-15;i+=16)
    {
        int8x16_t s1=vld1q_s8(a+i);
        int8x16_t s2=vld1q_s8(b+i);
        
        s1=vsubq_s8(s1,s2);

        vst1q_s8(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]-b[i];
    }
}

void neon_mul_int32(int *a,int *b,int *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        int32x4_t s1=vld1q_s32(a+i);
        int32x4_t s2=vld1q_s32(b+i);
        
        s1=vmulq_s32(s1,s2);

        vst1q_s32(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]*b[i];
    }
}

void neon_mul_int16(int16_t *a,int16_t *b,int16_t *c,int num)
{
    int i;
    
    for(i=0;i<num-7;i+=8)
    {
        int16x8_t s1=vld1q_s16(a+i);
        int16x8_t s2=vld1q_s16(b+i);
        
        s1=vmulq_s16(s1,s2);

        vst1q_s16(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]*b[i];
    }
}

void neon_mul_int8(int8_t *a,int8_t *b,int8_t *c,int num)
{
    int i;
    
    for(i=0;i<num-15;i+=16)
    {
        int8x16_t s1=vld1q_s8(a+i);
        int8x16_t s2=vld1q_s8(b+i);
        
        s1=vmulq_s8(s1,s2);

        vst1q_s8(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]*b[i];
    }
}

void neon_mul_flt32(float *a,float *b,float *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        float32x4_t s1=vld1q_f32(a+i);
        float32x4_t s2=vld1q_f32(b+i);
        
        s1=vmulq_f32(s1,s2);

        vst1q_f32(c+i,s1);
        
    }
    for(i;i<num;++i)
    {
        c[i]=a[i]*b[i];
    }
}

void neon_add(void *a,void *b,void *c,int num,int w,int type)//m*n
{
    if(type==0)//integer
    {
        if(w==32)
        {
            neon_add_int32((int*)a,(int *)b,(int *)c,num);
        }
        else if(w==16)
        {
            neon_add_int16((int16_t *)a,(int16_t *)b,(int16_t *)c,num);
        }
        else if(w==8)
        {
            neon_add_int8((int8_t *)a,(int8_t *)b,(int8_t *)c,num);
        }
        else if(w==64)
        {
            neon_add_int64((int64_t *)a,(int64_t *)b,(int64_t *)c,num);
        }
        else 
        {
            printf("Error add neon type!\n");
            exit(0);
        }
    }
    else if(type==1)
    {
        if(w==32)
        {
            neon_add_flt32((float*)a,(float *)b,(float *)c,num);
        }
        else
        {
            printf("Unsupport type of neon_add!\n");
            exit(0);
        }
    }
    else
    {
        printf("Error neon_add type!\n");
        exit(0);
    }
}

void neon_mul(void *a,void *b,void *c,int num,int w,int type)
{
    if(type==0)//integer
    {
        if(w==32)
        {
            neon_mul_int32((int*)a,(int *)b,(int *)c,num);
        }
        else if(w==16)
        {
            neon_mul_int16((int16_t *)a,(int16_t *)b,(int16_t *)c,num);
        }
        else if(w==8)
        {
            neon_mul_int8((int8_t *)a,(int8_t *)b,(int8_t *)c,num);
        }
        else
        {
            printf("Error neon-mul type!\n");
            exit(0);
        }
    }
    else if(type==1)
    {
        if(w==32)
        {
            neon_mul_flt32((float*)a,(float *)b,(float *)c,num);
        }
        else
        {
            printf("Error neon-mul type!\n");
            exit(0);
        }
    }
    else 
        printf("Unsupproted neon_mul type!\n");
}


void neon_sub(void *a,void *b,void *c,int num,int w,int type)
{
    if(type==0)//integer
    {
        if(w==32)
        {
            neon_sub_int32((int*)a,(int *)b,(int *)c,num);
        }
        else if(w==16)
        {
            neon_sub_int16((int16_t *)a,(int16_t *)b,(int16_t *)c,num);
        }
        else if(w==8)
        {
            neon_sub_int8((int8_t *)a,(int8_t *)b,(int8_t *)c,num);
        }
        else if(w==64)
        {
            neon_sub_int64((int64_t *)a,(int64_t *)b,(int64_t *)c,num);
        }
        else 
        {
            printf("Error sub neon type!\n");
            exit(0);
        }
    }
    else if(type==1)
    {
        if(w==32)
        {
            neon_sub_flt32((float*)a,(float *)b,(float *)c,num);
        }
        else
        {
            printf("Unsupport type of neon_sub!\n");
            exit(0);
        }
    }
    else
    {
        printf("Error neon_sub type!\n");
        exit(0);
    }
}
