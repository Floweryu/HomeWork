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
    // 构造函数和析构函数
    Vector(int initsize = 0);       //创建一个Vector，大小为initsize
    Vector(int initsize, T value);  //创建一个大小为initsize的Vector, 并且值都为value
    ~Vector() {delete [] elem;}

    // 常量成员函数，不改变类的成员，
    bool empty() const {return now_size == 0;}       // 判断是否为空
    int size() const {return now_size;}             // 返回向量中元素的个数
    int capacity() const {return max_capacity;}     // 返回当前向量所能容纳的最大元素值
    iterator begin() {return &elem[0];}             // 返回向量的头指针，指向第一个元素
    iterator end() {return &elem[now_size];}        // 返回向量的尾指针，指向最后一个元素

    // 非常成员函数
    void push_back(const T &x);                     //在数组的最后添加一个数据
    iterator insert(iterator it,const T &value);    //向量中迭代器指向元素前增加一个元素x
    void pop_back() {now_size--;}                   //删除最后一个数
    iterator erase(iterator it);                    //删除迭代器指向的数
    void clear();                                   //清空向量中所有元素
    void reserve(int newcapacity);                  //重新设置容量
};

#endif // VECTOR_H_INCLUDED
