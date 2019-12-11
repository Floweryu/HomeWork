/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>
#define MAXSIZE 7
void input(double f[MAXSIZE+ 1], double a, double b, long n);
void main(void) {
    long c[MAXSIZE][MAXSIZE/2+2] = {{2, 1}, {6, 1, 4}, {8, 1, 3}, {90, 7, 32, 12},
        {288, 19, 75, 50}, {840, 41, 216, 27, 272}, {17280, 751, 3577, 1323, 2989}
    };
    double a, b, f[MAXSIZE + 1], integral;
    long n, i;
    printf("\n请输入积分区间边界a, b:");
    scanf("%lf, %lf", &a, &b);
    printf("\n请输入积分节点的个数(2~8):");
    scanf("%ld", &n);
    input(f, a, b, n);
    integral = 0;
    for(i  = 0; i < n/2; i++)
        integral += (f[i]+f[n-i-1])*c[n-2][i+1]/c[n-2][0];
    if(n%2)
        integral += f[n/2]*c[n-2][n/2+1]/c[n-2][0];
    integral *= b-a;
    printf("\n积分值为=%lf", integral);
}
void input(double f[MAXSIZE+ 1], double a, double b, long n) {
    long i ;
    double h;
    h = (b - a)/ (n - 1);
    printf("\n请输入求积节点纵坐标: ");
    for(i = 0; i <= n-1; i++) {
        printf("\nx[%ld] = %lf, f[%ld] =", i, a+i*h, i);
        scanf("%lf", &f[i]);
    }
}
