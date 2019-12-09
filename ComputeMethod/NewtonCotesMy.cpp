#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_SIZE 4

int n;      //段数
double y[MAX_SIZE + 1];
long lamda[MAX_SIZE][2 + MAX_SIZE] = {
        {2, 1, 1},
        {6, 1, 4, 1},
        {8, 1, 3, 3, 1},
        {90, 7, 32, 12, 32, 7},
    };

void input(double y[], double a, double b, int n)
{
    double h = (b - a) / n;
    cout << "请输入积分节点的纵坐标：     "<<endl;
    for (int i = 0; i < n + 1; i++){
        cout<<"横坐标 x 为   : "<<setiosflags(ios::fixed)<<setprecision(6)<<a + i * h<<endl;
        cout<<"请输入纵坐标 y  :     ";
        cin>>y[i];
    }
    cout<<endl;
}

double NewtonCotes(double y[], double a, double b, int n)
{
    double integral = 0.0;
    for (int i = 0; i < n + 1; i++){
        integral += y[i] * lamda[n - 1][i + 1] / lamda[n - 1][0];
    }
    integral *= b - a;
    return integral;
}

int main()
{
    double a, b;
    cout << "请输入积分的边界 a 和 b   :    ";
    cin >> a >> b;
    cout << "请输入区间间隔的个数 n  :  ";
    cin >> n;

    input(y, a, b, n);

    double result = NewtonCotes(y, a, b, n);

    cout << "最终积分的结果是   :   "<<setiosflags(ios::fixed)<<setprecision(6)<< result << endl;
    return 0;
}

