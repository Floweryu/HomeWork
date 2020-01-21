#include "FileOperate.h"
#include "DiskOperate.h"
#include<iostream>
#include<string>
using namespace std;

#define ERROR -1

DirTable* RootDirTable;     //根目录
DirTable* CurrentDirTable;  //当前位置
string path;                //保存当前绝对路径

//初始化根目录
void InitRootDir()
{
    //分配一个盘块空间给RootDirTable
    int StartBlock = GetBlock(1);
    if (StartBlock == ERROR){
        cout<<"盘块空间分配失败！！"<<endl;
        return;
    }
    RootDirTable = (DirTable*)GetBlockAddr(StartBlock);
    RootDirTable->DirCount = 0;      //目录数初始化为0
    CurrentDirTable = RootDirTable; //当前目录就是根目录
    //初始化绝对路径
    path = "/User";
}

//获得绝对路径
string GetPath()
{
    return path;
}

//展示当前目录——dir
void ShowDir()
{
    int UnitNumber = CurrentDirTable->DirCount;
    cout << "当前目录数：  " << UnitNumber << endl << endl;
    //遍历所有目录表项
    for (int i = 0; i < UnitNumber; i++)
    {
        //获得目录项
        DirUnit UnitTemp = CurrentDirTable->dirs[i];
        cout << "当前目录名为： " << UnitTemp.FileName << endl;
        if (UnitTemp.type == '0')
            cout << "目录类型为：  目录 "<< endl;
        else
            cout << "目录类型为：  文件 "<< endl;

        if (UnitTemp.type == '1')   //如果是文件
        {
            int FcbBlock = UnitTemp.StartBlock;             //得到文件的起始盘块
            FCB* FileFcb = (FCB*)GetBlockAddr(FcbBlock);    //得到盘块的物理地址
            cout << "文件的大小为：  " << FileFcb->FileSize << endl
                 << "文件的起始盘块为：  " << FcbBlock << endl
                 << "文件的结束盘块号：  " <<FileFcb->BlockNum <<endl;
        }
        else{       //是目录
            int DirBlock = UnitTemp.StartBlock;
            DirTable* MyTable = (DirTable*)GetBlockAddr(DirBlock);
            cout << "目录里的文件数目：  " << MyTable->DirCount <<endl
                 << "目录的起始盘块：    " << DirBlock <<endl;
        }
        cout << endl;
    }
}

//切换目录————cd ：进入当前目录下的另一个目录
bool ChangeDir(string DirName)
{
    //目录在目录表中的位置
    int UnitIndex = FindUnitInTable(CurrentDirTable, DirName);
    if (UnitIndex == ERROR){    //不存在
        cout << "File not find !!!" << endl;
        return false;
    }
    if (CurrentDirTable->dirs[UnitIndex].type == '1'){   //不是一个目录
        cout << "Not a dir !!!" << endl;
        return false;
    }
    /********如果是目录**********/
    int DirBlock = CurrentDirTable->dirs[UnitIndex].StartBlock;
    CurrentDirTable = (DirTable*)GetBlockAddr(DirBlock);        //当前目录指针指向要切换的目录
    //修改绝对路径
    if (DirName == "..")    //如果是切换到父级目录
    {
        //回退路径
        int len = path.length();
        for (int i = len - 2; i >= 0; i--)
        {
            if (path[i] == '/'){
                path.erase(i);      //删掉 '/' 后面的路径
                break;
            }
        }
    }
    else{   //否则，进入当前目录的下一级目录
        path += "/" + DirName;          //进入 Dirname，不要忘记 '/'
    }
    return true;
}

//修改文件名或目录名———— mv
bool ChangeName(string OldName, string NewName)
{
    int UnitIndex = FindUnitInTable(CurrentDirTable, OldName);
    if (UnitIndex == ERROR){
        cout << "Can not find file!!!" << endl;
        return false;
    }

    CurrentDirTable->dirs[UnitIndex].FileName = NewName;     //在目录表中更改名字
    return true;
}

//创建文件————create
bool CreateFile(string FileName, int FileSize)
{
    if (FileName.length() >= NAME_LENGTH)
    {
        cout << "The file name is too long!!!" << endl;
        return false;
    }
    int FcbBlock = GetBlock(1);     //获得该文件的FCB空间
    if (FcbBlock == ERROR)
        return false;

    int FileBlock = GetBlock(FileSize);     //获取文件数据空间
    if (FileBlock == ERROR)
        return false;

    if (CreateFCB(FcbBlock, FileBlock, FileSize) == false)  //创建FCB
        return false;

    if (AddDirUnit(CurrentDirTable, FileName, '1', FcbBlock) == false)    //添加到目录项
        return false;

    return true;
}

//创建目录————mkdir
bool CreateDir(string DirName)
{
    if (DirName.length() >= 50){
        cout << "The file name is too long!!!" << endl;
        return false;
    }

    int DirBlock = GetBlock(1);     //为目录表分配空间
    if (DirBlock == ERROR)
        return false;

    if (AddDirUnit(CurrentDirTable, DirName, '0', DirBlock) == false)   //将目录项添加到当前目录
        return false;

    //为新建的目录添加一个父目录项
    DirTable* NewTable = (DirTable*)GetBlockAddr(DirBlock);
    NewTable->DirCount = 0;
    string parent = "..";
    if (AddDirUnit(NewTable, parent, '0', GetAddrBlock((char*)CurrentDirTable)) == false)
        return false;

    return true;
}

//创建FCB
bool CreateFCB(int FcbBlockNum, int FileBlockNum, int FileSize)
{
    //找到FCB的存储位置
    FCB* CurrentFCB = (FCB*)GetBlockAddr(FcbBlockNum);
    CurrentFCB->BlockNum = FileBlockNum;     //文件所在盘块位置
    CurrentFCB->FileSize = FileSize;         //文件的大小
    CurrentFCB->link = 1;                    //文件的链接个数
    CurrentFCB->DataSize = 0;                //已写入文件的数据量
    CurrentFCB->ReadPtr = 0;                 //文件的度指针

    return true;
}

//添加目录项
bool AddDirUnit(DirTable* MyDirTable, string FileName, char type, int FcbBlockNum)
{
    int DirNumber = MyDirTable->DirCount;
    if (DirNumber == DIRS_LENGTH){  //检查目录项数量是否超标
        cout << "The dir is full, try to delete some files !!!" << endl;
        return false;
    }

    //检查文件名是否已经存在
    if (FindUnitInTable(MyDirTable, FileName) != ERROR){
        cout << "The file already exits" << endl;
        return false;
    }

    //由于从0开始计算，所以数目就是当前申请空间的起始位置
    DirUnit* NewDir = &MyDirTable->dirs[DirNumber];
    MyDirTable->DirCount++;

    //设置新目录项内容
    NewDir->FileName = FileName;
    NewDir->type = type;
    NewDir->StartBlock = FcbBlockNum;

    return true;
}

//删除文件————rm
bool DeleteFile(string FileName)
{
    //忽略系统自动创建的父目录
    if (FileName == ".."){
        cout << "Can not delete !!!" << endl;
        return false;
    }

    //查找文件的目录项位置
    int UnitIndex = FindUnitInTable(CurrentDirTable, FileName);
    if (UnitIndex == ERROR){
        cout << "File not found !!!" << endl;
        return false;
    }
    DirUnit TempUnit = CurrentDirTable->dirs[UnitIndex];
    //判断类型
    if (TempUnit.type == '0'){
        cout << "This is not a file !!!" << endl;
        return false;
    }

    int FcbBlock = TempUnit.StartBlock;     //找到文件的盘块

    //释放内存
    ReleaseFile(FcbBlock);
    //从目录表中删除
    DeleteDirUnit(CurrentDirTable, UnitIndex);

    return true;
}

//释放文件内存
bool ReleaseFile(int FcbBlock)
{
    FCB* TempFCB = (FCB*)GetBlockAddr(FcbBlock);
    if (--TempFCB->link == 0)        //连接数减一后若没有链接
        ReleaseBlock(TempFCB->BlockNum, TempFCB->FileSize);     //释放盘块空间

    //释放FCB空间
    ReleaseBlock(FcbBlock, 1);
    return true;
}

//删除目录项
bool DeleteDirUnit(DirTable* MyDirTable, int UnitIndex)
{
    int DirUnitNumber = MyDirTable->DirCount;
    for (int i = UnitIndex; i < DirUnitNumber - 1; i++)     //覆盖删除
        MyDirTable->dirs[i] = MyDirTable->dirs[i + 1];

    MyDirTable->DirCount--;

    return true;
}

//删除目录————rmdir
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

    //从目录表中删除
    DeleteDirUnit(CurrentDirTable, DirIndex);

    return true;
}

//删除文件 / 目录项
bool DeleteFileOrTable(DirTable* MyDirTable, int UnitIndex)
{
    DirUnit TempUnit = MyDirTable->dirs[UnitIndex];

    if (TempUnit.type == '0')       //目录
    {
        int FcbBlock = TempUnit.StartBlock;
        DirTable* table = (DirTable*)GetBlockAddr(FcbBlock);

        cout << "Delete dir " <<TempUnit.FileName<<endl;
        int UnitCount = table->DirCount;
        for (int i = 1; i < UnitCount; i++){
            cout << "Now delete the " << i << " %%%%%% " <<table->dirs[i].FileName<<endl;
            DeleteFileOrTable(table, i);
        }

        ReleaseBlock(FcbBlock, 1);      //释放盘块
    }
    else{       //文件就可以直接删除
        int FcbBlock = TempUnit.StartBlock;
        ReleaseFile(FcbBlock);
    }

    return true;
}

//从目录中查找目录项目
int FindUnitInTable(DirTable* MyDirTable, string UnitName)
{
    int DirNumber = MyDirTable->DirCount;
    int UnitIndex = ERROR;
    for (int i = 0; i < DirNumber; i++)     //遍历目录表，找到目录所在的位置
    {
        if (UnitName == MyDirTable->dirs[i].FileName)
            UnitIndex = i;
    }
    return UnitIndex;
}








