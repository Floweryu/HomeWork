#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<iostream>
using namespace std;

#define QUEUE_SIZE 520

template<class T>
class Queue
{
private:
    int now_size;
    T base[QUEUE_SIZE];
public:
    Queue():now_size(0){}
    ~Queue(){}

    bool empty() const {return now_size == 0;}
    int size() const {return now_size;}
    T front() const {return base[0];}
    T back() const {return base[now_size - 1];}
    void push(T elem);
    void pop();
};

template<class T>
void Queue<T>::push(T elem)
{
    if (now_size >= QUEUE_SIZE){
        cout<<"There is no space for new elem.."<<endl;
    }
    else{
        base[now_size++] = elem;
    }
}

template<class T>
void Queue<T>::pop()
{
    if (now_size == 0){
        cout<<"The queue is empty.."<<endl;
    }
    else{
        for (int i = 0; i < now_size - 1; i++){
            base[i] = base[i + 1];
        }
        now_size--;
    }
}
#endif // QUEUE_H_INCLUDED
