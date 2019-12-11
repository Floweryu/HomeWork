/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>
#include <iostream>
#include <math.h>

#define MAX_N 20

int main(int argc, char* argv[]) {
    int n; // 未知数个数
    int i, j, k;
    static double a[MAX_N][MAX_N], b[MAX_N], x[MAX_N], y[MAX_N];
    static double l[MAX_N][MAX_N], u[MAX_N][MAX_N];
    printf("\nInput n value(dim of Ax=b): "); //输入系数矩阵维度
    scanf("%d", &n);
    if(n >MAX_N) {
        printf("The input n is larger than MAX_N, please redefine the MAX_N.\n");
        return 1;
    }
    if(n <= 0) {
        printf("Please input a number between 1 and %d.\n", MAX_N);
        return 1;
    }
    printf("Now input the matrix a(i, j), i, j = 0, ..., %d:\n", n-1); //输入 系数矩阵
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            scanf("%lf", &a[i][j]);
    printf("Now input the matrix b(i), i = 0, ..., %d:\n", n-1); //输入常数项
    for(i=0; i<n; i++)
        scanf("%lf", &b[i]);
    for(i=0; i<n; i++)
        l[i][i] = 1; 
    for(k=0; k<n; k++) {
        for(j=k; j<n; j++) {           // dolittle分解
            u[k][j]=a[k][j];
            for(i=0; i<=k-1; i++)
                u[k][j]-=(l[k][i]*u[i][j]);
            printf("%f\n", u[k][j]);
        }
        for(i=k+1; i<n; i++) {
            l[i][k]=a[i][k];
            for(j=0; j<=k-1; j++)
                l[i][k]-=(l[i][j]*u[j][k]);
            l[i][k]/=u[k][k];
            printf("%f\n", l[i][k]);
        }
    }

    for(i=0; i<n; i++) { // 解Ly = b
        y[i] = b[i];
        for(j=0; j<=i-1; j++)
            y[i] -= (l[i][j]*y[j]);
    }

    for(i=n-1; i>=0; i--){ // 解UX = Y
        x[i]=y[i];
        for(j=i+1; j<n; j++)
            x[i] -= (u[i][j]*x[j]);
        x[i]/=u[i][i];
    }

    printf("Solve...x_i = \n"); // 输出结果
    for(i=0; i<n; i++)
        printf("%f\n", x[i]);
    system("pause");
    return 0;
}