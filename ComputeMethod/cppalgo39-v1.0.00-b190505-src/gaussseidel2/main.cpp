/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<cmath>
#define N 100

using namespace std;

void main() {
    int i;
    float *x;
    float c[12]= {8.0,-3.0,2.0,20.0,
                  4.0,11.0,-1.0,33.0,
                  6.0,3.0,12.0,36.0
                 };	//here must be modifed
    float *gaussSeidel(float *,int);
    x=gaussSeidel(c,3);
    for( i=0; i<=2; i++ )
        cout<<"x["<<i<<"]="<<x[i]<<endl;
}


float *gaussSeidel(float *a,int n) {

    int	  i,j,nu=0;
    float *x,dx;
    x =new	float[n*sizeof(float)];
    for( i=0; i<=n-1; i++ )
        x[i]=0.0;
    do {
        for( i=0; i<=n-1; i++ ) {
            dx=0.0;
            for( j=0; j<=n-1; j++ )
                dx+=*(a+i*(n+1)+j)*x[j];
            dx=(*(a+i*(n+1)+n)-dx)/(*(a+i*(n+1)+i));
            x[i]+=dx;
        }
        if( nu>N ) {
            cout<<"迭代发散\n";
            return 0;
        }
        nu++;
    } while(fabs(dx)>1e-6);
    return x;
}

