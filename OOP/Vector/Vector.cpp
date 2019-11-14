#include "Vector.h"

template <class T>
Vector<T>::Vector(int initsize):now_size(initsize), max_capacity(initsize + SPARE_CAPACITY)
{
    elem = new T[max_capacity];
    assert(elem != NULL);                           //存储失败退出
}

template <class T>
Vector<T>::Vector(int initsize, T value):now_size(initsize), max_capacity(initsize + SPARE_CAPACITY)
{
    elem = new T[max_capacity];
    assert(elem != NULL);
    for (int i = 0; i != now_size; i++){
        elem[i] = value;
    }
}

//分配元素空间
template<class T>
void Vector<T>::reserve(int newcapacity)
{
    if (newcapacity <= max_capacity)
    {
        if (newcapacity < max_capacity / 2)
        {
            T *newarray = new T[newcapacity];
            int newsize = newcapacity > now_size ? now_size : newcapacity;
            for (int i = 0; i != newsize; ++i){
                newarray[i] = elem[i];
            }
            delete [] elem;
            elem = newarray;
            max_capacity = newcapacity;
        }
        return;
    }
    T *newarray = new T[newcapacity];
    for (int i = 0; i != now_size; ++i){
        newarray[i] = elem[i];
    }
    delete [] elem;
    elem = newarray;
    max_capacity = newcapacity;
}

/*********************************插入操作*******************************/
//在尾部插入
template<class T>
void Vector<T>::push_back(const T &value)
{
    if (now_size == max_capacity){
        reserve(2 * max_capacity);
    }
    elem[now_size++] = value;
}

//在任意处插入
template<class T>
T* Vector<T>::insert(iterator b, const T &value)
{
    if (b < this->begin() || b > this->end()){
        cout<<"Out of range!!!"<<endl;
        exit(0);
    }
    int num = b - elem;
    if (now_size == max_capacity){      // 容量不够
        reserve(2 * now_size);
        b = elem + num;                 //从新定位
    }
    for (iterator p = this->end(); p > b; p--){
        *p = *(p - 1);                  //元素向后移一位
    }
    *b = value;
    now_size++;
    return b;
}

//删除
template<class T>
T* Vector<T>::erase(iterator b)
{
    if (b < this->begin() || b >= this->end())  //确保迭代器在范围内，否则未定义，b不能为尾后迭代器
    {
        cout << "Out of range!!!" << endl;
        exit(0);
    }
    iterator q = b + 1;
    int num = q - elem;
    iterator p = this->end() - 1;
    for (; b < p; b++)
        *b = *(b + 1);
    now_size--;
    if (now_size <= max_capacity / 4)           //防止删除后空闲空间太大，浪费空间
    {
        reserve(now_size + SPARE_CAPACITY);
        iterator q1 = elem + num;                //重新进行内存分配后原来的指针q可能失效了
        return q1;
    }
    return q;
}

// 清空向量
template<typename T>
void Vector<T>::clear()
{
    now_size = 0;
}
