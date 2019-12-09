#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_SIZE 4

int n;      //����
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
    cout << "��������ֽڵ�������꣺     "<<endl;
    for (int i = 0; i < n + 1; i++){
        cout<<"������ x Ϊ   : "<<setiosflags(ios::fixed)<<setprecision(6)<<a + i * h<<endl;
        cout<<"������������ y  :     ";
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
    cout << "��������ֵı߽� a �� b   :    ";
    cin >> a >> b;
    cout << "�������������ĸ��� n  :  ";
    cin >> n;

    input(y, a, b, n);

    double result = NewtonCotes(y, a, b, n);

    cout << "���ջ��ֵĽ����   :   "<<setiosflags(ios::fixed)<<setprecision(6)<< result << endl;
    return 0;
}

