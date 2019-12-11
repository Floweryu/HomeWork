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
    int i;
    float *a;
    float x[16]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    float y[16]= {4.00,6.40,8.00,8.80,9.22,9.50,9.70,9.86,
                  10.00,10.20,10.32,10.42,10.50,10.55,10.58,10.60
                 };
    float *approx(float *,float *,int ,int );
    a=approx(x,y,16,2);
    for(i=0; i<=2; i++)
        cout<<"a["<<i<<"]="<<a[i]<<endl;
}
float *approx(float *x,float *y,int m,int n) {
    float *c,*a;
    int i,j,t;
    float power(int ,float);
    float *colPivot(float *,int );
    c= new float[((n+1)*(n+2)*sizeof(float))];
    for(i=0; i<=n; i++) {
        for (j=0; j<=n; j++) {
            *(c+i*(n+2)+j)=0.0;
            for(t=0; t<=m-1; t++)
                *(c+i*(n+2)+j)+=power(i+j,x[t]);
        }
        *(c+i*(n+2)+n+1)=0.0;
        for(j=0; j<=m-1; j++)
            *(c+i*(n+2)+n+1)+=y[j]*power(i,x[j]);
    }
    a=colPivot((float *)c,n+1);
    return a;
}
float *colPivot(float *a,int n) {
    int i,j,t,k;
    float *x,*c,p;
    x=new float[(n*sizeof(float))];
    c=new float[(n*(n+1)*sizeof(float))];
    for(i=0; i<=n-1; i++)
        for (j=0; j<=n; j++)
            *(c+i*(n+1)+j)=(*(a+i*(n+1)+j));
    for(i=0; i<=n-2; i++) {
        k=i;
        for(j=i+1; j<=n-1; j++)
            if(fabs(*(c+j*(n+1)+i))>(fabs(*(c+k*(n+1)+i))))
                k=j;
        if(k!=j)
            for(j=i; j<=n; j++) {
                p=*(c+i*(n+1)+j);
                *(c+i*(n+1)+j)=*(c+k*(n+1)+j);
                *(c+k*(n+1)+j)=p;
            }
        for(j=i+1; j<=n-1; j++) {
            p=(*(c+j*(n+1)+i))/(*(c+i*(n+1)+i));
            for(t=i; t<=n-1; t++)
                *(c+j*(n+1)+t)=*(c+j*(n+1)+t)-p*(*(c+i*(n+1)+t));
            *(c+j*(n+1)+n)-=*(c+i*(n+1)+n)*p;
        }
    }
    for( i=n-1; i>=0; i-- ) {
        for( j=n-1; j>=i+1; j--)
            (*(c+i*(n+1)+n))-=x[j]*(*(c+i*(n+1)+j));
        x[i]=*(c+i*(n+1)+n)/(*(c+i*(n+1)+i));
    }
    delete[] c;
    return x;
}
float power(int i,float v) {
    float a=1.0;
    while(i--)
        a*=v;
    return a;
}
