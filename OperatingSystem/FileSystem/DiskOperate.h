#ifndef DISKOPERATE_H_INCLUDED
#define DISKOPERATE_H_INCLUDED

#define SYSTEM_SIZE 100*1024*1024   //ϵͳ��С
#define BLOCK_SIZE  1024            //�̿��С
#define BLOCK_NUMBER SYSTEM_SIZE/BLOCK_SIZE //ϵͳ�̿���Ŀ

//��ʼ��ϵͳ
void InitSystem();

//���̷���
int GetBlock(int block_size);

//����̿�������ַ
char * GetBlockAddr(int block_num);

//��������ַ���̿��
int GetAddrBlock(char* addr);

//�ͷ��̿�
bool ReleaseBlock(int block_num, int block_size);

//�˳�ϵͳ
void ExitSystem();

#endif // DISKOPERATE_H_INCLUDED
