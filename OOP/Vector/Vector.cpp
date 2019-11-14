#include "Vector.h"

template <class T>
Vector<T>::Vector(int initsize):now_size(initsize), max_capacity(initsize + SPARE_CAPACITY)
{
    elem = new T[max_capacity];
    assert(elem != NULL);                           //�洢ʧ���˳�
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

//����Ԫ�ؿռ�
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

/*********************************�������*******************************/
//��β������
template<class T>
void Vector<T>::push_back(const T &value)
{
    if (now_size == max_capacity){
        reserve(2 * max_capacity);
    }
    elem[now_size++] = value;
}

//�����⴦����
template<class T>
T* Vector<T>::insert(iterator b, const T &value)
{
    if (b < this->begin() || b > this->end()){
        cout<<"Out of range!!!"<<endl;
        exit(0);
    }
    int num = b - elem;
    if (now_size == max_capacity){      // ��������
        reserve(2 * now_size);
        b = elem + num;                 //���¶�λ
    }
    for (iterator p = this->end(); p > b; p--){
        *p = *(p - 1);                  //Ԫ�������һλ
    }
    *b = value;
    now_size++;
    return b;
}

//ɾ��
template<class T>
T* Vector<T>::erase(iterator b)
{
    if (b < this->begin() || b >= this->end())  //ȷ���������ڷ�Χ�ڣ�����δ���壬b����Ϊβ�������
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
    if (now_size <= max_capacity / 4)           //��ֹɾ������пռ�̫���˷ѿռ�
    {
        reserve(now_size + SPARE_CAPACITY);
        iterator q1 = elem + num;                //���½����ڴ�����ԭ����ָ��q����ʧЧ��
        return q1;
    }
    return q;
}

// �������
template<typename T>
void Vector<T>::clear()
{
    now_size = 0;
}
