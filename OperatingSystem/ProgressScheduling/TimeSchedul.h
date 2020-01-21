#ifndef TIMESCHEDUL_H_INCLUDED
#define TIMESCHEDUL_H_INCLUDED

#include <iostream>
#include <list>
using namespace std;

struct TPCB{
    string id;              //������
    int RequestTime;        //Ҫ������ʱ��
    int RunningTime;        //�Ѿ�����ʱ��
    char State;             //״̬:   'R'���������� 'E'��������
    TPCB(string _id, int _request_time, int _running_time, char _state){
        id = _id;
        RequestTime = _request_time;
        RunningTime = _running_time;
        State = _state;
    }
};

class TimeSchedul
{
private:
    list<TPCB> progress;
    int time_sum;
public:
    TimeSchedul();
    ~TimeSchedul() {};
    void ShowList();                            //չʾ���������н���
    void ShowProgress(TPCB& pcb) const;         //չʾ������Ϣ
    string ShowProgressID(TPCB& pcb) const;     //չʾ����ID
    bool RunProgress(TPCB& pcb);                //���н���, ���̽�������true, ���򷵻� false
    void RunningMain();                         //ʱ��Ƭ����������
    int CalculateTime();                        //�������н��������������Ҫ��ʱ��Ƭ
};

TimeSchedul::TimeSchedul()
{
    TPCB Q1("Q1", 2, 1, 'R');
    TPCB Q2("Q2", 3, 0, 'R');
    TPCB Q3("Q3", 1, 0, 'R');
    TPCB Q4("Q4", 2, 0, 'R');
    TPCB Q5("Q5", 4, 0, 'R');
    progress.push_back(Q1);
    progress.push_back(Q2);
    progress.push_back(Q3);
    progress.push_back(Q4);
    progress.push_back(Q5);
    time_sum = 0;
}

//չʾ���������н���
void TimeSchedul::ShowList()
{
    if (progress.empty())
        cout << "���̶���Ϊ�գ������Ѿ�ȫ��������ϣ�����" << endl;
    else {
        list<TPCB>::iterator it;
        for (it = progress.begin(); it != progress.end(); it++){
            cout << (*it).id << " ";
        }
        cout << endl;
    }
}

//չʾ������Ϣ
void TimeSchedul::ShowProgress(TPCB& pcb) const
{
    cout << "���̵�IDΪ��  " << pcb.id << endl
         << "����Ҫ������ʱ��Ϊ��  " << pcb.RequestTime << endl
         << "�����Ѿ�����ʱ��Ϊ��  " << pcb.RunningTime << endl
         << "���̵�״̬Ϊ��  " << pcb.State << endl << endl;
}

//չʾ����ID
string TimeSchedul::ShowProgressID(TPCB& pcb) const
{
    return pcb.id;
}

//���н���, ���̽�������true, ���򷵻� false
bool TimeSchedul::RunProgress(TPCB& pcb)
{
    pcb.RunningTime++;
    if (pcb.RunningTime == pcb.RequestTime){
        pcb.State = 'E';
        ShowProgress(pcb);
        cout << pcb.id <<  " ����������ϣ��˳����̶��У���!" << endl<<endl;
        return true;
    }
    else {
        cout << pcb.id << " ���к󣬸ý�����Ϣ��Ϊ�� " << endl;
        ShowProgress(pcb);
        return false;
    }
}

//ʱ��Ƭ����������
void TimeSchedul::RunningMain()
{
    list<TPCB>::iterator it;
    int i = 1;
    for (it = progress.begin(); it != progress.end(); )
    {
        cout << "~~~~~~~~~~~~~��   " << i << "  ������~~~~~~~~~~~~" << endl;
        cout << "�������еĽ����� ��  " << ShowProgressID(*it) << endl;
        bool flag = RunProgress(*it);
        if (flag)
            progress.erase(it++);
        else
            it++;
        cout << "ʣ��Ľ���Ϊ��  " << endl;
        ShowList();

        if (it == progress.end())       //ѭ������
            it = progress.begin();
        cout << endl;
        i++;
    }
}

//�������н��������������Ҫ��ʱ��Ƭ
int TimeSchedul::CalculateTime()
{
    list<TPCB>::iterator it;
    for (it = progress.begin(); it != progress.end(); it++)
    {
        time_sum += (*it).RequestTime - (*it).RunningTime;      //Ҫ������ʱ�� - �Ѿ�����ʱ��
    }
    return time_sum;
}

#endif // TIMESCHEDUL_H_INCLUDED
