#include <iostream>
#include "PrioritySchedul.h"
#include "TimeSchedul.h"
using namespace std;

int main()
{
    cout << "*********** �����������㷨ʵ�ִ��������� **************" << endl;
    Progress NewProgress;
    int UseTime = NewProgress.CalculateTime();
    cout << "���������н��̹���Ҫ " << UseTime << " ��ʱ��Ƭ" <<endl << endl;
    int i = 1;
    while (UseTime--)
    {
        cout << "~~~~~~~~~~~~~��   " << i << "  ������~~~~~~~~~~~~" << endl;
        cout << "�������еĽ����� ��  " << NewProgress.ShowProgressID() << endl;

        NewProgress.RunProgress();

        cout << "ʣ��Ľ���Ϊ��  " << endl;
        NewProgress.ShowQueue();            //չʾʣ�����

        i++;
        cout << endl;
    }
    cout << endl << endl;

    cout << "*********** ʱ��Ƭ��ת��ʵ�ִ��������� **************" << endl;
    TimeSchedul NewPro;
    int _UseTime = NewPro.CalculateTime();
    cout << "���������н��̹���Ҫ " << _UseTime << " ��ʱ��Ƭ" <<endl << endl;
    NewPro.RunningMain();
    return 0;
}
