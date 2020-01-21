#ifndef BESTFIT_H_INCLUDED
#define BESTFIT_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_SIZE 150        //�ڴ������ռ�

struct Node{
    int address;        //��ַ
    int length;         //����������
    string state;       //״̬�� ���ַ���ʾ�ѷ��䣬"0"��ʾδ����
    Node (int _address, int _length, string _state){
        address = _address;
        length = _length;
        state = _state;
    }
};

//�����Ӧ���䡪��������������Ӧ����sort������
bool LessSortByLength(const Node& a, const Node& b)
{
    return a.length < b.length;
}

//����ʼ��ַ���򡪡����������ڴ���պϲ�
bool LessSortByAddress(const Node& a, const Node& b)
{
    return a.address < b.address;
}

class BestFit
{
private:
    vector<Node> UseList;
    vector<Node> FreeList;
public:
    BestFit();
    ~BestFit(){};
    void ShowMemory();                      //չʾ���������Է������ڴ�
    bool AllocationMemory(Node & work);     //��������ڴ�
    void MergeMemory();                     //���պϲ��ڴ�
    bool ExitProgress(string & name);       //�˳�����
};

BestFit::BestFit()
{
    Node Work1(1, 20, "work1");
    Node Work3(21, 15, "work3");
    Node Work2(56, 30, "work2");
    UseList.push_back(Work1);       //work1 ռ���ڴ�
    UseList.push_back(Work3);       //work2 ռ���ڴ�
    UseList.push_back(Work2);       //work2 ռ���ڴ�

    Node Free1(36, 20, "0");
    Node Free2(86, 65, "0");
    FreeList.push_back(Free1);      //������1
    FreeList.push_back(Free2);      //������2
}

void BestFit::ShowMemory()
{
    vector<Node>::iterator it;
    cout << "**********�ѷ������������Ϣ**********" << endl;
    if (UseList.empty())
        cout << "���н��̾����˳��ڴ棡����" <<endl<<endl;
    else
    {
        for (it = UseList.begin(); it != UseList.end(); it++){
            cout << "��ʼ��ַ:   " << (*it).address
                 << "   ||  ��ռ�ڴ泤�ȣ�   "<< (*it).length
                 << "   ||  ���̵����ƣ�״̬����   " << (*it).state << endl << endl;
        }
    }

    cout << "***********�������������Ϣ**********" << endl;
    if (FreeList.empty())
        cout << "�����ڴ�������꣬�Ѿ�û�пɷ���Ŀ�����������" <<endl<<endl;
    else
    {
        for (it = FreeList.begin(); it != FreeList.end(); it++){
        cout << "��ʼ��ַ:   " << (*it).address
             << "   ||  ��ռ�ڴ泤�ȣ�   "<< (*it).length
             << "   ||  ���̵����ƣ�״̬����   " << (*it).state << endl << endl;
        }
    }

}

//�����ڴ�
bool BestFit::AllocationMemory(Node& work)
{
    sort(FreeList.begin(), FreeList.end(), LessSortByLength);     //�Կ��������е�������
    for (unsigned int i = 0; i < FreeList.size(); i++)
    {
        if (FreeList[i].length >= work.length)    //�ÿ�����������̵���Ҫ
        {
            int _length;
            int _address;
            string _state;

            if (FreeList[i].length - work.length != 0){ //�ָ��С��������С��Ϊ 0 ����Ҫ������б���
                _length = FreeList[i].length - work.length;       //ʣ���������
                _address = FreeList[i].address + work.length;     //ʣ���������ʼ��ַ
                _state = "0";                               //������
                Node NewFree(_address, _length, _state);
                FreeList.push_back(NewFree);        //������б���
            }   //�¿��������� 0 ���ù���

            _length = work.length;
            _address = FreeList[i].address;
            _state = work.state;
            Node NewUse(_address, _length, _state);       //�·���Ľ����ڴ�
            UseList.push_back(NewUse);              //���뵽��ʹ�÷������

            FreeList.erase(FreeList.begin() + i);       //�ڿ���������ɾ���ÿ�����
            break;
        }
        if (i + 1 == FreeList.size())
            return false;
    }
    return true;
}

//�˳��ڴ�
bool BestFit::ExitProgress(string& name)
{
    for (unsigned int i = 0; i < UseList.size(); i++)   //���ѷ������˳��ڴ�
    {
        if (UseList[i].state == name)
        {
            int _address;
            int _length;
            string _state;
            _address = UseList[i].address;
            _length = UseList[i].length;
            _state = "0";       //�ÿ��ڴ�ռ��Ϊ������
            Node NewFree(_address, _length, _state);
            FreeList.push_back(NewFree);        //�Ѹÿ�������ӵ��������������
            UseList.erase(UseList.begin() + i);         //���ѷ���������ɾ���ý���
            break;
        }
        if (i + 1 == UseList.size())
            return false;       //û�ҵ��ý���
    }
    return true;        //�˳����̳ɹ�
}

//�����ڴ�
void BestFit::MergeMemory()
{
    sort(FreeList.begin(), FreeList.end(), LessSortByAddress);  //����ʼ��ַ�������У��������
    for (unsigned int i = 0; i < FreeList.size() - 1; i++)
    {
        if (FreeList[i].address + FreeList[i].length == FreeList[i + 1].address)    //�������������
        {
            FreeList[i].length += FreeList[i + 1].length;       //��ӵ�ǰ����������
            FreeList.erase(FreeList.begin() + i + 1);           //�ͷź�һ�������
            i--;    //�¿��������ܻ����Ժ���һ���������ϲ�
        }
    }
}

#endif // BESTFIT_H_INCLUDED
