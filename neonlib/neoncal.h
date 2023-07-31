
void neon_add(void *a,void *b,void *c,int num,int w,int type);
void neon_sub(void *a,void *b,void *c,int num,int w,int type);
void neon_mul(void *a,void *b,void *c,int num,int w,int type);//support s8,s16,s32,f32
void neon_mat_mul(void *a,void *b,void *c,int m,int n,int k,int w,int type);
void neon_exp(float *a,float *c,int num);
