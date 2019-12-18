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
        cout<<"���������鳤��:    "<<endl;
        cin>>len;
        for (int i = 0; i < len; i++){
            a[i] = rand() % 100;
        }
        cout<<"���������Ϊ��    "<<endl;
        Print(a, len);
        sort(a, a + len);
        cout<<"�ź���������Ϊ:   "<<endl;
        Print(a, len);
        int key;
        cout<<"***********************���ֲ���******************"<<endl;
        cout<<"������Ҫ���ҵ�ֵ��    ";
        cin>>key;
        int back = binary_search(a, 0, len, key);
        if (back == -1){
            cout<<"������û��Ҫ���ҵ�ֵ"<<endl;
        }
        else{
            cout<<"����Ԫ���ڵ� "<<back+1<<" ��λ��"<<endl;
        }
        cout<<"**********************��̬����*******************"<<endl;
        back = Search(a, len, key);
        if(back != -1)
        {
            cout<<"��ֵ�ڵ� "<<back + 1<<" ��λ��"<<endl;
        }
        else
            cout<<"û��Ҫ�ҵ�ֵ!!"<<endl;
    }

    return 0;
}
