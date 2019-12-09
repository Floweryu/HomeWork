/*
*ʹ�ø�˹��Ԫ�������з�����
* 10*x1 - x2 - 2*x3 = 7.2
* -x1 + 10*x2 - 2*x3 = 8.3
* -x1 - x2 + 5*x3 = 4.2
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int n;      //����Ľ���
    cout << "���������Ľ�����      ";
    cin >> n;

    double** CoeA = new double* [n];      //ϵ������
    for (int i = 0; i < n; i++){
        CoeA[i] = new double [n];
    }
    double* ResY = new double [n];      //�����ұ�����
    double* result = new double [n];    //����洢����


    //�����������
    cout << "�����뷽������������   " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            cin>>CoeA[i][j];
        }
        cin>>ResY[i];
    }


    //�����Ԫ�������������Ǿ���
    for (int k = 0; k < n - 1; k++)     //������׼��
    {
        for (int i = k + 1; i < n; i++) //������Ҫ������Ԫ����
        {
            double scale = CoeA[i][k] / CoeA[k][k];     //��ȥÿ��ʱ�ı�������
            for (int j = k + 1; j < n; j++){
                CoeA[i][j] -= CoeA[k][j] * scale;
            }
            ResY[i] -= ResY[k] * scale;  //�����ұ�
            CoeA[i][k] = 0;             //��ȥ�Ĳ�0
        }
    }

    //�����Ǿ�����лش�
    for (int i = n - 1; i >= 0; i--)
    {
        double temp = 0.0;
        for (int j = i + 1; j < n; j++){
            temp += CoeA[i][j] * result[j];         //��δ֪������ļ�������
        }
        result[i] = (ResY[i] - temp) / CoeA[i][i];  //���δ֪��
    }

    cout << "��˹��Ԫ���Ľ�Ϊ��   " << endl;
    for (int i = 0; i < n; i ++)
        cout << setiosflags(ios::fixed) << setprecision(6) << result[i] << " ";
    cout << endl;

    return 0;
}
