#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<iostream>
using namespace std;

#define MAX_SIZE 65525

template<class T>
class Stack
{
private:
    int pointer;
    T base[MAX_SIZE];
public:
    Stack();
    ~Stack() {delete [] base;}

    bool empty() const {return pointer == 0;}       //判断栈是否为空
    int size() const {return pointer;}              //返回栈的大小
    T top();                                        //返回栈顶元素
    void push(T elem);                              //进栈
    void pop();                                     //出栈
};

template<class T>
Stack<T>::Stack()
{
    pointer = 0;
}

template<class T>
T Stack<T>::top()
{
    return base[pointer - 1];
}

template<class T>
void Stack<T>::push(T elem)
{
    base[pointer++] = elem;
}

template<class T>
void Stack<T>::pop()
{
    pointer--;
}

#endif // STACK_H_INCLUDED
