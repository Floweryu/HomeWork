/*
*ʹ��Doolittle����ֽⷨ�����з�����
* 10*x1 - x2 - 2*x3 = 7.2
* -x1 + 10*x2 - 2*x3 = 8.3
* -x1 - x2 + 5*x3 = 4.2
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define MAXSIZE 50

int main()
{
    double CoeA[MAXSIZE][MAXSIZE], ResY[MAXSIZE], x[MAXSIZE], y[MAXSIZE];
    double L[MAXSIZE][MAXSIZE], U[MAXSIZE][MAXSIZE];
    int n;
    cout << "������ԭ���̵Ľ�����    ";
    cin >> n;

    cout << "�����뷽������������" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> CoeA[i][j];
        cin >> ResY[i];
    }

    //����L����ĶԽ���Ԫ��Ϊ1
    for (int i = 0; i < n; i++)
        L[i][i] = 1;

    //���� Doolittle �ֽ�
    for (int k = 0; k < n; k++)
    {
        //�ֽ�õ� U �������н��д���
        for (int j = k; j < n; j++) {
            U[k][j] = CoeA[k][j];
            for (int i = 0; i < k; i++)
                U[k][j] -= L[k][j] * U[i][j];
        }
        //�ֽ�õ� L �������н�������
        for (int i = k + 1; i < n; i++) {
            L[i][k] = CoeA[i][k];
            for (int j = 0; j < k; j++)
                L[i][k] -= L[i][j] * U[j][k];
            L[i][k] /= U[k][k];
        }
    }

    //���з�����Ļش�����
    for(int i = 0; i < n; i++)     //�� L ���лش������ Ly = ResY �ĵ� y
    {
        y[i] = ResY[i];
        for(int j = 0; j <= i - 1; j++)
            y[i] -= L[i][j] * y[j];
    }

    for(int i = n-1; i >= 0; i--)       //�� U ���лش�, ��� y = Ux, �õ� x
    {
        x[i] = y[i];
        for(int j = i + 1; j < n; j++)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }

    cout << "��÷�����ĸ�Ϊ��";
    for(int i=0; i<n; i++)
        cout << x[i] << " ";
    cout << endl;
    return 0;
}
