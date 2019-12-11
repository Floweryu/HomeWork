/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * March 1st, 2013 
 */

#include<iostream>
#include<math.h>
#include<process.h>
using namespace std;

/*
 * 要求对称系数矩阵。
 */


class Cholesky {
private:
    int i,j,k,n;
    double sum,*b,*d,*x,**a,eps;
public:
    void choleskyInput();
    void choleskyDecomposition();
    void choleskyOutput();
    ~Cholesky() {
        delete []b;
        delete []d;
        delete []x;
        for(i=0; i<n; i++) {
            delete [] a[i];
        }
        delete []a;
    }

};

void main() {
    Cholesky solution;
    solution.choleskyInput();
    solution.choleskyDecomposition();
    solution.choleskyOutput();
}

void Cholesky::choleskyInput() {
    cout<<"输入方程的个数";
    cin>>n;
    b=new double[n];
    d=new double[n];
    x=new double[n];
    a=new double*[n];

    for(i=0; i<n; i++) {
        a[i] = new double[n];
    }

    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            cout<<"/n输入a["<<i<<"]["<<j<<"]=";
            cin>>a[i][j];
        }
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            if(a[i][j] != a[j][i]) {
                cout<<"/n系数矩阵不对称.失败..."<<endl;
                exit(0);
            }
        }
    for(i=0; i<n; i++) {

        cout<<"/n输入 b["<<i<<"]=";
        cin>>b[i];
    }
    cout<<"/n输入最小主元素";
    cin>>eps;		//输入段结束
}
void Cholesky::choleskyDecomposition() {
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            sum=a[i][j];
            for(k=0; k<i; k++) {
                sum -= a[i][k]*a[j][k];
            }
            if( i==j) {
                if(sum <= 0) {
                    cout<<"/n矩阵非正定.失败..."<<endl;
                    exit(0);
                }
                d[i]=sqrt(sum);
            } else {
                a[j][i] = sum/d[i];
            }

        }

    for(i=0; i<n; i++) {
        sum=b[i];
        for(k=0; k<i; k++) {
            sum -= a[i][k]*x[k];
        }
        x[i] = sum/d[i];
    }

    for(i=(n-1); i>=0; i--) {
        sum = x[i];
        for(k=(i+1); k<n; k++) {
            sum -= a[k][i]*x[k];
        }
        x[i] = sum/d[i];
    }
}
void Cholesky::choleskyOutput() {
    cout<<"/n:结果是："<<endl;
    for(i=0; i<n; i++) {
        cout<<"x["<<i<<"]="<<x[i]<<endl;
    }

}