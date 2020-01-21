#ifndef PRIORITYSCHEDUL_H_INCLUDED
#define PRIORITYSCHEDUL_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct PCB{
    string id;      //���̱�ʾ��
    int priority;   //����������
    int time;       //Ҫ������ʱ��
    char state;     //"R" ��ʾ������"E" ��ʾ����
    PCB(string _id, int _priority, int _time, char _state){
        id = _id;
        priority = _priority;
        time = _time;
        state = _state;
    }
    bool operator<(const PCB& temp) const{
        return priority < temp.priority;        //�Ӵ�С
    }
};

class Progress
{
private:
    priority_queue<PCB> progresses;         //�洢���̵����ȶ���
    int time_sum;     //�����ܵ�ʱ��Ƭ��
public:
    Progress();
    ~Progress() {};
    void ShowQueue();                         //չʾ���̶���������н���ID
    void ShowProgress(PCB& pcb) const;        //չʾ���������Ľ�����Ϣ
    string ShowProgressID() const;            //չʾ���̵�ID
    int CalculateTime();                      //�������н��������������Ҫ��ʱ��Ƭ
    void RunProgress();                       //���ж��׽���(����������Ľ���)
    bool CheckState(PCB& pcb) const;          //�����̵�״̬
};

Progress::Progress()
{
    PCB P1("P1", 1, 2, 'R');
    PCB P2("P2", 5, 3, 'R');
    PCB P3("P3", 3, 1, 'R');
    PCB P4("P4", 4, 2, 'R');
    PCB P5("P5", 2, 4, 'R');
    progresses.push(P1);
    progresses.push(P2);
    progresses.push(P3);
    progresses.push(P4);
    progresses.push(P5);
    time_sum = 0;
}

//չʾ���̶���������н���ID
void Progress::ShowQueue()
{
    if (progresses.empty())
        cout << "���̶���Ϊ�գ������Ѿ�ȫ��������ϣ�����" << endl;
    else {
        priority_queue<PCB> prog = progresses;
        while (! prog.empty())
        {
            cout << prog.top().id << " ";
            prog.pop();
        }
        cout << endl;
    }
}

string Progress::ShowProgressID() const
{
    return progresses.top().id;
}

void Progress::ShowProgress(PCB& pcb) const
{
    cout << "���̵�IDΪ��  " << pcb.id << endl
         << "���̵�������Ϊ��  " << pcb.priority << endl
         << "���̵�����ʱ��Ϊ��  " << pcb.time << endl
         << "���̵�״̬Ϊ��  " << pcb.state << endl << endl;
}

//�������н��������������Ҫ��ʱ��Ƭ
int Progress::CalculateTime()
{
    priority_queue<PCB> prog = progresses;
    while (! prog.empty())
    {
        time_sum += prog.top().time;
        prog.pop();
    }
    return time_sum;
}

//�������Ƿ��������
bool Progress::CheckState(PCB& pcb) const
{
    if (pcb.time == 0)
        return true;
    else
        return false;
}

//���н���
void Progress::RunProgress()
{
    PCB running = progresses.top();         //��ȡ���������Ľ���
    progresses.pop();                       //���̳��ӣ����޸���ֵ��Ľ��������

    //�޸Ĳ���ֵ
    running.time--;
    running.priority--;
    running.priority = max(running.priority, 0);  //����������Ϊ0

    if (CheckState(running)){               //���ý����Ƿ������꣬������Ͳ��������
        running.state = 'E';
        cout << running.id << " ��ʱ����ϢΪ�� " << endl;
        ShowProgress(running);
        cout << running.id << " ������ϣ��˳����̶��� ����" << endl << endl;
    }
    else{           //û��������
        cout << running.id << " ���к󣬸ý�����Ϣ��Ϊ�� " << endl;
        ShowProgress(running);
        progresses.push(running);               //���޸��������ĸĽ������
    }

}

#endif // PRIORITYSCHEDUL_H_INCLUDED
