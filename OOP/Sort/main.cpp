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
    cout<<"**********************ð������**************************"<<endl;
    float a[1024];
    cout<<"���������鳤��:    ";
    cin>>len;
    srand(time(0));
    for (int i = 1; i <= len; i++){
        a[i] = rand() % NUM_MODEL / 10.0;
    }
    cout<<"ԭʼ����: "<<endl;
    Print(a, len);
    cout<<"ð������(����)����: "<<endl;
    Bubble_Sort(a, len, "up");
    Print(a, len);
    cout<<"ð������(����)����: "<<endl;
    Bubble_Sort(a, len, "down");
    Print(a, len);

    cout<<"**********************��������**************************"<<endl;
    int b[1024];
    cout<<"�����������鳤��:    ";
    cin>>len;
    srand(time(0));
    for (int i = 1; i <= len; i++){
        b[i] = rand() % NUM_MODEL;
    }
    cout<<"ԭʼ����: "<<endl;
    Print(b, len);
    cout<<"��������(����)����: "<<endl;
    Quick_Sort(b, 1, len, "up");
    Print(b, len);
    cout<<"��������(����)����: "<<endl;
    Quick_Sort(b, 1, len, "down");
    Print(b, len);

    cout<<"**********************������**************************"<<endl;
    int c[1024];
    cout<<"�����������鳤��:    ";
    cin>>len;
    srand(time(0));
    for (int i = 1; i <= len; i++){
        c[i] = rand() % NUM_MODEL;
    }
    cout<<"ԭʼ����: "<<endl;
    Print(c, len);
    cout<<"������(����)����: "<<endl;
    Heap_Sort(c, len, "up");
    Print(c, len);
    cout<<"������(����)����: "<<endl;
    Heap_Sort(c, len, "down");
    Print(c, len);
    return 0;
}
