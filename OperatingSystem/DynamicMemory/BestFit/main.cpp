#include <iostream>
#include "BestFit.h"

int main()
{
    cout << "****************最佳适应算法**************************" <<endl;
    cout << "************输入 0 ————退出程序*******************" <<endl;
    cout << "************输入 1 ————分配内存*******************" <<endl;
    cout << "************输入 2 ————回收内存*******************" <<endl;
    cout << "************输入 3 ————显示内存*******************" <<endl;
    cout << "******************************************************" <<endl;

    int command;        //输入的命令
    BestFit Memory;
    int _length;        //作业长度
    string name;        //作业名称
    bool flag;
    while (cout << "请输入命令：   ")
    {
        cin >> command;
        cout << endl;
        if (command == 0){      //退出程序
            exit(0);
        }
        else if (command == 1) { //分配内存
            cout << "请输入要分配作业的名称（string）：    ";
            cin >> name;
            cout << "请输入要分配作业所占内存的大小：（0 ~" << MAX_SIZE << "）：    ";
            cin >> _length;
            Node work(0, _length, name);
            flag = Memory.AllocationMemory(work);
            if (flag) {
                cout << "内存分配成功！！！" << endl <<endl;
                cout << "**************分配完内存后，已分配区和空闲区表信息如下**************" << endl<<endl;
                Memory.ShowMemory();
            }
            else
                cout << "未找到满足要求的空闲区！！！" << endl << endl;
        }
        else if (command == 2){ //回收内存
            cout << endl <<"请输入要退出的进程名：   ";
            cin >> name;
            cout << endl;
            flag = Memory.ExitProgress(name);
            if (flag)
                cout << "进程退出内存成功!!!" << endl<<endl;
            else
                cout << "已运行的进程中没有该进程！！！" << endl<<endl;

            Memory.MergeMemory();
            cout << "**************内存回收后分配表信息如下**************" << endl<<endl;
            Memory.ShowMemory();
        }
        else if (command == 3){
            cout << "**************内存分配表信息如下**************" << endl<<endl;
            Memory.ShowMemory();
        }
        else {
            cout << "错误命令！！！请输入一下命令：0, 1, 2, 3" << endl;
        }
    }

    return 0;
}
