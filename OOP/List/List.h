#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include<iostream>
using namespace std;

template<class T>
struct Node
{
    T data;
    Node<T> *prev, *next;
    Node(T elem)
    {
        data = elem;
        prev = next = nullptr;
    }
};

template<class T>
class List
{
private:
    int length;
    Node<T> *head, *tail;
public:
    List(): length(0), head(nullptr), tail(nullptr){}
    List(const T elem);
    ~List();

    int size() const;         //返回链表元素的个数
    T back() const;               //返回最后一个元素
    T front() const;             //返回第一个元素
    void clear();                   //删除所有的元素
    bool empty() const;                    //判断链表是否为空
    void push_back(const T elem);   //在链表最后插入一个元素
    void push_front(const T elem);  //在链表头插入一个元素
    void pop_back();            //删除链表最后一个元素
    void pop_front();           //删除链表的第一个元素
    void release();
};

template<class T>
List<T>::List(const T elem):length(0), head(nullptr), tail(nullptr)
{
    push_front(elem);
}

template<class T>
List<T>::~List()
{
    release();
}

template<class T>
int List<T>::size() const
{
    return length;
}

template<class T>
T List<T>::back() const
{
    return tail->data;
}

template<class T>
T List<T>::front() const
{
    return head->data;
}

template<class T>
void List<T>::clear()
{
    while(! empty()){
        pop_front();
    }
}

template<class T>
bool List<T>::empty() const
{
    return length == 0;
}

template<class T>
void List<T>::push_back(const T elem)
{
    Node<T>* newNode = new Node<T>(elem);
    if (tail){
        tail->next = newNode;
    }
    newNode->prev = tail;

    if (tail == nullptr){
        head = newNode;
    }
    tail = newNode;

    length++;
}

template<class T>
void List<T>::push_front(const T elem)
{
    Node<T>* newNode = new Node<T>(elem);
    if (head){
        head->prev = newNode;
    }
    newNode->next = head;

    if (head == nullptr){
        tail = newNode;
    }
    head = newNode;
    length++;
}

template<class T>
void List<T>::pop_back()
{
    if (empty())
        cout<<"List is empty!!"<<endl;
    Node<T>* temp(tail);
    tail = tail->prev;
    if (tail){
        tail->next = nullptr;
    }
    else{
        head = nullptr;
    }
    delete temp;
    length--;
}

template<class T>
void List<T>::pop_front()
{
    if( empty() )
        cout<<"List is empty!!"<<endl;

    Node<T>* temp(head);
    head = head->next;
    if(head)
        head->prev = nullptr;
    else
        tail = nullptr;

    delete temp;
    length--;
}

template<class T>
void List<T>::release()
{
    while(head)
    {
        Node<T>* temp(head);
        head = head->next;
        delete temp;
        length = 0;
    }
}

#endif // LIST_H_INCLUDED
