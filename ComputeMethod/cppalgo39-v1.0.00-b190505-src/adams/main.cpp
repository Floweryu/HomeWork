/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */


#include<iostream>

using namespace std;

float f(float x,float y) {
    return -x*y*y;
}
float *rungekutta(float (*f)(float x,float y),float a,float b,float y0,int N) {
    float x=a,y=y0,K1,K2,K3,K4,*yy;
    float h=(b-a)/N;
    int i;
    yy=new float[(sizeof(float)*3)];
    for(i=1; i<=3; i++) {
        K1=f(x,y);
        K2=f(x+h/2,y+h*K1/2);
        K3=f(x+h/2,y+h*K2/2);
        K4=f(x+h,y+h*K3);
        y=y+h*(K1+2*K2+2*K3+K4)/6;
        x=a+i*h;
        *(yy+i-1)=y;
    }
    return yy;
}
void adams(float a,float b,int N,float (*f)(float x,float y),float y0) {
    int i;
    float y1,y2,y,yp,yc,*yy,h,x;
    cout<<"x[0]="<<a<<'\t'<<"    y[0]="<<y0<<endl;
    yy=rungekutta(f,a,b,y0,N);
    y1=yy[0];
    y2=yy[1];
    y=yy[2];
    h=(b-a)/N;
    for(i=1; i<=3; i++)
        cout<<"x["<<i<<"]="<<a+i*h<<"    y["<<i<<"]="<<*(yy+i-1)<<endl;
    for(i=3; i<N; i++) {
        x=a+i*h;
        yp=y+h*(55*f(x,y)-59*f(x-h,y2)+37*f(x-2*h,y1)-9*f(x-3*h,y0))/24.0;
        yc=y+h*(9*f(x+h,yp)+19*f(x,y)-5*f(x-h,y2)+f(x-2*h,y1))/24.0;
        cout<<"x["<<i+1<<"]="<<x+h<<"    y["<<i+1<<"]="<<yc<<endl;
        y0=y1;
        y1=y2;
        y2=y;
        y=yc;
    }
}
int main() {
    float a=0,b=5.0,y0=2.0;
    int N=20;
    adams(a,b,N,f,y0);
	return 0;
}