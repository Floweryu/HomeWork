/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <math.h>
#include "stdio.h"

#define F(x,y) (y)-2*(x)/(y)
void main() {
    float x0,y0,k1,k2,k3,k4,x1,y1,h;
    int n,i;
    printf("input data x0,y0,h,n=\n");
    scanf("%f,%f,%f,%d",&x0,&y0,&h,&n);
    printf("%15s%15s%15s\n","     n","x      ","y      ");
    printf("     ");
    for (i=0; i<41; i++)
        printf("\n");
    printf("%15s%15.6f%15.6f\n","      0",x0,y0);
    for(i=1; i<=n; i++) {
        x1=x0+h;
        k1=F(x0,y0);
        k2=F(x0+h/2,y0+h*k1/2);
        k3=F(x0+h/2,y0+h*k2/2);
        k4=F(x0+h,y0+h*k3);
        y1=y0+h*(k1+2*k2+2*k3+k4)/6;
        printf("%15d%15.6f%15.6f\n",i,x1,y1);
        x0=x1;
        y0=y1;
    }
}
