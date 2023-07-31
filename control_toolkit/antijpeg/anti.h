
/*定义神经网络参数*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<algorithm>
#define ss 16   //表示每一个块的大小，16表示长宽都为16*8=128个像素
#define MAXSTEP 100 //表示epoh数
#define FILETER_NUM 15 //卷积核的层数
/*输入数据的维数*/
#define INPUT_L 9
#define INPUT_W 11
#define INPUT_H 1

/*结果维数*/
#define out 2

/*卷积层大小*/
#define cov_L 3
#define cov_W 3

float vecs_train[200000][9][11], vecs_test[200000][9][11];
int labels_train[200000], labels_test[200000];
int cnt_train = 0, cnt_test = 0;
int block_width;

float alpha;
struct ImgArr
{
    float* Img;
};
struct conLayer
{
    // int L, W, H;
    // float m[11][13][15];     // 值
    // float b[11][13][15];     // bias
    // float delta[11][13][15]; // 变化值?
    int L,W;
    float m[INPUT_L][INPUT_W];     // 值
} conLayer;
struct Input_Layer
{
    int L, W;
    float m[INPUT_L][INPUT_W];     // 值
    // float b[INPUT_L][INPUT_W];     // bias
    // float delta[INPUT_L][INPUT_W]; // 变化值?
};
struct Conv_Layer
{
    int L, W, H;
    float m[FILETER_NUM][INPUT_L-cov_L+1][INPUT_W-cov_W+1];     // 值
    float b[FILETER_NUM][INPUT_L-cov_L+1][INPUT_W-cov_W+1];     // bias
    float delta[FILETER_NUM][INPUT_L-cov_L+1][INPUT_W-cov_W+1]; // 变化值?
};
struct Pool_Layer
{
    int L, W, H;
    float m[FILETER_NUM][(INPUT_L-cov_L+1)/2][(INPUT_W-cov_W+1)/2];     // 值
    // float b[11][13][15];     // bias
    float delta[FILETER_NUM][(INPUT_L-cov_L+1)/2][(INPUT_W-cov_W+1)/2]; // 变化值?
}pool;
struct fconLayer
{
    int length;
    float m[1000];
    float b[2]; // bias
    float delta[1000];
    float w[out][1000]; // 权重?
} fconLayer;

struct Network
{
    struct Input_Layer Input_layer;
    struct Conv_Layer conv_layer1;
    struct Pool_Layer pool_layer1;
    struct conLayer filter1[FILETER_NUM];
    struct fconLayer fcnn_input;
    struct fconLayer fcnn_w;
    struct fconLayer fcnn_output;
} CNN;


float sigmod(float x)
{
    return 1.0 / (1.0 + exp(-x));
}


float sum(struct Conv_Layer A, int k)
{
    int i, j;
    float a = 0;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            a += A.delta[k][i][j];
    return a;
}

float sum1(struct Conv_Layer A, struct Input_Layer B, int x, int y, int aa)
{
    int i, j;
    float a = 0;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            a += A.delta[aa][i][j] * B.m[i + x][j + y];
    return a;
}
