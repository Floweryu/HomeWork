#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
    cout<<"*************************** Type int ********************"<<endl;
    Queue<int> q;
    for (int i = 0; i <= 11; i++){
        q.push(i);
    }
    if (q.empty()){
        cout<<"This is an empty queue.."<<endl;
    }
    else{
        cout<<"The size of the queue is "<<q.size()<<endl;
    }
    cout<<"The head of the queue is :  "<<q.front()<<"     The tail of the queue is :   "<<q.back()<<endl;
    for (int i = 0; i <= 5; i++){
        cout<<q.front()<<endl;
        q.pop();
    }
    cout<<"The size of the queue is "<<q.size()<<endl;

    cout<<"*************************** Type char ********************"<<endl;
    Queue<char> str;
    for (int i = 0; i <= 11; i++){
        str.push(i + 97);
    }
    if (str.empty()){
        cout<<"This is an empty queue.."<<endl;
    }
    else{
        cout<<"The size of the queue is "<<str.size()<<endl;
    }
    cout<<"The head of the queue is :  "<<str.front()<<"     The tail of the queue is :   "<<str.back()<<endl;
    for (int i = 0; i <= 5; i++){
        cout<<str.front()<<endl;
        str.pop();
    }
    cout<<"The size of the queue is "<<str.size()<<endl;
    return 0;
}
