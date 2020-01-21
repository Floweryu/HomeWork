#include<iostream>
#include<malloc.h>
#include "DiskOperate.h"
using namespace std;

#define ERROR -1        //������Ϣ��

char* SystemStartAddr;  //ϵͳ��ʼ��ַ

//��ʼ��ϵͳ
void InitSystem()
{
    // ���� 100M �洢 char ���͵Ĵ洢�ռ�
    SystemStartAddr = (char*)malloc(SYSTEM_SIZE * sizeof(char));

    //��ʼ�����̿��λʾͼ
    for (int i = 0; i < BLOCK_NUMBER; i++){
        SystemStartAddr[i] = '0';       // '0'��ʾ���̿���У�'1'��ʾ�ѱ�ʹ��
    }

    //λʾͼռ�õ��̿��� = λʾͼ�д洢���̿���� * �洢����(char����'0', '1') / ÿ���̿�Ĵ�С
    int BitMapSize = BLOCK_NUMBER * sizeof(char) / BLOCK_SIZE;

    //�� 0 ��ʼ���䣬��¼λʾͼռ�õ��̿�
    for (int i = 0; i < BitMapSize; i++){
        SystemStartAddr[i] = '1';
    }
}

//�˳�ϵͳ
void ExitSystem()
{
    free(SystemStartAddr);      //�ͷŴ洢�ռ�
}

//���̷��䡪���������������Ĵ洢�ռ�
int GetBlock(int block_size)
{
    int StartBlock = 0;     //��¼���������̿����ʼλ��
    int block_sum = 0;      //��¼�ѷ��䵽�̿������
    for (int i= 0; i < BLOCK_NUMBER; i++)
    {
        if (SystemStartAddr[i] == '0')      //���̿����
        {
            if (block_sum == 0)
                StartBlock = i;             //��¼��ʼλ��
            block_sum++;                    //��¼�����������̿�ĸ���

            if (block_sum == block_size)    //�ҵ����������������̿�
            {
                //�ѿ��е������̿��� "1"
                for (int j = StartBlock; j < StartBlock + block_size; j++)
                    SystemStartAddr[i] = '1';
                return StartBlock;
            }
        }
        else{
            block_sum = 0;
        }
    }
    cout<<"Do not find such series memory Or memory is FULL"<<endl;
    return ERROR;
}

//����̿�������ַ
char* GetBlockAddr(int block_num)
{
    return SystemStartAddr + block_num * BLOCK_SIZE;        //ƫ����
}

//��������ַ���̿�š����������������ַ��ָ���̿����ʼ��ַ��������Բ��ð��̿�ż�һ
int GetAddrBlock(char* addr)
{
    return (addr - SystemStartAddr) / BLOCK_SIZE;           //�����̿������
}

//�ͷ��̿�
bool ReleaseBlock(int block_num, int block_size)
{
    int EndBlock = block_num + block_size;
    //�޸�λʾͼ�̿��λ��Ϊ0
    for (int i = block_num; i < EndBlock; i++)
        SystemStartAddr[i] = '0';
    return true;
}



