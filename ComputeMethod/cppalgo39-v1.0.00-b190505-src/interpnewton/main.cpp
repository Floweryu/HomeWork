/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

void main() {
    double n=0.0,q=0.0;
    int p;
    double x[13]= {0,10,20,30,40,50,60,70,80,90,100,110,120};
    double y[13]= {5,1,7.5,3,4.5,8.8,15.5,6.5,-5,-10,-2,4.5,7};
    double a[13];//f[x0],f[x0,x1]..........f[x0,x1,....x12];
    double b[12];//f[x1],f[x1,x2]..........f[x1,x2,....x12];
    double c[11];//f[x2],f[x2,x3]..........f[x2,x3,....x12];
    double d[10];//f[x3],f[x3,x4]..........f[x3,x4,....x12];
    double e[9];//f[x4],f[x4,x5]..........f[x4,x5,....x12];
    double f[8];//f[x5],f[x5,x6]..........f[x5,x6,....x12];
    double g[7];//f[x6],f[x6,x7]..........f[x6,x7,....x12];
    double h[6];//f[x7],f[x7,x8]..........f[x7,x8,....x12];
    double i[5];//f[x8],f[x8,x9]..........f[x8,x9,....x12];
    double j[4];//f[x9],f[x9,x10]..........f[x9,x10,....x12];
    double k[3];//f[x10],f[x10,x11],f[x10,x11,x12];
    double l[2];//f[x11],f[x11,x12];
    double m[1];//f[x12]
    double s[13];
    m[0]=y[12];
    l[0]=y[11];
    k[0]=y[10];
    j[0]=y[9];
    i[0]=y[8];
    h[0]=y[7];
    g[0]=y[6];
    f[0]=y[5];
    e[0]=y[4];
    d[0]=y[3];
    c[0]=y[2];
    b[0]=y[1];
    a[0]=y[0];

    for(p=1; p<2; p++)
        l[p]=(m[p-1]-l[p-1])/(x[p+11]-x[11]);

    for(p=1; p<3; p++)
        k[p]=(l[p-1]-k[p-1])/(x[p+10]-x[10]);

    for(p=1; p<4; p++)
        j[p]=(k[p-1]-j[p-1])/(x[p+9]-x[9]);

    for(p=1; p<5; p++)
        i[p]=(j[p-1]-i[p-1])/(x[p+8]-x[8]);

    for(p=1; p<6; p++)
        h[p]=(i[p-1]-h[p-1])/(x[p+7]-x[7]);

    for(p=1; p<7; p++)
        g[p]=(h[p-1]-g[p-1])/(x[p+6]-x[6]);


    for(p=1; p<8; p++)
        f[p]=(g[p-1]-f[p-1])/(x[p+5]-x[5]);

    for(p=1; p<9; p++)
        e[p]=(f[p-1]-e[p-1])/(x[p+4]-x[4]);

    for(p=1; p<10; p++)
        d[p]=(e[p-1]-d[p-1])/(x[p+3]-x[3]);


    for(p=1; p<11; p++)
        c[p]=(d[p-1]-c[p-1])/(x[p+2]-x[2]);

    for(p=1; p<12; p++)
        b[p]=(c[p-1]-b[p-1])/(x[p+1]-x[1]);

    for(p=1; p<13; p++)
        a[p]=(b[p-1]-a[p-1])/(x[p]-x[0]);

    cout<<"请输入X值:";
    cin>>q;
    s[0]=(q-x[0]);
    for(p=1; p<13; p++) {
        s[p]=s[p-1]*(q-x[p]);
    }
    n=a[0];
    for(p=1; p<13; p++) {
        n+=a[p]*s[p-1];
    }
    cout<<"函数在点X处的近似值为:"<<n;
}