#ifndef FILEOPERATE_H_INCLUDED
#define FILEOPERATE_H_INCLUDED

#include<string>
using namespace std;

#define NAME_LENGTH 50          //�ļ�������
#define DIRS_LENGTH 30          //Ŀ¼����


/*Ŀ¼��ṹ
* Ŀ¼��������ļ������ļ�����
*/
typedef struct{
    string FileName;                    //Ŀ¼��
    char type;                          //�ļ����ͣ�'0'-dir��'1'-file
    int StartBlock;                     //FCB��ʼ�̿�
}DirUnit;


/*Ŀ¼��ṹ
* Ŀ¼���¼��Ŀ¼����Ŀ���Լ������洢Ŀ¼���б�
*һ��Ŀ¼��ֻռ��һ���̿飬һ��Ŀ¼���СΪ64B������һ��Ŀ¼�������ɺ�15��Ŀ¼�
*DirCount ��¼ÿ��Ŀ¼�����Ѻ��е�Ŀ¼����Ŀ��
*ϵͳ�ڳ�ʼ��ʱ�����Զ�����һ���յĸ�Ŀ¼�����ڴ����У���Ϊ�û��ĳ�ʼλ�ã�
*�û����е�Ŀ¼���ļ��������Ϊ��������״Ŀ¼�ṹ��չ����
*������һ��Ŀ¼��ʱ��ϵͳ���Զ�ΪĿ¼�����һ����Ϊ��..����Ŀ¼�ָʾ��Ŀ¼���λ��
*/
typedef struct{
    int DirCount;                   //Ŀ¼��Ŀ
    DirUnit dirs[DIRS_LENGTH];      //Ŀ¼��
}DirTable;


/*FCB�ṹ
*�ļ����ƿ�������ļ����ݵ���ʼλ�úʹ�С��
*dataSize,readptr��Ϊ�ļ��Ķ�д������׼���ģ���¼�ļ���д������ݳ��ȣ����ɳ����ļ���С�����͵�ǰ��ȡ��λ�á�
*Link��¼���ļ����������������ļ��Ĺ������ļ���������Ϊ0ʱ��ϵͳ���Ի����ļ��Ŀռ䡣
*һ��FCB��СΪ20B����Ҳ��һ���̿鱣�档
*���ڲ��õ����������䷽ʽ������ϵͳ�涨�ļ�������ʱ����������ļ��Ĵ�С�����Һ���Ҳ�����޸��ļ��Ĵ�С��
*/
typedef struct {
    int DataSize;          //��д������ݵĴ�С���ֽ�Ϊ��λ
    int FileSize;          //�ļ��Ĵ�С, �̿�Ϊ��λ
    int BlockNum;          //�ļ�������ʼ�̿�
    int ReadPtr;           //��ָ��
    int link;              //�ļ�������
}FCB;

//��ʼ����Ŀ¼
void InitRootDir();

//��þ���·��
string GetPath();

//չʾ��ǰĿ¼��������dir
void ShowDir();

//�л�Ŀ¼��������cd
bool ChangeDir(string DirName);

//�޸��ļ�����Ŀ¼����������mv
bool ChangeName(string OldName, string NewName);

//�����ļ���������create
bool CreateFile(string FileName, int FileSize);

//����Ŀ¼��������mkdir
bool CreateDir(string DirName);

//ɾ���ļ���������rm
bool DeleteFile(string FileName);

//�ͷ��ļ��ڴ�
bool ReleaseFile(int FcbBlock);

//ɾ��Ŀ¼��
bool DeleteDirUnit(DirTable* MyDirTable, int UnitIndex);

//ɾ��Ŀ¼��������rmdir
bool DeleteDir(string DirName);

//ɾ���ļ�/Ŀ¼��
bool DeleteFileOrTable(DirTable* MyDirTable, int UnitIndex);

//����FCB
bool CreateFCB(int FcbBlockNum, int FileBlockNum, int FileSize);

//���Ŀ¼��
bool AddDirUnit(DirTable* MyDirTable, string FileName, char type, int FcbBlockNum);

//��Ŀ¼���в���Ŀ¼
int FindUnitInTable(DirTable* MyDirTable, string UnitName);

#endif // FILEOPERATE_H_INCLUDED
