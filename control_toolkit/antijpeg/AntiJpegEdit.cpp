/**************************************************
* File name: AntiJpegEdit.cpp
* Author: SnoopyBug(李子腾),Banish(李剑锋)
* Author's blog: 
* Date: Aug 20th, 2022
*
*描述：未优化版本的神经网络训练函数
**************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "AntiJpegEdit.h"
#include <vector>
// #include <windows.h>
// #include <tchar.h>
// #include <io.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
// #define N_TRAIN 10
// #define N_TEST 10
// #define N_BLOCK 4
// #define WIDTH_FIG 138
// #define HEIGHT_FIG 139

using namespace std;
//* ############################ 加油锋锋

int N_TRAIN_fig, N_TEST_fig, N_TRAIN, N_TEST;

// float data_train[N_TRAIN_fig][N_BLOCK][64], data_test[N_TEST_fig][N_BLOCK][64];
// int label_data_train[N_TRAIN][N_BLOCK], label_data_test[N_TEST][N_BLOCK];

float vecs_train[200000][9][11], vecs_test[200000][9][11];
int labels_train[200000], labels_test[200000];

int cnt_train = 0, cnt_test = 0;
int ss = 0;
int block_width;

// void getAllFiles(string path, vector<string> &files)
// {
//     //文件句柄
//     long hFile = 0;
//     //文件信息
//     struct _finddata_t fileinfo; //很少用的文件信息读取结构
//     string p;                    // string类很有意思的一个赋值函数:assign()，有很多重载版本
//     if ((hFile = _findfirst(p.assign(path).append("\\*.*").c_str(), &fileinfo)) != -1)
//     {
//         do
//         {
//             if ((fileinfo.attrib & _A_SUBDIR)) //判断是否为文件夹
//             {
//                 if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//                 {
//                     files.push_back(p.assign(path).append("/").append(fileinfo.name));    //保存文件夹名字
//                     getAllFiles(p.assign(path).append("/").append(fileinfo.name), files); //递归当前文件夹
//                 }
//             }
//             else //文件处理
//             {
//                 files.push_back(p.assign(path).append("/").append(fileinfo.name)); //文件名
//             }
//         } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
//         _findclose(hFile);
//     }
//     else
//     {
//         printf("Failed(%d)\n", GetLastError());
//     }
// }

void getAllFiles(char *path, vector<string>& files)
{
	DIR * x=opendir(path);
    if(x==NULL)
    {
        files.push_back(path);
        return;
    }
	struct dirent *dirp;
	while(dirp=readdir(x))
	{
		
		// printf("%s %c\n",dirp->d_name,dirp->d_type);
		// cout<<dirp->d_type<<endl;
		// cout<<dirp->d_name<<endl;
        
        // struct stat s_buf;
        // stat(dirp->d_name,&s_buf);
        // if(S_ISDIR(s_buf.st_mode))
        // {
            if(dirp->d_name[0]=='.')
            continue;
            char newpath[256];
            strcpy(newpath,path);
            strcat(newpath,"/");
            strcat(newpath,dirp->d_name);
            strcat(newpath,"\0");
            // cout<<newpath<<endl;
            getAllFiles(newpath,files);
        // }
        // else
        files.push_back(newpath);
        // ;
	}
    closedir(x);
	
}
void readafile_train(string x, int lab)
{
    int z, i, j, k;
    int col, row;
    char s[100];
    // cout << x << endl;
    // exit(0);
    //  * 读取0(single)
    //  train
    // sprintf(s, "%s", x);
    int mm = x.length();
    // cout << s;
    // exit(0);
    for (i = 0; i < mm; i++)
    {
        s[i] = x[i];
    }
    s[mm] = 0;
    // cout << s;
    // exit(0);
    freopen(s, "r", stdin);
    // row = 222, col = 184;
    scanf("%d%d", &row, &col);
    // cout << row << " " << col << "\n";
    row = row, col = col;
    for (i = 0; i < row / ss * ss; i++)
    {
        for (j = 0; j < col / ss * ss; j++)
            for (k = 0; k < 9; k++)
            {
                scanf("%d", &z);
                if (z > 5 || z < -5)
                    continue;
                vecs_train[cnt_train + i / ss * (col / ss) + j / ss][k][z + 5]++;
                labels_train[cnt_train + i / ss * (col / ss) + j / ss] = lab;
            }
        for (j = col / ss * ss; j < col; j++)
        {
            for (k = 0; k < 9; k++)
                scanf("%d", &z);
        }
    }
    fclose(stdin);
    cnt_train += row / ss * (col / ss);
    // cout << cnt_train << "\n";
}
void readafile_test(string x, int lab)
{
    int z, i, j, k;
    int col, row;
    char s[100];
    // cout << x << endl;
    // exit(0);
    //  * 读取0(single)
    //  train
    // sprintf(s, "%s", x);
    int mm = x.length();
    // cout << s;
    // exit(0);
    for (i = 0; i < mm; i++)
    {
        s[i] = x[i];
    }
    s[mm] = 0;
    // cout << s;
    // exit(0);
    freopen(s, "r", stdin);
    // row = 222, col = 184;
    scanf("%d%d", &row, &col);
    row = row, col = col;
    for (i = 0; i < row / ss * ss; i++)
    {
        for (j = 0; j < col / ss * ss; j++)
            for (k = 0; k < 9; k++)
            {
                scanf("%d", &z);
                if (z > 5 || z < -5)
                    continue;
                vecs_test[cnt_test + i / ss * (col / ss) + j / ss][k][z + 5]++;
                labels_test[cnt_test + i / ss * (col / ss) + j / ss] = lab;
            }
        for (j = col / ss * ss; j < col; j++)
        {
            for (k = 0; k < 9; k++)
                scanf("%d", &z);
        }
    }
    fclose(stdin);
    cnt_test += row / ss * (col / ss);
    // cout << cnt_train << "\n";
}
void readdata(string dir, int lab, bool fl)
{
    cout << dir;
    // SetThreadLocale(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_UNICODE));
    // printf("_________Start Test_________\n");
    // string DATA_DIR = "C:/Users/DELL/Desktop/ATEC";
    vector<string> files;
    //测试
    // char DistAll[] = {"AllFiles.txt"};
    // string dir="";//文件目录，自己填
    char path[200];
    for(int i=0;i<dir.length();i++)
    {
        path[i]=dir[i];
    }
    path[dir.length()]=0;
    getAllFiles(path, files); //所有文件与文件夹的路径都输出
    // ofstream ofn(DistAll);  //输出文件流
    int size = files.size();
    int FaiNum = 0;
    cout << size << endl;
    //  cout << "Get Files Nums:" << size << endl;
    //  cout.clear();
    // exit(0);
    for (int i = 0; i < size; i++)
    {
        // cout << files[i] << endl;
        // cout << i << "\n";
        int s = files[i].length();
        // cout << files[i] << "\n";
        if (s >= 5 && files[i][s - 1] == 't' && files[i][s - 2] == 'x' && files[i][s - 3] == 't' && files[i][s - 4] == '.')
        {
            // cout << files[i] << "\n";
            if (!fl)
                readafile_train(files[i], lab);
            else
                readafile_test(files[i], lab);
        }
    }
}
// int main()
// {
//     readdata("/mnt/hgfs/飞腾/MSTAR官方数据/jpg/MSTAR_PUBLIC_CLUTTER_CD1/CLUTTER/1",0,0);
    // readdata("jpg",0,0);
//     // printf("1");
//     test();
//     // fopen(stdout);
//     printf("1");
//     // readafile(6158);
//     // readafile(6159);
//     // readafile(6160);
//     // readafile(6161);
//     return 0;
// }
// //* ############################ 锋锋加油

// 读入图像
ImgArr read_Vec(float vecs[][9][11], int n_vec)
{
    // 图像数组的初始化
    ImgArr imgarr = (ImgArr)malloc(sizeof(MinstImg));
    imgarr->ImgNum = n_vec;
    imgarr->ImgPtr = (MinstImg *)malloc(n_vec * sizeof(MinstImg));

    int i, r, c;
    for (i = 0; i < n_vec; ++i)
    {
        imgarr->ImgPtr[i].r = 9;
        imgarr->ImgPtr[i].c = 11;
        imgarr->ImgPtr[i].ImgData = (float **)malloc(9 * sizeof(float *));
        for (r = 0; r < 9; ++r)
        {
            imgarr->ImgPtr[i].ImgData[r] = (float *)malloc(11 * sizeof(float));
            for (c = 0; c < 11; ++c)
            {
                // printf("%.2f->%.2f\t", imgarr->ImgPtr[i].ImgData[r][c] ,vecs[i][r][c]);
                imgarr->ImgPtr[i].ImgData[r][c] = vecs[i][r][c] / 64;
            }
        }
    }

    return imgarr;
}

// 读入标签
LabelArr read_Label(int labels[], int n_label)
{
    int label_long = 2;
    // 图像标记数组的初始化
    LabelArr labarr = (LabelArr)malloc(sizeof(MinstLabel));
    labarr->LabelNum = n_label;
    labarr->LabelPtr = (MinstLabel *)malloc(n_label * sizeof(MinstLabel));

    int i;
    for (i = 0; i < n_label; ++i)
    {
        labarr->LabelPtr[i].l = 2;
        labarr->LabelPtr[i].LabelData = (float *)calloc(label_long, sizeof(float));
        int temp = labels[i];
        labarr->LabelPtr[i].LabelData[temp] = 1.0;
    }

    return labarr;
}

void lzt_init(int N_TRAIN)
{
    int i, j, k;
    for (i = 0; i < N_TRAIN; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 11; k++)
            {
                if (!(i % 4))
                {
                    vecs_train[i][j][k] = 1;
                    labels_train[i] = 1;

                    vecs_test[i][j][k] = 1;
                    labels_test[i] = 1;
                }
                else
                {
                    vecs_train[i][j][k] = 0;
                    labels_train[i] = 0;

                    vecs_test[i][j][k] = 0;
                    labels_test[i] = 0;
                }
            }
        }
    }
}
//
//
//
//
//
//
//
//
// main.c

#include <time.h>
#include <stdbool.h>
#define max(a, b) ((a > b) ? a : b)
const int out = 2;
float alpha; // learning rate
ImgArr trainImg;
ImgArr testImg;
// float labels[60000];
// float labels1[10000];

// 卷积层
struct conLayer
{
    int L, W, H;
    float m[11][13][15];     // 值
    float b[11][13][15];     // bias
    float delta[11][13][15]; // 变化值?
} conLayer;

struct conLayer init1(struct conLayer A)
{
    int i, j, k;
    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 13; j++)
        {
            for (k = 0; k < 15; k++)
            {
                A.m[i][j][k] = 0.01 * (rand() % 100);
            }
        }
    }

    return A;
};

// 全连接层
struct fconLayer
{
    int length;
    float m[1000];
    float b[1000]; // bias
    float delta[1000];
    float w[20][1000]; // 权重?
} fconLayer;

struct fconLayer init2(struct fconLayer A)
{
    int i, j, k;
    for (i = 0; i < 20; i++)
        for (j = 0; j < 1000; j++)
            A.w[i][j] = 0.01 * (rand() % 100);
    return A;
}

struct Network
{
    struct conLayer Input_layer;
    struct conLayer conv_layer1;
    struct conLayer pool_layer1;
    struct conLayer filter1[15];
    struct fconLayer fcnn_input;
    struct fconLayer fcnn_w;
    struct fconLayer fcnn_output;
} CNN;

void init()
{
    int i;
    CNN.Input_layer = init1(CNN.Input_layer);
    // printf("%f\n", CNN.Input_layer.m[0][0][0]);
    CNN.conv_layer1 = init1(CNN.conv_layer1);
    CNN.pool_layer1 = init1(CNN.pool_layer1);
    for (i = 0; i < 15; i++)
        CNN.filter1[i] = init1(CNN.filter1[i]);
    CNN.fcnn_input = init2(CNN.fcnn_input);
    CNN.fcnn_w = init2(CNN.fcnn_w);
    CNN.fcnn_output = init2(CNN.fcnn_output);
}

float Relu(float x)
{
    return max(0.0, x);
}

struct fconLayer softmax(struct fconLayer A)
{
    int i;
    float sum = 0.0;
    float maxx = -100000000;
    for (i = 0; i < out; i++)
        maxx = max(maxx, A.m[i]);
    for (i = 0; i < out; i++)
        sum += exp(A.m[i] - maxx);
    for (i = 0; i < out; i++)
    {
        A.m[i] = exp(A.m[i] - maxx) / sum;
    }
    return A;
}

float sigmod(float x)
{
    return 1.0 / (1.0 + exp(-x));
}

float sum(struct conLayer A, int k)
{
    int i, j;
    float a = 0;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            a += A.delta[i][j][k];
    return a;
}

float sum1(struct conLayer A, struct conLayer B, int x, int y, int aa)
{
    int i, j;
    float a = 0;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            a += A.delta[i][j][aa] * B.m[i + x][j + y][0];
    return a;
}

struct conLayer Update(struct conLayer A, struct conLayer B, struct conLayer C, int aa)
{
    int i, j, k;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            for (k = 0; k < A.H; k++)
            {
                A.m[i][j][k] -= alpha * sum1(C, B, i, j, aa);
                C.b[i][j][k] -= alpha * sum(C, aa);
                // cout<<aa<<" "<<C.b[i][j][k]<<" "<<alpha*sum(C,aa)<<"\n";
            }
    return A;
}

// 将像素值读入网络输入层
struct conLayer CNN_Input(int num, struct conLayer A, int flag, ImgArr Img)
{
    A.L = 9;
    A.W = 11;
    A.H = 1;
    int i, j, k;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 11; j++)
        {
            for (k = 0; k < 1; k++)
            {
                if (flag == 0)
                {
                    A.m[i][j][k] = Img->ImgPtr[num].ImgData[i][j];
                }
                else
                {
                    A.m[i][j][k] = Img->ImgPtr[num].ImgData[i][j];
                }
            }
        }
    }
    return A;
}

// 卷积操作，A为输入，B为num维卷积核，C为输出
struct conLayer conv(struct conLayer A, struct conLayer B[], int number, struct conLayer C)
{
    int i, j, k, a, b, num;
    memset(C.m, 0, sizeof(C.m));
    for (i = 0; i < number; i++)
    {
        B[i].L = B[i].W = 3;
        B[i].H = 1;
    }
    C.L = A.L - B[0].L + 1;
    C.W = A.W - B[0].W + 1;
    C.H = number;
    // cout<<number<<" "<<C.L<<" "<<C.W<<" "<<B[0].L<<" "<<B[0].W<<" "<<A.H<<"\n";/*15 7 9 3 3 1*/
    /*able to optimize*/
    for (num = 0; num < number; num++)
        for (i = 0; i < C.L; i++)
            for (j = 0; j < C.W; j++)
            {
                for (a = 0; a < B[0].L; a++)
                    for (b = 0; b < B[0].W; b++)
                        for (k = 0; k < A.H; k++)
                        {
                            C.m[i][j][num] += A.m[i + a][j + b][k] * B[num].m[a][b][k];
                        }
                C.m[i][j][num] = Relu(C.m[i][j][num] + C.b[i][j][num]);
            }
    return C;
}

struct fconLayer Classify_input(struct conLayer A, struct fconLayer B)
{
    int i, j, k;
    int x = 0;
    /*able to optimize*/
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            for (k = 0; k < A.H; k++)
                B.m[x++] = sigmod(A.m[i][j][k]);
    B.length = x;
    return B;
}

struct conLayer pool_input(struct conLayer A, struct fconLayer B)
{
    int i, j, k;
    int x = 1;
     /*maybe able to optimize*/
    //  cout<<A.L<<A.W<<A.H<<endl;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
            for (k = 0; k < A.H; k++)
            {
                A.delta[i][j][k] = B.delta[x++];
            }
    return A;
}
// 三维数组
float ***funcao(int a, int b, int c)
{
    float ***ppp = (float ***)malloc(a * sizeof(float **));
    int i, j, k;
    // Optimized your memory allocation code
    for (i = 0; i < a; i++)
    {
        ppp[i] = (float **)malloc(b * sizeof(float *));
        for (j = 0; j < b; j++)
        {
            ppp[i][j] = (float *)malloc(c * sizeof(float));
        }
    }
    return ppp;
}
void funcao_free(float ***ppp, int a, int b)
{
    int i, j, k;
    // Optimized your memory allocation code
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            free(ppp[i][j]);
        }
        free(ppp[i]);
    }
    free(ppp);
}
// 以上：三维数组
struct conLayer pool_delta(struct conLayer A, struct conLayer B)
{
    int i, j, k;
    float ***aa = funcao(A.L + 1, A.W + 1, A.H); // 5 5 7
    // float aa[A.H][A.L][A.W];
    /*hard to optimize*/
    // cout<<A.H<<" "<<A.W<<" "<<A.L<<endl;
    for (i = 0; i < A.H; i++)
    {
        for (j = 0; j < A.L; j += 2)
        {
            for (k = 0; k < A.W; k += 2)
            {
                aa[j][k][i] = B.delta[j / 2][k / 2][i] / 4.0;
                aa[j + 1][k][i] = B.delta[j / 2][k / 2][i] / 4.0;
                aa[j][k + 1][i] = B.delta[j / 2][k / 2][i] / 4.0;
                aa[j + 1][k + 1][i] = B.delta[j / 2][k / 2][i] / 4.0;
                // cout<<aa[j][k][i]<<" "<<aa[j + 1][k][i]<<" "<<aa[j][k + 1][i]<<" "<<aa[j + 1][k + 1][i]<<endl;
            }
        }
    }
     /*maybe able to optimize*/
    for (k = 0; k < A.H; k++)
        for (i = 0; i < A.L; i++)
        {
            for (j = 0; j < A.W; j++)
            {
                // cout<<A.m[i][j][k]<<endl;
                if (A.m[i][j][k] < 0)
                    A.delta[i][j][k] = 0;
                else
                    A.delta[i][j][k] = A.m[i][j][k] * aa[i][j][k];
            }
        }
    funcao_free(aa, A.L + 1, A.W + 1);
    return A;
}

// 最大池化层sigmod
struct conLayer maxpooling(struct conLayer conv_layer, struct conLayer A)
{
    int i, j, k;
    A.L = conv_layer.L / 2;
    A.W = conv_layer.W / 2;
    A.H = conv_layer.H;
    /*maybe able to optimize*/
    for (k = 0; k < conv_layer.H; k++)
        for (i = 0; i < conv_layer.L; i += 2)
            for (j = 0; j < conv_layer.W; j += 2)
                // A.m[i / 2][j / 2][k] = (conv_layer.m[i][j][k] + conv_layer.m[i + 1][j][k] + conv_layer.m[i][j + 1][k], conv_layer.m[i + 1][j + 1][k]) / 4.0;
                A.m[i / 2][j / 2][k] = (conv_layer.m[i][j][k] + conv_layer.m[i + 1][j][k] + conv_layer.m[i][j + 1][k] + conv_layer.m[i + 1][j + 1][k]) / 4.0;
    return A;
}

struct fconLayer fcnn_Mul(struct fconLayer A, struct fconLayer B, struct fconLayer C)
{
    int i, j;
    memset(C.m, 0, sizeof(C.m));
    C.length = out;

    /*mayble able to optimize*/
    for (i = 0; i < C.length; i++)
    {
        for (j = 0; j < A.length; j++)
        {
            C.m[i] += B.w[i][j] * A.m[j];
        }
        C.m[i] += B.b[i];
    }
    return C;
}

void forward_propagation(int num, int flag, ImgArr Img, float *labels) //做一次前向输出
{
    int i;
    CNN.Input_layer = CNN_Input(num, CNN.Input_layer, flag, Img);
    CNN.conv_layer1 = conv(CNN.Input_layer, CNN.filter1, 15, CNN.conv_layer1);
    // printf("H:%d    L:%d    W:%d", CNN.conv_layer1.H, CNN.conv_layer1.L, CNN.conv_layer1.W);
    CNN.pool_layer1 = maxpooling(CNN.conv_layer1, CNN.pool_layer1);
    CNN.fcnn_input = Classify_input(CNN.pool_layer1, CNN.fcnn_input);//biaozhunhua
    CNN.fcnn_output = fcnn_Mul(CNN.fcnn_input, CNN.fcnn_w, CNN.fcnn_output);
    CNN.fcnn_output = softmax(CNN.fcnn_output); 
     /*hard to optimize*/
    for (i = 0; i < out; i++)
    {
        if (i == (int)labels[num])
            CNN.fcnn_output.delta[i] = CNN.fcnn_output.m[i] - 1.0;
        else
            CNN.fcnn_output.delta[i] = CNN.fcnn_output.m[i];
    }
}

void back_propagation() //反向传播
{
    int i, j;
    memset(CNN.fcnn_input.delta, 0, sizeof(CNN.fcnn_input.delta));
    /*unclear how to optimize*/
    for (i = 0; i < CNN.fcnn_input.length; i++)
    {
        for (j = 0; j < out; j++)
        {
            CNN.fcnn_input.delta[i] += CNN.fcnn_input.m[i] * (1.0 - CNN.fcnn_input.m[i]) * CNN.fcnn_w.w[j][i] * CNN.fcnn_output.delta[j];
        }
    }
    for (j = 0; j < out; j++)
    {
        // cout<<CNN.fcnn_output.delta[j]<<endl;
        for (i = 0; i < CNN.fcnn_input.length; i++)
        {
        
            
            CNN.fcnn_w.w[j][i] -= alpha * CNN.fcnn_output.delta[j] * CNN.fcnn_input.m[i];
            CNN.fcnn_w.b[j] -= alpha * CNN.fcnn_output.delta[j];
        }
    }

    CNN.pool_layer1 = pool_input(CNN.pool_layer1, CNN.fcnn_input);
    CNN.conv_layer1 = pool_delta(CNN.conv_layer1, CNN.pool_layer1); // pooling误差传递
    for (i = 0; i < 15; i++)
        CNN.filter1[i] = Update(CNN.filter1[i], CNN.Input_layer, CNN.conv_layer1, i);
}

void test(ImgArr imgarr, LabelArr labarr)
{
    int i, j, k;
    freopen("lzt.txt", "w", stdout);
    for (i = 0; i < 6; i++)
    {
        printf("%.2f %.2f \n", labarr->LabelPtr[i].LabelData[0], labarr->LabelPtr[i].LabelData[1]);
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 11; k++)
                printf("%.2f ", imgarr->ImgPtr[i].ImgData[j][k]);
            printf("\n");
        }
        printf("\n");
    }
    for (i = 621; i < 624; i++)
    {
        printf("%.2f %.2f \n", labarr->LabelPtr[i].LabelData[0], labarr->LabelPtr[i].LabelData[1]);
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 11; k++)
                printf("%.2f ", imgarr->ImgPtr[i].ImgData[j][k]);
            printf("\n");
        }
        printf("\n");
    }
    // fclose(stdout);
}

void shuffle()
{
    int i, j, k, r;
    float vec_tmp[9][11], label_tmp;
    for (i = 0; i < N_TRAIN; i++)
    {
        r = rand() % N_TRAIN;
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 11; k++)
            {
                vec_tmp[j][k] = vecs_train[i][j][k];
                vecs_train[i][j][k] = vecs_train[r][j][k];
                vecs_train[r][j][k] = vec_tmp[j][k];

                label_tmp = labels_train[i];
                labels_train[i] = labels_train[r];
                labels_train[r] = label_tmp;
            }
        }
    }
    for (i = 0; i < N_TEST; i++)
    {
        r = rand() % N_TEST;
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 11; k++)
            {
                vec_tmp[j][k] = vecs_test[i][j][k];
                vecs_test[i][j][k] = vecs_test[r][j][k];
                vecs_test[r][j][k] = vec_tmp[j][k];

                label_tmp = labels_test[i];
                labels_test[i] = labels_test[r];
                labels_test[r] = label_tmp;
            }
        }
    }
}

int main()
{
    // string dir1,dir2;
    // readdata("jpg", 0, 0);
    // exit(0);
    // alpha = 0.005;
    srand((unsigned)(time(NULL)));
    init();

    ss = 32;
    readdata("./control_toolkit/antijpeg/TEST-text0_train", 0, 0); //      第二个参数: 0->没有双压缩  第三个参数：0->train
    readdata("./control_toolkit/antijpeg/TEST-text1_train", 1, 0);
    readdata("./control_toolkit/antijpeg/TEST-text0_test", 0, 1); //
    readdata("./control_toolkit/antijpeg/TEST-text1_test", 1, 1);
    // lzt_init(cnt = 62100);

    N_TRAIN = cnt_train;
    N_TEST = cnt_test;
    shuffle();
    // N_TRAIN /= 100;
    // N_TEST /= 1000;

    ImgArr trainImg = read_Vec(vecs_train, N_TRAIN);
    LabelArr trainLabel = read_Label(labels_train, N_TRAIN);
    ImgArr testImg = read_Vec(vecs_test, N_TEST);
    LabelArr testLabel = read_Label(labels_test, N_TEST);
    // ImgArr testImg = read_Vec(vecs_train, N_TRAIN);
    // LabelArr testLabel = read_Label(labels_train, N_TRAIN);

    printf("trainLabel->LabelNum: %d\n", trainLabel->LabelNum);
    // test(trainImg, trainLabel);
    // printf("PASS~\n");

    int i, j;
    float *labels = (float *)malloc(sizeof(float) * trainLabel->LabelNum);
    // float labels[trainLabel->LabelNum];
    for (i = 0; i < trainLabel->LabelNum; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (trainLabel->LabelPtr[i].LabelData[j] == 1.0)
            {
                labels[i] = (float)j;
                // printf("%.1f  ", labels[i]);
            }
        }
    }
    float *labels1 = (float *)malloc(sizeof(float) * testLabel->LabelNum);
    // float labels1[testLabel->LabelNum];
    for (i = 0; i < testLabel->LabelNum; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (testLabel->LabelPtr[i].LabelData[j] == 1.0)
            {
                labels1[i] = (float)j;
                // printf("%.1f  ", labels1[i]);
            }
        }
    }

    int step;
    for (step = 0; step < 100; step++)
    {
        alpha = 0.005 / pow(2, (step / 10));

        float err = 0;
        for (i = 0; i < N_TRAIN; i++)
        {
            forward_propagation(i, 0, trainImg, labels);
            err -= log(CNN.fcnn_output.m[(int)labels[i]]);
            back_propagation();
        }
        // printf("\nconvdelta:\n");
        // for (int m = 0; m < 24; m++)
        //     for (int n = 0; n < 24; n++)
        //         printf("%f\t", CNN.conv_layer1.delta[m][n][0]);
        // printf("\n convll:\n");

        // for (int m = 0; m < 5; m++)
        //     for (int n = 0; n < 5; n++)
        //         printf("%f\t", CNN.filter1[0].m[m][n][0]);
        // printf("step: %d\tloss:%.5f\n", time, 1.0 * err / trainN); //每次记录一遍数据集的平均误差
        int sum = 0;
        for (j = 0; j < N_TEST; j++)
        {
            forward_propagation(j, 1, testImg, labels1);
            int ans = -1;
            float sign = -1;
            for (i = 0; i < out; i++)
            {
                if (CNN.fcnn_output.m[i] > sign)
                {
                    sign = CNN.fcnn_output.m[i];
                    ans = i;
                }
            }
            int ans1 = ans;
            int label = (int)(labels1[j]);
            if (ans1 == label)
                sum++;
        }

        // printf("\n");
        // printf("sum:%d\n", sum);
        printf("epoch %d    \taccuracy %.3f%%\tloss %.5f\n", step + 1, 100.0 * sum / N_TEST, 1.0 * err / N_TRAIN);
    }
    return 0;
}
