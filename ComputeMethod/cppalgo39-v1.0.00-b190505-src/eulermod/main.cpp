/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#define N 10

using namespace std;

void modEuler(float (*f1)(float,float),float x0,float y0,float xn,int n) {
    int i;
    float yp,yc,x=x0,y=y0,h=(xn-x0)/n;
    // cout<<"x[0]="<<x<<'\t'<<"y[0]"<<y<<endl;
    for(i=1; i<=n; i++) {
        yp=y+h*f1(x,y);
        x=x0+i*h;
        yc=y+h*f1(x,yp);
        y=(yp+yc)/2.0;
        cout<<"x["<<i<<"]="<<x<<"    y["<<i<<"]="<<y<<endl;
    }
}
void main() {

    float xn=0.0,x0=-1.0,y0=3.0;
    float f1(float ,float);
    modEuler(f1,x0,y0,xn,N);
}
float f1(float x,float y) {
    return 3*x-2*y*y-12;
}
