#ifndef BESTFIT_H_INCLUDED
#define BESTFIT_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_SIZE 150        //内存区最大空间

struct Node{
    int address;        //地址
    int length;         //空闲区长度
    string state;       //状态， 有字符表示已分配，"0"表示未分配
    Node (int _address, int _length, string _state){
        address = _address;
        length = _length;
        state = _state;
    }
};

//最佳适应分配————降序排序，应用与sort函数中
bool LessSortByLength(const Node& a, const Node& b)
{
    return a.length < b.length;
}

//按起始地址升序————方便内存回收合并
bool LessSortByAddress(const Node& a, const Node& b)
{
    return a.address < b.address;
}

class BestFit
{
private:
    vector<Node> UseList;
    vector<Node> FreeList;
public:
    BestFit();
    ~BestFit(){};
    void ShowMemory();                      //展示空闲区和以分配区内存
    bool AllocationMemory(Node & work);     //分配进程内存
    void MergeMemory();                     //回收合并内存
    bool ExitProgress(string & name);       //退出进程
};

BestFit::BestFit()
{
    Node Work1(1, 20, "work1");
    Node Work3(21, 15, "work3");
    Node Work2(56, 30, "work2");
    UseList.push_back(Work1);       //work1 占用内存
    UseList.push_back(Work3);       //work2 占用内存
    UseList.push_back(Work2);       //work2 占用内存

    Node Free1(36, 20, "0");
    Node Free2(86, 65, "0");
    FreeList.push_back(Free1);      //空闲区1
    FreeList.push_back(Free2);      //空闲区2
}

void BestFit::ShowMemory()
{
    vector<Node>::iterator it;
    cout << "**********已分配区分配表信息**********" << endl;
    if (UseList.empty())
        cout << "所有进程均已退出内存！！！" <<endl<<endl;
    else
    {
        for (it = UseList.begin(); it != UseList.end(); it++){
            cout << "起始地址:   " << (*it).address
                 << "   ||  所占内存长度：   "<< (*it).length
                 << "   ||  进程的名称（状态）：   " << (*it).state << endl << endl;
        }
    }

    cout << "***********空闲区分配表信息**********" << endl;
    if (FreeList.empty())
        cout << "所有内存均已用完，已经没有可分配的空闲区！！！" <<endl<<endl;
    else
    {
        for (it = FreeList.begin(); it != FreeList.end(); it++){
        cout << "起始地址:   " << (*it).address
             << "   ||  所占内存长度：   "<< (*it).length
             << "   ||  进程的名称（状态）：   " << (*it).state << endl << endl;
        }
    }

}

//分配内存
bool BestFit::AllocationMemory(Node& work)
{
    sort(FreeList.begin(), FreeList.end(), LessSortByLength);     //对空闲区进行递增排序
    for (unsigned int i = 0; i < FreeList.size(); i++)
    {
        if (FreeList[i].length >= work.length)    //该空闲区满足进程的需要
        {
            int _length;
            int _address;
            string _state;

            if (FreeList[i].length - work.length != 0){ //分割的小空闲区大小不为 0 ，就要加入空闲表中
                _length = FreeList[i].length - work.length;       //剩余空闲区大
                _address = FreeList[i].address + work.length;     //剩余空闲区起始地址
                _state = "0";                               //空闲区
                Node NewFree(_address, _length, _state);
                FreeList.push_back(NewFree);        //加入空闲表中
            }   //新空闲区等于 0 不用管它

            _length = work.length;
            _address = FreeList[i].address;
            _state = work.state;
            Node NewUse(_address, _length, _state);       //新分配的进程内存
            UseList.push_back(NewUse);              //加入到已使用分配表中

            FreeList.erase(FreeList.begin() + i);       //在空闲区表中删除该空闲区
            break;
        }
        if (i + 1 == FreeList.size())
            return false;
    }
    return true;
}

//退出内存
bool BestFit::ExitProgress(string& name)
{
    for (unsigned int i = 0; i < UseList.size(); i++)   //从已分配区退出内存
    {
        if (UseList[i].state == name)
        {
            int _address;
            int _length;
            string _state;
            _address = UseList[i].address;
            _length = UseList[i].length;
            _state = "0";       //该块内存空间变为空闲区
            Node NewFree(_address, _length, _state);
            FreeList.push_back(NewFree);        //把该空闲区添加到空闲区分配表中
            UseList.erase(UseList.begin() + i);         //从已分配分配表中删除该进程
            break;
        }
        if (i + 1 == UseList.size())
            return false;       //没找到该进程
    }
    return true;        //退出进程成功
}

//回收内存
void BestFit::MergeMemory()
{
    sort(FreeList.begin(), FreeList.end(), LessSortByAddress);  //按起始地址升序排列，方便回收
    for (unsigned int i = 0; i < FreeList.size() - 1; i++)
    {
        if (FreeList[i].address + FreeList[i].length == FreeList[i + 1].address)    //如果空闲区相邻
        {
            FreeList[i].length += FreeList[i + 1].length;       //添加到前个空闲区上
            FreeList.erase(FreeList.begin() + i + 1);           //释放后一块空闲区
            i--;    //新空闲区可能还可以和下一个空闲区合并
        }
    }
}

#endif // BESTFIT_H_INCLUDED
