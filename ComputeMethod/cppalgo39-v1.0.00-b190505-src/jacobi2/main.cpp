/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<math.h>
#define EPS 1e-6
#define MAX 100

using namespace std;

float *jacobi(float a[3][4],int n) {
    float *x,*y,epsilon,s;
    int	  i,j,k=0;

    x =new float[(n*sizeof(float))];	//here must be modifed
    y =new float[(n*sizeof(float))];	//here must be modifed
    for( i=0; i<n; i++ )
        x[i]=0;
    while(1) {
        epsilon=0;
        k++;
        for( i=0; i<n; i++ ) {
            s=0;
            for( j=0; j<n; j++ ) {
                if(j==i)
                    continue;
                s+=a[i][j]*x[j];
            }
            y[i] =(a[i][n]-s)/a[i][i];
            epsilon +=fabs(y[i]-x[i]);
        }
        if(epsilon<EPS) {
            cout<<"迭代次数为："<<k<<endl;
            return y;
        }
        if( k>=MAX ) {
            cout<<"The method is disconvergent";
            return y;
        }
        for( i=0; i<n; i++ )
            x[i]=y[i];
    }
    return y;
}

void main() {
    int i;
    float a[3][4]= {5.0,2.0,1.0,8.0,2.0,8.0,-3.0,21.0,1.0,-3.0,-6.0,1.0};	//here must be modifed
    float *x;
    x=new float[(3*sizeof(float))];		//here must be modifed
    x=jacobi(a,3);
    for( i=0; i<3; i++ )
        cout<<"x["<<i<<"]="<<x[i]<<endl;
}
