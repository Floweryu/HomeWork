#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class Vector
{
private:
    int max_capacity;
    int now_size;
    T *elem;
public:
    enum{ SPARE_CAPACITY = 5 };
    typedef T* iterator;
    // ���캯������������
    Vector(int initsize = 0);       //����һ��Vector����СΪinitsize
    Vector(int initsize, T value);  //����һ����СΪinitsize��Vector, ����ֵ��Ϊvalue
    ~Vector() {delete [] elem;}

    // ������Ա���������ı���ĳ�Ա��
    bool empty() const {return now_size == 0;}       // �ж��Ƿ�Ϊ��
    int size() const {return now_size;}             // ����������Ԫ�صĸ���
    int capacity() const {return max_capacity;}     // ���ص�ǰ�����������ɵ����Ԫ��ֵ
    iterator begin() {return &elem[0];}             // ����������ͷָ�룬ָ���һ��Ԫ��
    iterator end() {return &elem[now_size];}        // ����������βָ�룬ָ�����һ��Ԫ��

    // �ǳ���Ա����
    void push_back(const T &x);                     //�������������һ������
    iterator insert(iterator it,const T &value);    //�����е�����ָ��Ԫ��ǰ����һ��Ԫ��x
    void pop_back() {now_size--;}                   //ɾ�����һ����
    iterator erase(iterator it);                    //ɾ��������ָ�����
    void clear();                                   //�������������Ԫ��
    void reserve(int newcapacity);                  //������������
};

#endif // VECTOR_H_INCLUDED
