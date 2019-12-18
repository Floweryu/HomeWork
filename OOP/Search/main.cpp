#include <iostream>
#include <algorithm>
#include <ctime>
#include "Search.h"
using namespace std;

void Print(int *a, int length)
{
    for (int i = 0; i < length; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl<<endl;
}

int main()
{
    srand(time(0));
    int len;
    int a[1024];
    while(true)
    {
        cout<<"请输入数组长度:    "<<endl;
        cin>>len;
        for (int i = 0; i < len; i++){
            a[i] = rand() % 100;
        }
        cout<<"输入的数组为：    "<<endl;
        Print(a, len);
        sort(a, a + len);
        cout<<"排好序后的数组为:   "<<endl;
        Print(a, len);
        int key;
        cout<<"***********************二分查找******************"<<endl;
        cout<<"请输入要查找的值：    ";
        cin>>key;
        int back = binary_search(a, 0, len, key);
        if (back == -1){
            cout<<"数组中没有要查找的值"<<endl;
        }
        else{
            cout<<"查找元素在第 "<<back+1<<" 个位置"<<endl;
        }
        cout<<"**********************静态查找*******************"<<endl;
        back = Search(a, len, key);
        if(back != -1)
        {
            cout<<"此值在第 "<<back + 1<<" 个位置"<<endl;
        }
        else
            cout<<"没有要找的值!!"<<endl;
    }

    return 0;
}
