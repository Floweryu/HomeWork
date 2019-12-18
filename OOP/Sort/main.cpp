#include <iostream>
#include <ctime>
#include "Sort.h"
using namespace std;

#define NUM_MODEL 100

template<class T>
void Print(T *a, int length)
{
    for (int i = 1; i <= length; i++){
        cout<<a[i]<<"  ";
    }
    cout<<endl<<endl;
}

int main()
{
    int len;
    cout<<"**********************冒泡排序**************************"<<endl;
    float a[1024];
    cout<<"请输入数组长度:    ";
    cin>>len;
    srand(time(0));
    for (int i = 1; i <= len; i++){
        a[i] = rand() % NUM_MODEL / 10.0;
    }
    cout<<"原始数组: "<<endl;
    Print(a, len);
    cout<<"冒泡排序(升序)后结果: "<<endl;
    Bubble_Sort(a, len, "up");
    Print(a, len);
    cout<<"冒泡排序(降序)后结果: "<<endl;
    Bubble_Sort(a, len, "down");
    Print(a, len);

    cout<<"**********************快速排序**************************"<<endl;
    int b[1024];
    cout<<"请再输入数组长度:    ";
    cin>>len;
    srand(time(0));
    for (int i = 1; i <= len; i++){
        b[i] = rand() % NUM_MODEL;
    }
    cout<<"原始数组: "<<endl;
    Print(b, len);
    cout<<"快速排序(升序)后结果: "<<endl;
    Quick_Sort(b, 1, len, "up");
    Print(b, len);
    cout<<"快速排序(降序)后结果: "<<endl;
    Quick_Sort(b, 1, len, "down");
    Print(b, len);

    cout<<"**********************堆排序**************************"<<endl;
    int c[1024];
    cout<<"请再输入数组长度:    ";
    cin>>len;
    srand(time(0));
    for (int i = 1; i <= len; i++){
        c[i] = rand() % NUM_MODEL;
    }
    cout<<"原始数组: "<<endl;
    Print(c, len);
    cout<<"堆排序(升序)后结果: "<<endl;
    Heap_Sort(c, len, "up");
    Print(c, len);
    cout<<"堆排序(降序)后结果: "<<endl;
    Heap_Sort(c, len, "down");
    Print(c, len);
    return 0;
}
