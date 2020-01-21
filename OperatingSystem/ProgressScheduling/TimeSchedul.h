#ifndef TIMESCHEDUL_H_INCLUDED
#define TIMESCHEDUL_H_INCLUDED

#include <iostream>
#include <list>
using namespace std;

struct TPCB{
    string id;              //进程名
    int RequestTime;        //要求运行时间
    int RunningTime;        //已经运行时间
    char State;             //状态:   'R'——就绪， 'E'——结束
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
    void ShowList();                            //展示链表里所有进程
    void ShowProgress(TPCB& pcb) const;         //展示进程信息
    string ShowProgressID(TPCB& pcb) const;     //展示进程ID
    bool RunProgress(TPCB& pcb);                //运行进程, 进程结束返回true, 否则返回 false
    void RunningMain();                         //时间片运行主函数
    int CalculateTime();                        //计算所有进程运行完毕所需要的时间片
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

//展示链表里所有进程
void TimeSchedul::ShowList()
{
    if (progress.empty())
        cout << "进程队列为空，进程已经全部运行完毕！！！" << endl;
    else {
        list<TPCB>::iterator it;
        for (it = progress.begin(); it != progress.end(); it++){
            cout << (*it).id << " ";
        }
        cout << endl;
    }
}

//展示进程信息
void TimeSchedul::ShowProgress(TPCB& pcb) const
{
    cout << "进程的ID为：  " << pcb.id << endl
         << "进程要求运行时间为：  " << pcb.RequestTime << endl
         << "进程已经运行时间为：  " << pcb.RunningTime << endl
         << "进程的状态为：  " << pcb.State << endl << endl;
}

//展示进程ID
string TimeSchedul::ShowProgressID(TPCB& pcb) const
{
    return pcb.id;
}

//运行进程, 进程结束返回true, 否则返回 false
bool TimeSchedul::RunProgress(TPCB& pcb)
{
    pcb.RunningTime++;
    if (pcb.RunningTime == pcb.RequestTime){
        pcb.State = 'E';
        ShowProgress(pcb);
        cout << pcb.id <<  " 进程运行完毕，退出进程队列！！!" << endl<<endl;
        return true;
    }
    else {
        cout << pcb.id << " 运行后，该进程信息变为： " << endl;
        ShowProgress(pcb);
        return false;
    }
}

//时间片运行主函数
void TimeSchedul::RunningMain()
{
    list<TPCB>::iterator it;
    int i = 1;
    for (it = progress.begin(); it != progress.end(); )
    {
        cout << "~~~~~~~~~~~~~第   " << i << "  次运行~~~~~~~~~~~~" << endl;
        cout << "现在运行的进程是 ：  " << ShowProgressID(*it) << endl;
        bool flag = RunProgress(*it);
        if (flag)
            progress.erase(it++);
        else
            it++;
        cout << "剩余的进程为：  " << endl;
        ShowList();

        if (it == progress.end())       //循环迭代
            it = progress.begin();
        cout << endl;
        i++;
    }
}

//计算所有进程运行完毕所需要的时间片
int TimeSchedul::CalculateTime()
{
    list<TPCB>::iterator it;
    for (it = progress.begin(); it != progress.end(); it++)
    {
        time_sum += (*it).RequestTime - (*it).RunningTime;      //要求运行时间 - 已经运行时间
    }
    return time_sum;
}

#endif // TIMESCHEDUL_H_INCLUDED
