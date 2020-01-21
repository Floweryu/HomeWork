#ifndef PRIORITYSCHEDUL_H_INCLUDED
#define PRIORITYSCHEDUL_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct PCB{
    string id;      //进程表示符
    int priority;   //进程优先数
    int time;       //要求运行时间
    char state;     //"R" 表示就绪，"E" 表示结束
    PCB(string _id, int _priority, int _time, char _state){
        id = _id;
        priority = _priority;
        time = _time;
        state = _state;
    }
    bool operator<(const PCB& temp) const{
        return priority < temp.priority;        //从大到小
    }
};

class Progress
{
private:
    priority_queue<PCB> progresses;         //存储进程的优先队列
    int time_sum;     //计算总的时间片数
public:
    Progress();
    ~Progress() {};
    void ShowQueue();                         //展示进程队列里的所有进程ID
    void ShowProgress(PCB& pcb) const;        //展示优先数最大的进程信息
    string ShowProgressID() const;            //展示进程的ID
    int CalculateTime();                      //计算所有进程运行完成所需要的时间片
    void RunProgress();                       //运行队首进程(即优先数大的进程)
    bool CheckState(PCB& pcb) const;          //检查进程的状态
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

//展示进程队列里的所有进程ID
void Progress::ShowQueue()
{
    if (progresses.empty())
        cout << "进程队列为空，进程已经全部运行完毕！！！" << endl;
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
    cout << "进程的ID为：  " << pcb.id << endl
         << "进程的优先数为：  " << pcb.priority << endl
         << "进程的运行时间为：  " << pcb.time << endl
         << "进程的状态为：  " << pcb.state << endl << endl;
}

//计算所有进程运行完成所需要的时间片
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

//检查进程是否运行完毕
bool Progress::CheckState(PCB& pcb) const
{
    if (pcb.time == 0)
        return true;
    else
        return false;
}

//运行进程
void Progress::RunProgress()
{
    PCB running = progresses.top();         //获取优先数最大的进程
    progresses.pop();                       //进程出队，把修改数值后的进程再入队

    //修改参数值
    running.time--;
    running.priority--;
    running.priority = max(running.priority, 0);  //优先数不能为0

    if (CheckState(running)){               //检查该进程是否运行完，运行完就不用再入队
        running.state = 'E';
        cout << running.id << " 此时的信息为： " << endl;
        ShowProgress(running);
        cout << running.id << " 运行完毕，退出进程队列 ！！" << endl << endl;
    }
    else{           //没有运行完
        cout << running.id << " 运行后，该进程信息变为： " << endl;
        ShowProgress(running);
        progresses.push(running);               //把修改完参数后的改进程入队
    }

}

#endif // PRIORITYSCHEDUL_H_INCLUDED
