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

    bool empty() const {return pointer == 0;}       //�ж�ջ�Ƿ�Ϊ��
    int size() const {return pointer;}              //����ջ�Ĵ�С
    T top();                                        //����ջ��Ԫ��
    void push(T elem);                              //��ջ
    void pop();                                     //��ջ
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
