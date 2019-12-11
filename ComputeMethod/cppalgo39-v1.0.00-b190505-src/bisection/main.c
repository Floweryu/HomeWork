/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>

double f(double x) {
    return x*x - 4;    /*计算并返回函数值f(x)*/
}

void main(void) {
    double a,b,epsilon,x,middle;
    printf("\n请输入x的精度要求：");
    scanf("%lf",&epsilon);
    printf("\n请输入有根区间的边界a,b：");
    scanf("%lf,%lf",&a,&b);
    if(f(a)==0)x=a;
    else if(f(b)==0)	x=b;
    else {
        while((b-a)/2>epsilon) {
            middle=(a+b)/2;
            if(f(middle)==0)	break;
            else if(f(a)*f(middle)>0)	a=middle;
            else	b=middle;
        }
        x=(a+b)/2;
    }
    printf("\n方程f(x)=0的根x=%lf。",x);
}
