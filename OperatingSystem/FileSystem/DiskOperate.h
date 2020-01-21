#ifndef DISKOPERATE_H_INCLUDED
#define DISKOPERATE_H_INCLUDED

#define SYSTEM_SIZE 100*1024*1024   //系统大小
#define BLOCK_SIZE  1024            //盘块大小
#define BLOCK_NUMBER SYSTEM_SIZE/BLOCK_SIZE //系统盘块数目

//初始化系统
void InitSystem();

//磁盘分配
int GetBlock(int block_size);

//获得盘块的物理地址
char * GetBlockAddr(int block_num);

//获得物理地址的盘块号
int GetAddrBlock(char* addr);

//释放盘块
bool ReleaseBlock(int block_num, int block_size);

//退出系统
void ExitSystem();

#endif // DISKOPERATE_H_INCLUDED
