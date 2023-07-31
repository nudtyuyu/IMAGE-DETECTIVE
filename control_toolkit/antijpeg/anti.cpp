/**************************************************
* File name: anti.cpp
* Author: SnoopyBug(李子腾),Banish(李剑锋)
* Author's blog: 
* Date: Aug 20th, 2022
*
*描述：这是图像篡改检测神经网络训练程序，用于训练神经网络参数
**************************************************/

#include "./neonlib/neoncal.h"
#include "anti.h"
using namespace std;
/*遍历目录下的所有文件*/
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
        if(dirp->d_name[0]=='.')
            continue;
        char newpath[256];
        strcpy(newpath,path);
        strcat(newpath,"/");
        strcat(newpath,dirp->d_name);
        strcat(newpath,"\0");
        getAllFiles(newpath,files);

        files.push_back(newpath);
	}
    closedir(x);
	
}
/*读入训练集的一个文件*/
void readafile_train(string x, int lab)
{
    int z, i, j, k;
    int col, row;
    char s[100];

    int mm = x.length();

    for (i = 0; i < mm; i++)
    {
        s[i] = x[i];
    }
    s[mm] = 0;

    freopen(s, "r", stdin);
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
                vecs_train[cnt_train + i / ss * (col / ss) + j / ss][k][z + 5]+=1.0/64;
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
/*读入测试集的一个文件*/
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
                vecs_test[cnt_test + i / ss * (col / ss) + j / ss][k][z + 5]+=1.0/64;
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
/*读入输入*/
void readdata(string dir, int lab, bool fl)
{
    cout << dir;
    vector<string> files;
    char path[200];
    for(int i=0;i<dir.length();i++)
    {
        path[i]=dir[i];
    }
    path[dir.length()]=0;
    getAllFiles(path, files); //所有文件与文件夹的路径都输出
    int size = files.size();
    int FaiNum = 0;
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        int s = files[i].length();
        // cout << files[i] << "\n";
        if (s >= 5 && files[i][s - 1] == 't' && files[i][s - 2] == 'x' && files[i][s - 3] == 't' && files[i][s - 4] == '.')
        {
            if (!fl)
                readafile_train(files[i], lab);
            else
                readafile_test(files[i], lab);
        }
    }
}
struct Input_Layer CNN_Input(int num, struct Input_Layer A, int flag, ImgArr* img)
{
    A.L = INPUT_L;
    A.W = INPUT_W;
    int i, j, k,t=num*INPUT_L*INPUT_W;
    /*maybe able to optimize*/
    for (i = 0; i < A.L; i++)
    {
        for (j = 0; j < A.W; j++)
        {
            A.m[i][j] = img->Img[t++];
        }
    }
    return A;
}
struct fconLayer Classify_input(struct Pool_Layer A, struct fconLayer B)
{
    int i, j, k;
    int x = 0;
    /*maybe able to optimize*/
    for (k = 0; k < A.H; k++)
        for (i = 0; i < A.L; i++)
            for (j = 0; j < A.W; j++)
                B.m[x++] = sigmod(A.m[k][i][j]);
    B.length = x;
    return B;
}
struct fconLayer softmax(struct fconLayer A)
{
    int i;
    float sum = 0.0;
    float maxx = -100000000;
    /*hard to optimize*/
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
struct fconLayer fcnn_Mul(struct fconLayer A, struct fconLayer B, struct fconLayer C)
{
    // cout<<1;
    int i, j;
    memset(C.m, 0, sizeof(C.m));
    C.length = out;
    
    /*mayble able to optimize*/
    for (i = 0; i < C.length; i++)
    {
        neon_mul((void *)B.w[i],(void *)A.m,(void *)A.w[i],A.length,32,1);
        // cout<<2;
        /*able to optimize in the future*/
        for (j = 0; j < A.length; j++)
        {
            C.m[i] += A.w[i][j];
        }
        C.m[i] += B.b[i];
    }
    return C;
}
float Relu(float x)
{
    return max((float)0.0, x);
}
/*卷积*/
struct Conv_Layer conv(struct Input_Layer A, struct conLayer B[], int number, struct Conv_Layer C)
{
    int i, j, k, a, b, num;
    memset(C.m, 0, sizeof(C.m));

    // // cout<<number<<" "<<C.L<<" "<<C.W<<" "<<B[0].L<<" "<<B[0].W<<" "<<A.H<<"\n";/*15 7 9 3 3 1*/
    for (num = 0; num < number; num++)
    {
        neon_mul((void*)A.m,(void*)B[num].m,(void *)conLayer.m,INPUT_L*INPUT_W,32,1);
        for(i=0;i<C.L;i++)
            for(j=0;j<C.W;j++)
            {
                // C.m[num][i][j]
                // for (b = 0; b < B[0].W; b++)
                //     C.m[i][j][num] += C.m[num][i][j + b];
                C.m[num][i][j]=0;
                /*maybe able to optimize*/
                for (a = 0; a < B[0].L; a++)
                    for (b = 0; b < B[0].W; b++)
                            C.m[num][i][j] += conLayer.m[i + a][j + b];
                C.m[num][i][j] = Relu(C.m[num][i][j] + C.b[num][i][j]);
            }

    }
    //     for (i = 0; i < C.L; i++)
    //         for (j = 0; j < C.W; j++)
    //         {
    //             for (a = 0; a < B[0].L; a++)
    //                 for (b = 0; b < B[0].W; b++)

    //                         C.m[i][j][num] += A.m[i + a][j + b] * B[num].m[a][b];
    //             C.m[i][j][num] = Relu(C.m[i][j][num] + C.b[i][j][num]);
    //         }
    return C;
}

/*池化，平均池化，和函数名字不符*/
struct Pool_Layer maxpooling(struct Conv_Layer conv_layer, struct Pool_Layer A)
{
    int i, j, k;
    /*maybe able to optimize*/
    for (k = 0; k < A.H; k++)
        for (i = 0; i < A.L; i ++)
            for (j = 0; j < A.W; j++)
                // A.m[i / 2][j / 2][k] = (conv_layer.m[i][j][k] + conv_layer.m[i + 1][j][k] + conv_layer.m[i][j + 1][k], conv_layer.m[i + 1][j + 1][k]) / 4.0;
                A.m[k][i][j] = (conv_layer.m[k][2*i][2*j] + conv_layer.m[k][2*i + 1][2*j] + conv_layer.m[k][2*i][2*j + 1] + conv_layer.m[k][2*i + 1][2*j + 1]) / 4.0;
    return A;
}

void forward_propagation(int num, int flag, ImgArr* Img, int *labels) //做一次前向输出
{
    int i;
    CNN.Input_layer = CNN_Input(num, CNN.Input_layer, flag, Img);
    CNN.conv_layer1 = conv(CNN.Input_layer, CNN.filter1, 15, CNN.conv_layer1);
    // cout<<CNN.conv_layer1.L<<" "<<CNN.conv_layer1.W<<" "<<CNN.conv_layer1.H<<"\n";
    CNN.pool_layer1 = maxpooling(CNN.conv_layer1, CNN.pool_layer1);/*no pool_layer*/
    CNN.fcnn_input = Classify_input(CNN.pool_layer1, CNN.fcnn_input);
    // cout<<CNN.fcnn_input.length<<"ss\n";
    // cout<<"sss";
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

struct conLayer init1(struct conLayer A)
{
    int i, j, k;
    /*unclear to optimize*/
    for (i = 0; i < INPUT_L; i++)
    {
        for (j = 0; j < INPUT_W; j++)
        {
            A.m[i][j] = 0.01 * (rand() % 100);

        }
    }

    return A;
};

/*神经网络初始化函数*/
void init()
{
    int i,j;
    for(i=0;i<out;i++)
        for(j=0;j<1000;j++)
            CNN.fcnn_w.w[i][j];
    for (i = 0; i < FILETER_NUM; i++)
    {
        CNN.filter1[i].L = cov_L;
        CNN.filter1[i].W = cov_W;
        CNN.filter1[i] = init1(CNN.filter1[i]);
    }
    CNN.conv_layer1.L = INPUT_L - cov_L + 1;
    CNN.conv_layer1.W = INPUT_W - cov_W + 1;
    CNN.conv_layer1.H = FILETER_NUM;

    CNN.pool_layer1.L = CNN.conv_layer1.L / 2;
    CNN.pool_layer1.W = CNN.conv_layer1.W / 2;
    CNN.pool_layer1.H = CNN.conv_layer1.H;
}
struct Pool_Layer pool_input(struct Pool_Layer A, struct fconLayer B)
{
    int i, j, k;
    int x = 1;
     /*maybe able to optimize*/
    for (k = 0; k < A.H; k++)
        for (i = 0; i < A.L; i++)
            for (j = 0; j < A.W; j++)
                A.delta[k][i][j] = B.delta[x++];
            
    return A;
}
struct conLayer Update(struct conLayer A, struct Input_Layer B, struct Conv_Layer C, int aa)
{
    int i, j, k;
    for (i = 0; i < A.L; i++)
        for (j = 0; j < A.W; j++)
        {
            A.m[i][j] -= alpha * sum1(C, B, i, j, aa);
            C.b[aa][i][j] -= alpha * sum(C, aa);
            // cout<<aa<<" "<<C.b[aa][i][j]<<" "<<alpha*sum(C,aa)<<"\n";
        }
    return A;
}

struct Conv_Layer pool_delta(struct Conv_Layer A, struct Pool_Layer B)
{
    int i, j, k;
    // float *aa[][] =   pool.delta; // 5 5 7
    // float aa[A.H][A.L][A.W];
    /*hard to optimize*/
    // cout<<A.H<<" "<<A.L<<" "<<A.W<<endl;
    for (i = 0; i < A.H; i++)
    {
        for (j = 0; j < A.L; j += 2)
        {
            for (k = 0; k < A.W; k += 2)
            {
                pool.delta[i][j][k] = B.delta[i][j / 2][k / 2] / 4.0;
                pool.delta[i][j + 1][k] = B.delta[i][j / 2][k / 2] / 4.0;
                pool.delta[i][j][k + 1] = B.delta[i][j / 2][k / 2] / 4.0;
                pool.delta[i][j + 1][k + 1] = B.delta[i][j / 2][k / 2] / 4.0;
                // cout<<pool.delta[i][j][k]<<" "<<pool.delta[i][j + 1][k]<<" "<<pool.delta[i][j][k + 1]<<" "<<pool.delta[i][j + 1][k + 1]<<endl;
            }
        }
    }
     /*maybe able to optimize*/
    for (k = 0; k < A.H; k++)
        for (i = 0; i < A.L; i++)
        {
            for (j = 0; j < A.W; j++)
            {
                // cout<<A.m[k][i][j]<<endl;
                if (A.m[k][i][j] < 0)
                    A.delta[k][i][j] = 0;
                else
                    A.delta[k][i][j] = A.m[k][i][j] * pool.delta[k][i][j];
            }
        }
    // funcao_free(aa, A.W + 1, A.L + 1);
    return A;
}

void back_propagation() //反向传播
{
    int i, j;
    memset(CNN.fcnn_input.delta, 0, sizeof(CNN.fcnn_input.delta));
    /*unclear how to optimize*/
    // cout<<CNN.fcnn_input.length<<"\n";
    
    for (j = 0; j < out; j++)
    {
        for (i = 0; i < CNN.fcnn_input.length; i++)
        {
        
            CNN.fcnn_input.delta[i] += CNN.fcnn_input.m[i] * (1.0 - CNN.fcnn_input.m[i]) * CNN.fcnn_w.w[j][i] * CNN.fcnn_output.delta[j];
            // cout<<i<<" "<<j<<" "<<CNN.fcnn_input.delta[i]<<endl;
        }
    }
    for (j = 0; j < out; j++)
    {
        // cout<<CNN.fcnn_output.delta[j]<<"\n";
        for (i = 0; i < CNN.fcnn_input.length; i++)
        {
        
            CNN.fcnn_w.w[j][i] -= alpha * CNN.fcnn_output.delta[j] * CNN.fcnn_input.m[i];
            CNN.fcnn_w.b[j] -= alpha * CNN.fcnn_output.delta[j];
            // cout<<CNN.fcnn_w.w[j][i]<<" "<<alpha * CNN.fcnn_output.delta[j] * CNN.fcnn_input.m[i]<<"\n";
            // cout<<CNN.fcnn_w.b[j]<<" "<<alpha * CNN.fcnn_output.delta[j]<<"\n";
        }
    }
    
    
    CNN.pool_layer1 = pool_input(CNN.pool_layer1, CNN.fcnn_input);
    
    CNN.conv_layer1 = pool_delta(CNN.conv_layer1, CNN.pool_layer1); // pooling误差传递
    
    for (i = 0; i < 15; i++)
        CNN.filter1[i] = Update(CNN.filter1[i], CNN.Input_layer, CNN.conv_layer1, i);
    
}
void shuffle()
{
    int i, j, k, r;
    float vec_tmp[9][11], label_tmp;
    for (i = 0; i < cnt_train; i++)
    {
        r = rand() % cnt_train;
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
    for (i = 0; i < cnt_test; i++)
    {
        r = rand() % cnt_test;
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

/*记录训练好的网络参数*/
void storecs()
{
    freopen("cs.txt","w",stdout);
    //filter
    int i,j,k;
    for(i=0;i<FILETER_NUM;++i)
    {
        for(j=0;j<INPUT_L;++j)
        {
            for(k=0;k<INPUT_W;++k)
            {
                printf("%f ",CNN.filter1[i].m[j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
    //conv_layer
    for(i=0;i<FILETER_NUM;++i)
    {
        for(j=0;j<INPUT_L;++j)
        {
            for(k=0;k<INPUT_W;++k)
            {
                printf("%f ",CNN.conv_layer1.b[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
    //fcnn_w
    for(i=0;i<out;i++)
    {
        for(j=0;j<180;j++)
            printf("%f ",CNN.fcnn_w.w[i][j]);
        printf("\n");
    }

    //fcnn_b
    for(i=0;i<out;i++)
    {
        printf("%f\n",CNN.fcnn_w.b[i]);
    }
    fclose(stdout);
}

int main()
{
    srand((unsigned)(time(NULL)));
    init();//初始化神经网络参数
    readdata("TEST-text0_train", 0, 0); //      第二个参数: 0->没有双压缩  第三个参数：0->train
    readdata("TEST-text1_train", 1, 0);
    readdata("TEST-text0_test", 0, 1); //
    readdata("TEST-text1_test", 1, 1);
    shuffle();
    ImgArr imgarr1,imgarr2;
    imgarr1.Img=(float*)vecs_train;
    imgarr2.Img=(float*)vecs_test;
    int step,i,j;
    for(step=0;step<MAXSTEP;step++)//迭代MAXSTEP次
    {
        alpha = 0.005 / pow(2, (step / 10));
        float err = 0;
        for (i = 0; i < cnt_train; i++)
        {
            // cout<<"ww\n";
            forward_propagation(i, 0, &imgarr1, labels_train);//前向计算
            // cout<<1;
            err -= log(CNN.fcnn_output.m[(int)labels_train[i]]);//计算error
            // printf("%d",1);
            back_propagation();//反向传播
        }

        int sum = 0;
        for (j = 0; j < cnt_test; j++)//用测试集测试网络准确度
        {
            forward_propagation(j, 1, &imgarr2, labels_test);
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
            int label = (int)(labels_test[j]);
            if (ans1 == label)
                sum++;
        }
        printf("epoch %d    \taccuracy %.3f%%\tloss %.5f\n", step + 1, 100.0 * sum / cnt_test, 1.0 * err / cnt_train);
    }
    storecs();//记录网络参数
    return 0;
}
