/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include "stdio.h"
#include "math.h"
float f(float x) {
    return(4/(1+x*x));
}
int main() {
    float a=0,b=1,h,t1,t2,s1,s2=0,c1,c2=0,r1,r2=0,exp=0.00001;
    float s,x;
    int k=0;
    h=b-a;
    t2=0.5*h*(f(a)+f(b));
    do {
        r1=r2;
        do {
            c1=c2;
            do {
                s1=s2;
                t1=t2;
                k++;
                h=0.5*h;
                s=0;
                x=a+h;
                while(x<b) {
                    s=s+f(x);
                    x=x+2*h;
                }
                t2=0.5*t1+h*s;
                s2=t2+(t2-t1)/3;
            } while(k==1);
            c2=s2+(s2-s1)/15;
        } while(k==2);
        r2=c2+(c2-c1)/63;
    } while(fabs(r2-r1)>=exp);
    printf("\nThe result is:%7.5f",r2);
    return 0;
}