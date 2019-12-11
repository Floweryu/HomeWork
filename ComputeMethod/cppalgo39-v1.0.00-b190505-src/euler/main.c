/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>
#define MAXSIZE 50

double f(double x,double y);

void main(void) {
    double a,b,h,x[MAXSIZE],y[MAXSIZE];
    long i,n;
    printf("\n请输入求解区间a,b：");
    scanf("%lf,%lf",&a,&b);
    printf("\n请输入步长h：");
    scanf("%lf",&h);
    n=(long)((b-a)/h);
    x[0]=a;

    printf("\n请输入起点x[0]=%lf处的纵坐标y[0]：",x[0]);
    scanf("%lf",&y[0]);
    for(i=0; i<n; i++) {
        x[i+1]=x[i]+h;
        y[i+1]=y[i]+h*f(x[i],y[i]);
    }
	
    printf("\n计算结果为：");

    for(i=0; i<=n; i++)
        printf("\nx[%ld]=%lf,y[%ld]=%lf",i,x[i],i,y[i]);
}

double f(double x,double y) {
    return y - 2*x/y;    /*计算并返回函数值f(x,y)*/
}
