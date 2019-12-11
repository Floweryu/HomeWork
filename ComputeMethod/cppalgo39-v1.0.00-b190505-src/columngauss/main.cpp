/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<math.h>

using namespace std;

float *colPivot( float *c,int n ) {
    int i,j,t,k;
    float *x,p;
    x=new float[n*sizeof(float)];
    for( i=0; i<=n-2; i++) {
        k=i;
        for(j=i+1; j<=n-1; j++)
            if(fabs(*(c+j*(n+1)+i))>(fabs(*(c+k*(n+1)+i))))
                k=j;
        if(k!=i)
            for( j=i; j<=n; j++ ) {
                p=*(c+i*(n+1)+j);
                *(c+i*(n+1)+j)=*(c+k*(n+1)+j);
                *(c+k*(n+1)+j)=p;
            }
        for( j=i+1; j<=n-1; j++ ) {
            p=(*(c+j*(n+1)+i))/(*(c+i*(n+1)+i));
            for( t=i; t<=n; t++ )
                *(c+j*(n+1)+t)-=p*(*(c+i*(n+1)+t));
        }
    }
    for( i=n-1; i>=0; i--) {
        for( j=n-1; j>=i+1; j--)
            (*(c+i*(n+1)+n))-=x[j]*(*(c+i*(n+1)+j));
        x[i]=*(c+i*(n+1)+n)/(*(c+i*(n+1)+i));
    }
    return x;
}

int main() {
    int i;
    float *x;
    float c[3][4] = {0.101,2.304,3.555,1.183,
                     -1.347,3.712,4.623,2.137,
                     -2.835,1.072,5.643,3.035
                    };
    float *ColPivot(float *,int);
    x=colPivot(c[0],3);
    for( i=0; i<=2; i++ )
        cout<<"x("<<i<<")="<<x[i]<<endl;
	return 0;
}