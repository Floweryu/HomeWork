/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>
#include <math.h>
double f(double x);
double df(double x);


void main(void) {
    double epsilon,x0,x1,fx0,dfx0;
    long i,maxi;
    printf("\n请输入x的精度要求：");
    scanf("%lf",&epsilon);
    printf("\n请输入迭代初值：");
    scanf("%lf",&x1);
    printf("\n请输入最大迭代次数：");
    scanf("%ld",&maxi);

    for(i=0; i<maxi; i++) {
        x0=x1;
        fx0=f(x0);
        dfx0=df(x0);
        x1=x0-fx0/dfx0;
        if(fabs(x1-x0)<=epsilon)
            break;
    }

    if(i<maxi)
        printf("\n方程f(x)=0的根x=%lf。",x1);
    else
        printf("\n迭代次数已超过上限。");
}


double f(double x) {
    return x*exp(x) - 1;    /*计算并返回函数值f(x)*/
}
double df(double x) {
    return exp(x) + x*exp(x);    /*计算并返回函数值f’(x)*/
}
