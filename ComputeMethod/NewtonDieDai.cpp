/*
*��ţ�ٵ�������  x*exp(x) - 1 = 0 �ĸ�
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//ԭ����ֵ
double original_f(double x)
{
    return x * exp(x) - 1;
}

//������ֵ
double derived_f(double x)
{
    return exp(x) * (x + 1);
}

int main()
{
    double xk; // ��ʼֵ
    double ebxl;    //�������ȿ��ƣ���ֵ��
    cout<<"������x�ĳ�ʼֵ��  ";
    cin>>xk;
    cout<<"����������ľ���:   ";
    cin>>ebxl;

    double xk1;  //�������
    xk1 = xk - original_f(xk) / derived_f(xk);
    while(fabs(xk1 - xk) > ebxl)
    {
        xk = xk1;
        xk1 = xk - original_f(xk) / derived_f(xk);
    }
    cout<<"���̵ĸ�Ϊ��"<<setiosflags(ios::fixed)<<setprecision(6)<<xk<<endl;
    return 0;
}
