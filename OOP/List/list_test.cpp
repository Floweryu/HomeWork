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
        cout<<"����Ϊ��"<<endl;
    else
        cout<<"������Ϊ�� "<<a.size()<<endl;

    cout<<"��һ��Ԫ��Ϊ:   "<<a.front()<<endl;
    cout<<"���һ��Ԫ��Ϊ��   "<<a.back()<<endl;
    a.push_front(0);
    cout<<"������Ϊ�� "<<a.size()<<"     ��һ��Ԫ��Ϊ:  "<<a.front()<<endl;
    a.pop_back();
    a.pop_front();
    cout<<"������Ϊ�� "<<a.size()<<"     ��һ��Ԫ��Ϊ:  "<<a.front()<<"    ���һ��Ԫ��Ϊ�� "<<a.back()<<endl;

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
        cout<<"����Ϊ��"<<endl;
    else
        cout<<"������Ϊ�� "<<str.size()<<endl;

    cout<<"��һ��Ԫ��Ϊ:   "<<str.front()<<endl;
    cout<<"���һ��Ԫ��Ϊ��   "<<str.back()<<endl;
    str.push_front('o');
    cout<<"������Ϊ�� "<<str.size()<<"     ��һ��Ԫ��Ϊ:  "<<str.front()<<endl;
    str.pop_back();
    str.pop_front();
    cout<<"������Ϊ�� "<<str.size()<<"     ��һ��Ԫ��Ϊ:  "<<str.front()<<"    ���һ��Ԫ��Ϊ�� "<<str.back()<<endl;
    return 0;
}
