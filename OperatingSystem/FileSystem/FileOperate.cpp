#include "FileOperate.h"
#include "DiskOperate.h"
#include<iostream>
#include<string>
using namespace std;

#define ERROR -1

DirTable* RootDirTable;     //��Ŀ¼
DirTable* CurrentDirTable;  //��ǰλ��
string path;                //���浱ǰ����·��

//��ʼ����Ŀ¼
void InitRootDir()
{
    //����һ���̿�ռ��RootDirTable
    int StartBlock = GetBlock(1);
    if (StartBlock == ERROR){
        cout<<"�̿�ռ����ʧ�ܣ���"<<endl;
        return;
    }
    RootDirTable = (DirTable*)GetBlockAddr(StartBlock);
    RootDirTable->DirCount = 0;      //Ŀ¼����ʼ��Ϊ0
    CurrentDirTable = RootDirTable; //��ǰĿ¼���Ǹ�Ŀ¼
    //��ʼ������·��
    path = "/User";
}

//��þ���·��
string GetPath()
{
    return path;
}

//չʾ��ǰĿ¼����dir
void ShowDir()
{
    int UnitNumber = CurrentDirTable->DirCount;
    cout << "��ǰĿ¼����  " << UnitNumber << endl << endl;
    //��������Ŀ¼����
    for (int i = 0; i < UnitNumber; i++)
    {
        //���Ŀ¼��
        DirUnit UnitTemp = CurrentDirTable->dirs[i];
        cout << "��ǰĿ¼��Ϊ�� " << UnitTemp.FileName << endl;
        if (UnitTemp.type == '0')
            cout << "Ŀ¼����Ϊ��  Ŀ¼ "<< endl;
        else
            cout << "Ŀ¼����Ϊ��  �ļ� "<< endl;

        if (UnitTemp.type == '1')   //������ļ�
        {
            int FcbBlock = UnitTemp.StartBlock;             //�õ��ļ�����ʼ�̿�
            FCB* FileFcb = (FCB*)GetBlockAddr(FcbBlock);    //�õ��̿�������ַ
            cout << "�ļ��Ĵ�СΪ��  " << FileFcb->FileSize << endl
                 << "�ļ�����ʼ�̿�Ϊ��  " << FcbBlock << endl
                 << "�ļ��Ľ����̿�ţ�  " <<FileFcb->BlockNum <<endl;
        }
        else{       //��Ŀ¼
            int DirBlock = UnitTemp.StartBlock;
            DirTable* MyTable = (DirTable*)GetBlockAddr(DirBlock);
            cout << "Ŀ¼����ļ���Ŀ��  " << MyTable->DirCount <<endl
                 << "Ŀ¼����ʼ�̿飺    " << DirBlock <<endl;
        }
        cout << endl;
    }
}

//�л�Ŀ¼��������cd �����뵱ǰĿ¼�µ���һ��Ŀ¼
bool ChangeDir(string DirName)
{
    //Ŀ¼��Ŀ¼���е�λ��
    int UnitIndex = FindUnitInTable(CurrentDirTable, DirName);
    if (UnitIndex == ERROR){    //������
        cout << "File not find !!!" << endl;
        return false;
    }
    if (CurrentDirTable->dirs[UnitIndex].type == '1'){   //����һ��Ŀ¼
        cout << "Not a dir !!!" << endl;
        return false;
    }
    /********�����Ŀ¼**********/
    int DirBlock = CurrentDirTable->dirs[UnitIndex].StartBlock;
    CurrentDirTable = (DirTable*)GetBlockAddr(DirBlock);        //��ǰĿ¼ָ��ָ��Ҫ�л���Ŀ¼
    //�޸ľ���·��
    if (DirName == "..")    //������л�������Ŀ¼
    {
        //����·��
        int len = path.length();
        for (int i = len - 2; i >= 0; i--)
        {
            if (path[i] == '/'){
                path.erase(i);      //ɾ�� '/' �����·��
                break;
            }
        }
    }
    else{   //���򣬽��뵱ǰĿ¼����һ��Ŀ¼
        path += "/" + DirName;          //���� Dirname����Ҫ���� '/'
    }
    return true;
}

//�޸��ļ�����Ŀ¼���������� mv
bool ChangeName(string OldName, string NewName)
{
    int UnitIndex = FindUnitInTable(CurrentDirTable, OldName);
    if (UnitIndex == ERROR){
        cout << "Can not find file!!!" << endl;
        return false;
    }

    CurrentDirTable->dirs[UnitIndex].FileName = NewName;     //��Ŀ¼���и�������
    return true;
}

//�����ļ���������create
bool CreateFile(string FileName, int FileSize)
{
    if (FileName.length() >= NAME_LENGTH)
    {
        cout << "The file name is too long!!!" << endl;
        return false;
    }
    int FcbBlock = GetBlock(1);     //��ø��ļ���FCB�ռ�
    if (FcbBlock == ERROR)
        return false;

    int FileBlock = GetBlock(FileSize);     //��ȡ�ļ����ݿռ�
    if (FileBlock == ERROR)
        return false;

    if (CreateFCB(FcbBlock, FileBlock, FileSize) == false)  //����FCB
        return false;

    if (AddDirUnit(CurrentDirTable, FileName, '1', FcbBlock) == false)    //��ӵ�Ŀ¼��
        return false;

    return true;
}

//����Ŀ¼��������mkdir
bool CreateDir(string DirName)
{
    if (DirName.length() >= 50){
        cout << "The file name is too long!!!" << endl;
        return false;
    }

    int DirBlock = GetBlock(1);     //ΪĿ¼�����ռ�
    if (DirBlock == ERROR)
        return false;

    if (AddDirUnit(CurrentDirTable, DirName, '0', DirBlock) == false)   //��Ŀ¼����ӵ���ǰĿ¼
        return false;

    //Ϊ�½���Ŀ¼���һ����Ŀ¼��
    DirTable* NewTable = (DirTable*)GetBlockAddr(DirBlock);
    NewTable->DirCount = 0;
    string parent = "..";
    if (AddDirUnit(NewTable, parent, '0', GetAddrBlock((char*)CurrentDirTable)) == false)
        return false;

    return true;
}

//����FCB
bool CreateFCB(int FcbBlockNum, int FileBlockNum, int FileSize)
{
    //�ҵ�FCB�Ĵ洢λ��
    FCB* CurrentFCB = (FCB*)GetBlockAddr(FcbBlockNum);
    CurrentFCB->BlockNum = FileBlockNum;     //�ļ������̿�λ��
    CurrentFCB->FileSize = FileSize;         //�ļ��Ĵ�С
    CurrentFCB->link = 1;                    //�ļ������Ӹ���
    CurrentFCB->DataSize = 0;                //��д���ļ���������
    CurrentFCB->ReadPtr = 0;                 //�ļ��Ķ�ָ��

    return true;
}

//���Ŀ¼��
bool AddDirUnit(DirTable* MyDirTable, string FileName, char type, int FcbBlockNum)
{
    int DirNumber = MyDirTable->DirCount;
    if (DirNumber == DIRS_LENGTH){  //���Ŀ¼�������Ƿ񳬱�
        cout << "The dir is full, try to delete some files !!!" << endl;
        return false;
    }

    //����ļ����Ƿ��Ѿ�����
    if (FindUnitInTable(MyDirTable, FileName) != ERROR){
        cout << "The file already exits" << endl;
        return false;
    }

    //���ڴ�0��ʼ���㣬������Ŀ���ǵ�ǰ����ռ����ʼλ��
    DirUnit* NewDir = &MyDirTable->dirs[DirNumber];
    MyDirTable->DirCount++;

    //������Ŀ¼������
    NewDir->FileName = FileName;
    NewDir->type = type;
    NewDir->StartBlock = FcbBlockNum;

    return true;
}

//ɾ���ļ���������rm
bool DeleteFile(string FileName)
{
    //����ϵͳ�Զ������ĸ�Ŀ¼
    if (FileName == ".."){
        cout << "Can not delete !!!" << endl;
        return false;
    }

    //�����ļ���Ŀ¼��λ��
    int UnitIndex = FindUnitInTable(CurrentDirTable, FileName);
    if (UnitIndex == ERROR){
        cout << "File not found !!!" << endl;
        return false;
    }
    DirUnit TempUnit = CurrentDirTable->dirs[UnitIndex];
    //�ж�����
    if (TempUnit.type == '0'){
        cout << "This is not a file !!!" << endl;
        return false;
    }

    int FcbBlock = TempUnit.StartBlock;     //�ҵ��ļ����̿�

    //�ͷ��ڴ�
    ReleaseFile(FcbBlock);
    //��Ŀ¼����ɾ��
    DeleteDirUnit(CurrentDirTable, UnitIndex);

    return true;
}

//�ͷ��ļ��ڴ�
bool ReleaseFile(int FcbBlock)
{
    FCB* TempFCB = (FCB*)GetBlockAddr(FcbBlock);
    if (--TempFCB->link == 0)        //��������һ����û������
        ReleaseBlock(TempFCB->BlockNum, TempFCB->FileSize);     //�ͷ��̿�ռ�

    //�ͷ�FCB�ռ�
    ReleaseBlock(FcbBlock, 1);
    return true;
}

//ɾ��Ŀ¼��
bool DeleteDirUnit(DirTable* MyDirTable, int UnitIndex)
{
    int DirUnitNumber = MyDirTable->DirCount;
    for (int i = UnitIndex; i < DirUnitNumber - 1; i++)     //����ɾ��
        MyDirTable->dirs[i] = MyDirTable->dirs[i + 1];

    MyDirTable->DirCount--;

    return true;
}

//ɾ��Ŀ¼��������rmdir
bool DeleteDir(string DirName)
{
    if (DirName == ".."){
        cout << "Can not delete .." << endl;
        return false;
    }

    int DirIndex = FindUnitInTable(CurrentDirTable, DirName);
    if (DirIndex == ERROR){
        cout << "Cannot find the file !!!" << endl;
        return false;
    }

    DirUnit TempDir = CurrentDirTable->dirs[DirIndex];
    if (TempDir.type == '0')
        DeleteFileOrTable(CurrentDirTable, DirIndex);
    else{
        cout << "Is not a dir" << endl;
        return false;
    }

    //��Ŀ¼����ɾ��
    DeleteDirUnit(CurrentDirTable, DirIndex);

    return true;
}

//ɾ���ļ� / Ŀ¼��
bool DeleteFileOrTable(DirTable* MyDirTable, int UnitIndex)
{
    DirUnit TempUnit = MyDirTable->dirs[UnitIndex];

    if (TempUnit.type == '0')       //Ŀ¼
    {
        int FcbBlock = TempUnit.StartBlock;
        DirTable* table = (DirTable*)GetBlockAddr(FcbBlock);

        cout << "Delete dir " <<TempUnit.FileName<<endl;
        int UnitCount = table->DirCount;
        for (int i = 1; i < UnitCount; i++){
            cout << "Now delete the " << i << " %%%%%% " <<table->dirs[i].FileName<<endl;
            DeleteFileOrTable(table, i);
        }

        ReleaseBlock(FcbBlock, 1);      //�ͷ��̿�
    }
    else{       //�ļ��Ϳ���ֱ��ɾ��
        int FcbBlock = TempUnit.StartBlock;
        ReleaseFile(FcbBlock);
    }

    return true;
}

//��Ŀ¼�в���Ŀ¼��Ŀ
int FindUnitInTable(DirTable* MyDirTable, string UnitName)
{
    int DirNumber = MyDirTable->DirCount;
    int UnitIndex = ERROR;
    for (int i = 0; i < DirNumber; i++)     //����Ŀ¼���ҵ�Ŀ¼���ڵ�λ��
    {
        if (UnitName == MyDirTable->dirs[i].FileName)
            UnitIndex = i;
    }
    return UnitIndex;
}








