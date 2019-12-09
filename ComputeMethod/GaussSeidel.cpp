/*
*使用高斯-赛德尔迭代法解下列方程组
* 10*x1 - x2 - 2*x3 = 7.2
* -x1 + 10*x2 - 2*x3 = 8.3
* -x1 - x2 + 5*x3 = 4.2
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

#define MAXSIZE 50

double CoeA[MAXSIZE][MAXSIZE];      //系数矩阵
double ResY[MAXSIZE];       //每个等式结果值数组
double result[MAXSIZE];     //结果向量

//输入增广矩阵
void input(double CoeA[MAXSIZE][MAXSIZE], double ResY[MAXSIZE], long n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>CoeA[i][j];    //输入系数
        }
        cin>>ResY[i];       //输入结果值
    }
}

int main()
{
    long n;     //方程阶数
    double ebxl;    //精确度阈值
    cout<<"请输入矩阵的阶数：    ";
    cin>>n;
    cout<<"请输入迭代的精确度阈值：  ";
    cin>>ebxl;
    cout<<"请输入方程组的增广矩阵：   "<<endl;
    input(CoeA, ResY, n);
    cout<<"请输入初始值向量："<<endl;
    for (int i = 0; i < n; i++){
        cin>>result[i];
    }

    double maxn;
    do
    {
        maxn = 0;       //记录最大差值
        for (int i = 0; i < n; i++)     //迭代x1 ~ xn的循环
        {
            double sum = 0.0;
            double old_x = result[i];      //记录上一次迭代的值
            for (int j = 0; j < n; j++)
            {
                if (j != i){
                    sum += CoeA[i][j] * result[j];     //求出除xi之外的乘积之和
                }
            }
            result[i] = (ResY[i] - sum) / CoeA[i][i];   //单独求出xi的值并替换上一次的值
            double dt = fabs(result[i] - old_x);        //求出相邻两次迭代的差值的绝对值
            maxn = max(maxn, dt);       //得到差值最大值
        }
    }while(maxn > ebxl);

    cout<<"原方程组的解向量为:"<<endl;
    for (int i = 0; i < n; i++){
        cout<<setiosflags(ios::fixed)<<setprecision(6)<<result[i]<<" ";
    }
    cout<<endl;
    return 0;
}
