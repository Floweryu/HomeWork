/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>
#include <math.h>
#define MAXSIZE 50
void input(double a[MAXSIZE][MAXSIZE+1],long n);
void output(double x[MAXSIZE],long n);
void main(void) {
    double a[MAXSIZE][MAXSIZE+1],x[MAXSIZE],s;
    long n,i,j,k;
    printf("\n请输入原方程组的阶数：");
    scanf("%ld",&n);
    input(a,n);
    for(k=0; k<=n-2; k++)
        for(i=k+1; i<=n-1; i++) {
            a[i][k]/=-a[k][k];
            for(j=k+1; j<=n; j++)	a[i][j]+=a[i][k]*a[k][j];
        }
    for(k=n-1; k>=0; k--) {
        s=0;
        for(j=k+1; j<=n-1; j++)	s+=a[k][j]*x[j];
        x[k]=(a[k][n]-s)/a[k][k];
    }
    output(x,n);
}

void input(double a[MAXSIZE][MAXSIZE+1],long n) {
    long i,j;
    printf("\n请输入原方程组的增广矩阵：\n");
    for(i=1; i<=n; i++)
        for(j=1; j<=n+1; j++)
            scanf("%lf",&a[i-1][j-1]);
}
void output(double x[MAXSIZE],long n) {
    long k;
    printf("\n原方程组的解为：\n");
    for(k=1; k<=n; k++)
        printf("  %lf",x[k-1]);
}