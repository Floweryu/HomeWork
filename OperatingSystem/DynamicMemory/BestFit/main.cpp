#include <iostream>
#include "BestFit.h"

int main()
{
    cout << "****************�����Ӧ�㷨**************************" <<endl;
    cout << "************���� 0 ���������˳�����*******************" <<endl;
    cout << "************���� 1 �������������ڴ�*******************" <<endl;
    cout << "************���� 2 �������������ڴ�*******************" <<endl;
    cout << "************���� 3 ����������ʾ�ڴ�*******************" <<endl;
    cout << "******************************************************" <<endl;

    int command;        //���������
    BestFit Memory;
    int _length;        //��ҵ����
    string name;        //��ҵ����
    bool flag;
    while (cout << "���������   ")
    {
        cin >> command;
        cout << endl;
        if (command == 0){      //�˳�����
            exit(0);
        }
        else if (command == 1) { //�����ڴ�
            cout << "������Ҫ������ҵ�����ƣ�string����    ";
            cin >> name;
            cout << "������Ҫ������ҵ��ռ�ڴ�Ĵ�С����0 ~" << MAX_SIZE << "����    ";
            cin >> _length;
            Node work(0, _length, name);
            flag = Memory.AllocationMemory(work);
            if (flag) {
                cout << "�ڴ����ɹ�������" << endl <<endl;
                cout << "**************�������ڴ���ѷ������Ϳ���������Ϣ����**************" << endl<<endl;
                Memory.ShowMemory();
            }
            else
                cout << "δ�ҵ�����Ҫ��Ŀ�����������" << endl << endl;
        }
        else if (command == 2){ //�����ڴ�
            cout << endl <<"������Ҫ�˳��Ľ�������   ";
            cin >> name;
            cout << endl;
            flag = Memory.ExitProgress(name);
            if (flag)
                cout << "�����˳��ڴ�ɹ�!!!" << endl<<endl;
            else
                cout << "�����еĽ�����û�иý��̣�����" << endl<<endl;

            Memory.MergeMemory();
            cout << "**************�ڴ���պ�������Ϣ����**************" << endl<<endl;
            Memory.ShowMemory();
        }
        else if (command == 3){
            cout << "**************�ڴ�������Ϣ����**************" << endl<<endl;
            Memory.ShowMemory();
        }
        else {
            cout << "�����������������һ�����0, 1, 2, 3" << endl;
        }
    }

    return 0;
}
