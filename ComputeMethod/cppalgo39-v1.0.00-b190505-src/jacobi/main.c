/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include "stdio.h"
#include "math.h"
#define MAX 100
#define n 3
#define exp 0.005
main() {
    int i,j,k,m;
    float temp,s;
    float static a[n][n]= {{10,0,-1},{-2,10,-1},{0,-1,5}};
    float static b[n]= {9,7,4};
    float static x[n],B[n][n],g[n],y[n]= {0,0,0};
 
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            B[i][j]=-a[i][j]/a[i][i];
            g[i]=b[i]/a[i][i];
        }
    for(i=0; i<n; i++)
        B[i][i]=0;
    m=0;
    do {
        for(i=0; i<n; i++)
            x[i]=y[i];
        for(i=0; i<n; i++) {
            y[i]=g[i];
            for(j=0; j<n; j++)
                y[i]=y[i]+B[i][j]*x[j];
        }
        m++;
        printf("\n%dth result is:",m);
        printf("\nx0=%7.5f,x1=%7.5f,x2=%7.5f",y[0],y[1],y[2]);
        temp=0;
        for(i=0; i<n; i++) {
            s=fabs(y[i]-x[i]);
            if(temp<s) temp=s;
        }
        printf("\ntemp=%f",temp);
    } while(temp>=exp);
    printf("\n\nThe last result is:");
    for(i=0; i<n; i++)
        printf("\nx[%d]=%7.5f",i,y[i]);
}


