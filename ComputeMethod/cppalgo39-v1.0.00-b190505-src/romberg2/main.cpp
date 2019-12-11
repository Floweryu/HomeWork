/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<math.h>

using namespace std;

float f(float x) {
    return 1/(1+x*x);
}
float romberg(float a,float b,float (*f)(float),float epsilon) {
    int n=1,k;
    float h=b-a,x,temp;
    float T1,T2,S1,S2,C1,C2,R1,R2;
    T1=(b-a)/2*((*f)(a)+(*f)(b));
    while(1) {
        temp=0;
        for(k=0; k<=n-1; k++) {
            x=a+k*h+h/2;
            temp+=(*f)(x);
        }
        T2=(T1+temp*h)/2;
        if(fabs(T2-T1)<epsilon)
            return T2;
        S2=T2+(T2-T1)/3.0;
        if(n==1) {
            T1=T2;
            S1=S2;
            h/=2;
            n*=2;
            continue;
        }
        C2=S2+(S2-S1)/15;
        if(n==2) {
            C1=C2;
            T1=T2;
            S1=S2;
            h/=2;
            n*=2;
            continue;
        }
        R2=C2+(C2-C1)/63;
        if(n==4) {
            R1=R2;
            C1=C2;
            T1=T2;
            S1=S2;
            h/=2;
            n*=2;
            continue;
        }
        if(fabs(R2-R1)<epsilon)
            return R2;
        R1=R2;
        C1=C2;
        T1=T2;
        S1=S2;
        h/=2;
        n*=2;
    }
}
void main() {
    float epsilon=5e-6;
    cout<<"R="<<romberg(0,1,f,epsilon)<<endl;
}

