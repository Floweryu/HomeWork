#include <iostream>
#include "PrioritySchedul.h"
#include "TimeSchedul.h"
using namespace std;

int main()
{
    cout << "*********** 优先数调度算法实现处理器调度 **************" << endl;
    Progress NewProgress;
    int UseTime = NewProgress.CalculateTime();
    cout << "运行完所有进程共需要 " << UseTime << " 个时间片" <<endl << endl;
    int i = 1;
    while (UseTime--)
    {
        cout << "~~~~~~~~~~~~~第   " << i << "  次运行~~~~~~~~~~~~" << endl;
        cout << "现在运行的进程是 ：  " << NewProgress.ShowProgressID() << endl;

        NewProgress.RunProgress();

        cout << "剩余的进程为：  " << endl;
        NewProgress.ShowQueue();            //展示剩余进程

        i++;
        cout << endl;
    }
    cout << endl << endl;

    cout << "*********** 时间片轮转法实现处理器调度 **************" << endl;
    TimeSchedul NewPro;
    int _UseTime = NewPro.CalculateTime();
    cout << "运行完所有进程共需要 " << _UseTime << " 个时间片" <<endl << endl;
    NewPro.RunningMain();
    return 0;
}
