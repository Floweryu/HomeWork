#include<iostream>
#include<malloc.h>
#include "DiskOperate.h"
using namespace std;

#define ERROR -1        //错误信息量

char* SystemStartAddr;  //系统起始地址

//初始化系统
void InitSystem()
{
    // 分配 100M 存储 char 类型的存储空间
    SystemStartAddr = (char*)malloc(SYSTEM_SIZE * sizeof(char));

    //初始化磁盘块的位示图
    for (int i = 0; i < BLOCK_NUMBER; i++){
        SystemStartAddr[i] = '0';       // '0'表示该盘块空闲，'1'表示已被使用
    }

    //位示图占用的盘块数 = 位示图中存储的盘块个数 * 存储类型(char——'0', '1') / 每个盘块的大小
    int BitMapSize = BLOCK_NUMBER * sizeof(char) / BLOCK_SIZE;

    //从 0 开始分配，记录位示图占用的盘块
    for (int i = 0; i < BitMapSize; i++){
        SystemStartAddr[i] = '1';
    }
}

//退出系统
void ExitSystem()
{
    free(SystemStartAddr);      //释放存储空间
}

//磁盘分配————分配连续的存储空间
int GetBlock(int block_size)
{
    int StartBlock = 0;     //记录分配连续盘块的起始位置
    int block_sum = 0;      //记录已分配到盘块的数量
    for (int i= 0; i < BLOCK_NUMBER; i++)
    {
        if (SystemStartAddr[i] == '0')      //该盘块空闲
        {
            if (block_sum == 0)
                StartBlock = i;             //记录起始位置
            block_sum++;                    //记录已连续分配盘块的个数

            if (block_sum == block_size)    //找到满足数量的连续盘块
            {
                //把空闲的连续盘块置 "1"
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

//获得盘块的物理地址
char* GetBlockAddr(int block_num)
{
    return SystemStartAddr + block_num * BLOCK_SIZE;        //偏移量
}

//获得物理地址的盘块号————这里物理地址是指该盘块的起始地址或向后，所以不用把盘块号减一
int GetAddrBlock(char* addr)
{
    return (addr - SystemStartAddr) / BLOCK_SIZE;           //计算盘块的数量
}

//释放盘块
bool ReleaseBlock(int block_num, int block_size)
{
    int EndBlock = block_num + block_size;
    //修改位示图盘块的位置为0
    for (int i = block_num; i < EndBlock; i++)
        SystemStartAddr[i] = '0';
    return true;
}



