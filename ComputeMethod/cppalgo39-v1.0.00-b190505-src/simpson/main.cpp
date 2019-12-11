/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<math.h>

using namespace std;
void main() {
    int i,n=2;
    float s;
    float f(float);
    float simpson(float (*)(float),float,float,int );
    for( i=0; i<=2; i++ ) {
        s=simpson(f,0,1,n);
        cout<<"s("<<n<<")="<<s<<endl;
        n*=2;
    }
}
float simpson(float (*f)(float),float a,float b,int n) {
    int k;
    float s,s1,s2=0.0;
    float h=(b-a)/n;
    s1=f(a+h/2);
    for(k=1; k<=n-1; k++) {
        s1+=f(a+k*h+h/2);
        s2+=f(a+k*h);
    }
    s=h/6*(f(a)+4*s1+2*s2+f(b));
    return s;
}
float f(float x) {
    return 1/(1+x*x);
    /*	if(x==0)
    		return 1;
    	else
    		return sin(x)/x;*/
}

