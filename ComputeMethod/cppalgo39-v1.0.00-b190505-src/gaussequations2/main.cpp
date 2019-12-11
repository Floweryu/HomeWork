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

//gauss 顺序消元求解方程组
class Gauss {
private:
    int i,j,k,n;
    double eps,ratio,sum,*x,**a;
    /*
    i,j     为数组下标
    k       为步骤计数器和数组下标
    n       表示方程个数
    eps     表示主元素的最小允许值
    ratio   用于存储比值a[i][k]/a[k][k]
    sum     累加器
    x[i]    表示方程组未知数
    a[i][j] 表示增广矩阵的元素
    */
public:
    void gaussInput();         //数据输入
    void gaussElimination();   //消元函数
    void gaussOutput();        //结果输出

    ~Gauss() {
        delete [] x;
        for(i = 0; i < n; i++) {
            delete [] a[i];
        }
        delete [] a;
    }
};

void main() {
    Gauss solution;
    solution.gaussInput();
    solution.gaussElimination();
    solution.gaussOutput();
}

void Gauss::gaussInput() {
    cout<<"输入方程的个数";
    cin>>n;
    x=new double[n];
    a=new double*[n];

    for(i=0; i<n; i++) {
        a[i] = new double[n+1];
    }

    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            cout<<"/n输入a["<<i<<"]["<<j<<"]=";
            cin>>a[i][j];
        }

    for(i=0; i<n; i++) {
        cout<<"/n输入 b["<<i<<"]=";
        cin>>a[i][n];
    }
    cout<<"/n输入最小主元素";
    cin>>eps;     //输入段结束
}

void Gauss::gaussElimination() { //gauss 消去函数
    for(k=0; k<(n-1); k++) {
        for(i=(k+1); i<n; i++) {
            if(fabs(a[k][k])<eps) {
                cout<<"/n主元素太小.失败...."<<endl;
                exit(0);
            }
            ratio = a[i][k]/a[k][k];
            for(j=(k+1); j<(n+1); j++) {
                a[i][j] -= ratio*a[k][j];
            }
            a[i][k] = 0;
        }
    }
    x[n-1] = a[n-1][n]/a[n-1][n-1];//回代
    for(i=(n-2); i>=0; i--) {
        sum = 0.0;
        for(j=(i+1); j<n; j++) {
            sum += a[i][j] * x[j];
        }
        x[i] = (a[i][n] - sum)/a[i][i];
    }
}

void Gauss::gaussOutput() { //结果输出函数
    cout<<"/n结果是："<<endl;
    for(i=0; i<n; i++) {
        cout<<"/nx["<<i<<"]="<<x[i]<<endl;
    }
}