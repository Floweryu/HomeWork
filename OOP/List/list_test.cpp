#include <iostream>
#include "List.h"
using namespace std;

int main()
{
    cout<<"********************** Type int ***********************"<<endl;
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    if (a.empty())
        cout<<"链表为空"<<endl;
    else
        cout<<"链表长度为： "<<a.size()<<endl;

    cout<<"第一个元素为:   "<<a.front()<<endl;
    cout<<"最后一个元素为：   "<<a.back()<<endl;
    a.push_front(0);
    cout<<"链表长度为： "<<a.size()<<"     第一个元素为:  "<<a.front()<<endl;
    a.pop_back();
    a.pop_front();
    cout<<"链表长度为： "<<a.size()<<"     第一个元素为:  "<<a.front()<<"    最后一个元素为： "<<a.back()<<endl;

    cout<<"********************** Type char ***********************"<<endl;
    List<char> str;
    str.push_back('a');
    str.push_back('b');
    str.push_back('c');
    str.push_back('d');
    str.push_back('e');
    str.push_back('f');
    str.push_back('g');
    str.push_back('h');
    str.push_back('i');
    if (str.empty())
        cout<<"链表为空"<<endl;
    else
        cout<<"链表长度为： "<<str.size()<<endl;

    cout<<"第一个元素为:   "<<str.front()<<endl;
    cout<<"最后一个元素为：   "<<str.back()<<endl;
    str.push_front('o');
    cout<<"链表长度为： "<<str.size()<<"     第一个元素为:  "<<str.front()<<endl;
    str.pop_back();
    str.pop_front();
    cout<<"链表长度为： "<<str.size()<<"     第一个元素为:  "<<str.front()<<"    最后一个元素为： "<<str.back()<<endl;
    return 0;
}
