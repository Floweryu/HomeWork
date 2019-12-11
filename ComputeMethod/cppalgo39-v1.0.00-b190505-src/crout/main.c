/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include "stdio.h"
#include "math.h"//头文件
#define N 20//自定义N=20

int main() { //主函数
    int i,j,k;
    int size;
    float a[N][N],l[N][N],u[N][N];
    float b[N],x[N],y[N];//定义变量
    printf("\t\t\tCrout分解法解方程组\n");
    printf("请输入方阵A的n：");
    scanf("%d",&size);
    printf("\n");
    printf("请输入方程组的系数:\n");
    for(i=0; i<size; i++) {
        for(j=0; j<size; j++) {
            scanf("%f",&a[i][j]);//输入方程组系数矩阵a[][]
        }
    }
    printf("\n请输入方程组的y:\n");
    for(i=0; i<size; i++)
        scanf("%f",&b[i]);//输入结果矩阵b[]
    printf("\n方阵A[][]为：\n");
    for(i=0; i<size; i++) {
        for(j=0; j<size; j++) {
            printf("%f  ",a[i][j]);//输出a[][]
        }
        printf("\n");
    }
    printf("\n方程组y为:\n");
    for(i=0; i<size; i++)
        printf("%f  ",b[i]);//输出b[]
    printf("\n");
    for(i=0; i<size; i++) {
        u[i][i]=1;//定初始值 令u[i][i]=1
    }
    for(i=0; i<size; i++)
        for(j=i+1; j<size; j++) {
            l[i][j]=0;//定初始值 令l[i][j]=0
        }
    for(j=0; j<size; j++)
        for(i=j+1; i<size; i++) {
            u[i][j]=0;//定初始值 令u[i][j]=0
        }
    l[0][0]=a[0][0];
    for(i=1; i<size; i++) {
        l[i][0]=a[i][0];//计算第一行的l[][]
        u[0][i]=a[0][i]/l[0][0];//计算第一列的u[][]
    }
    for(i=1; i<size-1; i++) {
        for(j=1; j<=i; j++) { //计算第2行到第size-1行的l[][]
            l[i][j]=a[i][j];
            for(k=0; k<j; k++) {
                l[i][j]=l[i][j]-l[i][k]*u[k][j];
            }
        }
        printf("\n");
        for(j=i+1; j<size; j++) { //计算第2行到第size行的u[][]
            u[i][j]=a[i][j];
            for(k=0; k<=i-1; k++) {
                u[i][j]=u[i][j]-l[i][k]*u[k][j];

            }
            u[i][j]=u[i][j]/l[i][i];
        }
        printf("\n");
    }
    for(j=1; j<size; j++) { //计算第size行的l[][]
        l[size-1][j]=a[size-1][j];
        for(k=0; k<=j-1; k++) {
            l[size-1][j]=l[size-1][j]-l[size-1][k]*u[k][j];
        }
    }
    printf("\n");
    printf("输出矩阵L[i][j]\n");
    for(i=0; i<size; i++) {
        for(j=0; j<size; j++) {
            printf("%f",l[i][j]);
            printf("   ");//输出下三角矩阵l[][]
        }
        printf("\n");
    }
    printf("输出矩阵U[i][j]\n");
    for(i=0; i<size; i++) {
        for(j=0; j<size; j++) {
            printf("%f",u[i][j]);
            printf("   ");//输出单位上三角矩阵u[][]
        }
        printf("\n");
    }
    y[0]=b[0]/l[0][0];//给y[0]初始值
    for(i=1; i<size; i++) { //计算y[i]的值
        y[i]=b[i];
        for(k=0; k<=i-1; k++) {
            y[i]=y[i]-l[i][k]*y[k];//计算公式
        }
        y[i]=y[i]/l[i][i];
    }
    printf("\n");
    printf("y值:\n");
    for(i=0; i<size; i++)
        printf("y[%d]=%f  ",i+1,y[i]);//输出y[i]的结果
    printf("\n\n");
    printf("x的值:\n");
    x[size-1]=y[size-1];//给x[size-1]赋值
    for(i=size-2; i>=0; i--) {
        x[i]=y[i];
        for(k=i+1; k<size; k++) {
            x[i]=x[i]-u[i][k]*x[k];//计算x[]
        }
    }
    for(i=0; i<size; i++) {
        printf("x[%d]=%f\n",i+1,x[i]);//输出x[i]的结果
    }
}
