/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */


#include<math.h>
#include <stdio.h>
double f(double x) {
    double y;
    y=pow(x-1,-1/2);
    return(y);
}

double point(double xo) {
    double x1,x2,xt,xs;
    x1=f(xo);
    printf("x1=%lf",x1);
    x2=f(x1);
    printf("\tx2=%lf",x2);
    xt=xo-(2*x1)+x2;
    printf("\txt=%lf",xt);
    xs=(xo*x2)-(x1*x1);
    printf("\txt=%lf",xs);
    xt=xs/xt;
    printf("\txt=%lf\n",xt);
    return xt;
}

double repass(double a,double eps) {
    double c1,c2;
    c1=point(a);
    printf("x1=%lf\n",c1);
    c2=point(c1);
    printf("x2=%lf\n",c2);
    while(fabs(c2-c1)>eps) {
        c1=point(c1);
        c2=point(c1);
        printf("x1=%lf\n",c1);
        printf(">>>>>>>>>x=%lf\n",c2);
    }
    return c2;
}

int main() {
    double a=1,x,eps=1e-8;
    double repass(double a,double eps);
    printf(" Please input x(0):\n");
    x=repass(a,eps);
    printf("\n x(*)=%lf\n",x);
    return 0;
}
