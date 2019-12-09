/*
*ʹ�ø�˹-���¶������������з�����
* 10*x1 - x2 - 2*x3 = 7.2
* -x1 + 10*x2 - 2*x3 = 8.3
* -x1 - x2 + 5*x3 = 4.2
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

#define MAXSIZE 50

double CoeA[MAXSIZE][MAXSIZE];      //ϵ������
double ResY[MAXSIZE];       //ÿ����ʽ���ֵ����
double result[MAXSIZE];     //�������

//�����������
void input(double CoeA[MAXSIZE][MAXSIZE], double ResY[MAXSIZE], long n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>CoeA[i][j];    //����ϵ��
        }
        cin>>ResY[i];       //������ֵ
    }
}

int main()
{
    long n;     //���̽���
    double ebxl;    //��ȷ����ֵ
    cout<<"���������Ľ�����    ";
    cin>>n;
    cout<<"����������ľ�ȷ����ֵ��  ";
    cin>>ebxl;
    cout<<"�����뷽������������   "<<endl;
    input(CoeA, ResY, n);
    cout<<"�������ʼֵ������"<<endl;
    for (int i = 0; i < n; i++){
        cin>>result[i];
    }

    double maxn;
    do
    {
        maxn = 0;       //��¼����ֵ
        for (int i = 0; i < n; i++)     //����x1 ~ xn��ѭ��
        {
            double sum = 0.0;
            double old_x = result[i];      //��¼��һ�ε�����ֵ
            for (int j = 0; j < n; j++)
            {
                if (j != i){
                    sum += CoeA[i][j] * result[j];     //�����xi֮��ĳ˻�֮��
                }
            }
            result[i] = (ResY[i] - sum) / CoeA[i][i];   //�������xi��ֵ���滻��һ�ε�ֵ
            double dt = fabs(result[i] - old_x);        //����������ε����Ĳ�ֵ�ľ���ֵ
            maxn = max(maxn, dt);       //�õ���ֵ���ֵ
        }
    }while(maxn > ebxl);

    cout<<"ԭ������Ľ�����Ϊ:"<<endl;
    for (int i = 0; i < n; i++){
        cout<<setiosflags(ios::fixed)<<setprecision(6)<<result[i]<<" ";
    }
    cout<<endl;
    return 0;
}
