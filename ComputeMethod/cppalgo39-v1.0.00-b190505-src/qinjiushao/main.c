/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

/*秦九韶算法*/

#include "stdio.h"
#define N 100
int main() {
    int n,k,i;
    float a[N],x;
    double v;

    /*输入数据*/
    printf("please input n= ");
    scanf("%d",&n);
    printf("please input fator a0,a1,...,a%d= ",n);
    for(i=0; i<=n; i++) {
        scanf("%f",&a[i]);
    }
    printf("please input x= ");
    scanf("%f",&x);
    v=a[0];

    /*判断 k是否等于 n*/
    for(k=1; k<=n; k++)
        v=x*v+a[k];   // 这一步非常关键

    /*输出数据*/
    printf("the answer is v=%lf",v);
    getch();
    return 0;
}
