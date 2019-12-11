/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include <stdio.h>
#include <conio.h>
#include <dos.h>

void main() {
    char play;
    int i,n;
    float a[100],b[100],c[100],d[100];
    float u[100],l[100],y[100],x[100];

    do {
        printf("Please input the square distance set of piece n:\r\n");
        scanf("%d",&n);

        printf("Please input a2--an:\n");
        for(i=2; i<=n; i++) {
            printf("a%d=",i);
            scanf("%f",&a[i]);
        }

        printf("Please input b1--bn:\n");
        for(i=1; i<=n; i++) {
            printf("b%d=",i);
            scanf("%f",&b[i]);
        }

        printf("Please input c1--c(n-1):\n");
        for(i=1; i<n; i++) {
            printf("c%d=",i);
            scanf("%f",&c[i]);
        }

        printf("Please input d1--dn:\n");
        for(i=1; i<=n; i++) {
            printf("d%d=",i);
            scanf("%f",&d[i]);
        }

        u[1]=b[1];
        y[1]=d[1];
        for(i=2; i<=n; i++) {
            l[i]=a[i]/u[i-1];
            u[i]=b[i]-l[i]*c[i-1];
            y[i]=d[i]-l[i]*y[i-1];
        }
        x[n]=y[n]/u[n];
        for(i=n-1; i>0; i--)
            x[i]=(y[i]-c[i]*x[i+1])/u[i];
        cprintf("The result:\r\n\n");
        for(i=n; i>=1; i--)
            printf("   x%d=%f\n",i,x[i]);
        getche();
        printf("\n");
        printf("continue?(y/n)");
        play=getche();
    } while(play=='y'||play=='Y');

}