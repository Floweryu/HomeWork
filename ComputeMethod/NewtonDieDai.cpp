/*
*用牛顿迭代法求  x*exp(x) - 1 = 0 的根
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//原函数值
double original_f(double x)
{
    return x * exp(x) - 1;
}

//导函数值
double derived_f(double x)
{
    return exp(x) * (x + 1);
}

int main()
{
    double xk; // 初始值
    double ebxl;    //迭代精度控制（阈值）
    cout<<"请输入x的初始值：  ";
    cin>>xk;
    cout<<"请输入迭代的精度:   ";
    cin>>ebxl;

    double xk1;  //迭代结果
    xk1 = xk - original_f(xk) / derived_f(xk);
    while(fabs(xk1 - xk) > ebxl)
    {
        xk = xk1;
        xk1 = xk - original_f(xk) / derived_f(xk);
    }
    cout<<"方程的根为："<<setiosflags(ios::fixed)<<setprecision(6)<<xk<<endl;
    return 0;
}
