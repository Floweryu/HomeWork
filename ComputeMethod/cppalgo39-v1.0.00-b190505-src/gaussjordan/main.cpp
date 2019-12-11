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

class Jordan {
private:
    int i,j,k,n,flag,scani,scanj,*row,*col;
    double eps,pivot,aijcolk,*x,**a;
public:
    void jordanInput();//数据输入的函数声明
    void jordanReduction();//消去法函数声明
    void jordanOutput();//结果输出的函数声明
    ~Jordan() {
        delete [] row;
        delete [] col;
        delete [] x;
        for(i=0; i<n; i++) {
            delete [] a[i];
        }
        delete []a;
    }
};

void main() {
    Jordan solution;
    solution.jordanInput();
    solution.jordanReduction();
    solution.jordanOutput();
}

void Jordan::jordanInput() {
    cout<<"输入方程的个数:";
    cin>>n;
    row = new int[n];
    col = new int[n];
    x = new double[n];
    a = new double* [n];

    for(i=0; i<n; i++) {
        a[i] = new double[n+1];
    }
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            cout<<"/n输入 a["<<i<<"]["<<j<<"]=";
            cin>>a[i][j];
        }
    for(i=0; i<n; i++) {
        cout<<"/n输入 b["<<i<<"]=";
        cin>>a[i][n];
    }
    cout<<"/n输入最小主元素";
    cin>>eps;
}

void Jordan::jordanReduction() {
    for(k=0; k<n; k++) {
        pivot = 0.0;
        for(i=0; i<n; i++) {
            flag = 0;
            for(j=0; j<n; j++) {
                flag = 0;
                if(k>0) {
                    for(scani=0; scani<k; scani++)
                        for(scanj=0; scanj<k; scanj++) {
                            if((i==row[scani])||(j==col[scanj])) {
                                flag = 1;//标记记录过的行和列
                            }
                        }
                } else {

                    flag = 0;//标记为未为设置
                }
                if(flag == 0) {
                    if(fabs(a[i][j])>fabs(pivot)) {
                        pivot = a[i][j];
                        row[k] = i;
                        col[k] = j;
                    }
                }//记录主元信息结束
            }
        }

        if(fabs(pivot)>eps) {
            for(j=0; j<(n+1); j++) {
                a[row[k]][j]/=pivot;
            }
            for(i=0; i<n; i++) {
                aijcolk=a[i][col[k]];
                if(i!=row[k]) {
                    for(j=0; j<(n+1); j++) {
                        a[i][j] = a[i][j] - aijcolk * a[row[k]][j];
                    }
                }
            }
        } else {
            cout<<"/n最大的主元素 = "<<pivot<<endl;
            cout<<"/n矩阵可能奇异.失败..."<<endl;
            exit(0);
        }
    }
    for(i=0; i<n; i++) {
        x[col[i]] = a[row[i]][n];
    }
}

void Jordan::jordanOutput() {
    cout<<"/n结果是:"<<endl;
    for(i=0; i<n; i++) {
        cout<<"/nx["<<i<<"]="<<x[i]<<endl;
    }
}