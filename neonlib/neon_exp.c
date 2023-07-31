#include<stdio.h>
#include<arm_neon.h>
#include<stdlib.h>
#include<math.h>
#define log_2 0.6931471806
#define one_log2 1.4426950409 //1/log(2)
/*
Based on: 

		e ^ x = m * (2^n)
		x = log(m) + n * log(2)
		n = (int) (x * 1.0 / log(2))
		m = e ^ (x - n * log(2))
*/
float32x4_t s2={one_log2,one_log2,one_log2,one_log2};
float32x4_t s7={log_2,log_2,log_2,log_2};
int32x4_t s6={1,1,1,1};
const float xs[8] = {
	0.9999999916728642,		//p0
	0.04165989275009526, 	//p4
	1.000000059694879, 		//p1
	0.008336936973260111, 	//p5
    0.5000006143673624, 	//p2
	0.0014122663401803872, 	//p6
	0.16666570253074878, 	//p3
	0.00019578093328483123	//p7
};
void neon_exp(float *a,float *c,int num)
{
    int i;
    
    for(i=0;i<num-3;i+=4)
    {
        float32x4_t s1,s4,s5,s8;
        float32x4_t ss0,ss1,ss2,ss3;
        float32x4_t ans1,ans2;
        int32x4_t s3;
        s5=vld1q_f32(a+i);//s5=a
        s1=vmulq_f32(s5,s2);//s1=s5/log(2)
        s3=vcvtq_s32_f32(s1);//s3=(int)s1    n
        ans1=vcvtq_f32_s32(vqshlq_s32(s6,s3));//1<<n

        s4=vcvtq_f32_s32(s3);//s4=(float)s3  n
        s4=vsubq_f32(s5,vmulq_f32(s4,s7));// s4 t=log(m)
        
        s1=vmulq_f32(s4,s4);//t^2
        s5=vmulq_f32(s1,s4);//t^3
        s8=vmulq_f32(s1,s1);//t^4
        ss0=vaddq_f32(vdupq_n_f32(xs[0]),vmulq_f32(s8,vdupq_n_f32(xs[1])));
        ss1=vmulq_f32(vaddq_f32(vdupq_n_f32(xs[2]),vmulq_f32(s8,vdupq_n_f32(xs[3]))),s4);
        ss0=vaddq_f32(ss0,ss1);
        ss2=vmulq_f32(vaddq_f32(vdupq_n_f32(xs[4]),vmulq_f32(s8,vdupq_n_f32(xs[5]))),s1);
        ss3=vmulq_f32(vaddq_f32(vdupq_n_f32(xs[6]),vmulq_f32(s8,vdupq_n_f32(xs[7]))),s5);
        ss2=vaddq_f32(ss2,ss3);
        ans2=vaddq_f32(ss0,ss2);

        ans1=vmulq_f32(ans1,ans2);
        vst1q_f32(c+i,ans1);
        
    }
    for(i;i<num;++i)
    {
        float s1,s2,s3,s4;
        float ss0,ss1,ss2,ss3;
        int s5;
        s1=a[i];
        s2=a[i]*one_log2;
        s5=(int)s2;
        
        s1=s1-s5*log_2;
        
        s5=1<<s5;
        s2=s1*s1;
        s3=s1*s2;
        s4=s1*s3;
        ss0=xs[0]+s4*xs[1];
        ss1=(xs[2]+s4*xs[3])*s1;
        ss2=(xs[4]+s4*xs[5])*s2;
        ss3=(xs[6]+s4*xs[7])*s3;
        a[i]=s5*(ss0+ss1+ss2+ss3);
        // a[i]=s5;
    }
}