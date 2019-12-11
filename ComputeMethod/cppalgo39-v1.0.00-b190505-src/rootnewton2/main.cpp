/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<math.h>
#define N 100
#define EPS 1e-6
#define ETA 1e-8

using namespace std;

void main() {
    float f(float);
    float f1(float);
    float x0,y0;
    float newton(float (*)(float),float (*)(float),float);

    cout<<"Please input x0\n";
    cin>>x0;
    cout<<"x(0)="<<x0<<endl;
    y0=newton(f,f1,x0);
    cout<<"\nThe root of the equation is x="<<(float)y0<<endl;
}

float newton(float (*f)(float),float (*f1)(float),float x0) {
    float x1,d;
    int k=0;
    do {
        x1=x0-f(x0)/f1(x0);
        if((k++>N)||(fabs(f1(x1))<EPS)) {
            cout<<"\nNewton method faild!";
            return 0;
        }
        d=(fabs(x1)<1?x1-x0:(x1-x0)/x1);
        x0=x1;
        cout<<"x("<<k<<")="<<x0<<endl;
    } while(fabs(d)>EPS&&fabs(f(x1))>ETA);
    return 1;
}

float f(float x) {
//	return log(x)+x-2;
    return x*x*x+x*x-3*x-3;
}

float f1(float x) {
//	return 1/x+1;
    return 3.0*x*x+2*x-3;
}
