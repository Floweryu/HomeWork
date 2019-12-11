/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>

using namespace std;

void main() {
    void rungeKutta(float (*f)(float,float),float a,float b,float y0,int N);
    float f(float,float);
    float a=0,b=5,y0=2;
    rungeKutta(f,a,b,y0,20);
}
void rungeKutta(float (*f)(float x,float y),float a,float b,float y0,int N) {
    float x=a,y=y0,K1,K2,K3,K4;
    float h=(b-a)/N;
    int i;
    cout<<"x[0]="<<x<<'\t'<<"y[0]="<<y<<endl;
    for(i=1; i<=N; i++) {
        K1=f(x,y);
        K2=f(x+h/2,y+h*K1/2);
        K3=f(x+h/2,y+h*K2/2);
        K4=f(x+h,y+h*K3);
        y=y+h*(K1+2*K2+2*K3+K4)/6;
        x=a+i*h;
        cout<<"x["<<i<<"]="<<x<<"    y["<<i<<"]="<<y<<endl;
    }
}
float f(float x,float y) {
    return -x*y*y;
}
