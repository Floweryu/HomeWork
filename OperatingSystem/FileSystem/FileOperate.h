#ifndef FILEOPERATE_H_INCLUDED
#define FILEOPERATE_H_INCLUDED

#include<string>
using namespace std;

#define NAME_LENGTH 50          //文件名长度
#define DIRS_LENGTH 30          //目录表长度


/*目录项结构
* 目录项包含了文件名和文件类型
*/
typedef struct{
    string FileName;                    //目录名
    char type;                          //文件类型：'0'-dir，'1'-file
    int StartBlock;                     //FCB起始盘块
}DirUnit;


/*目录表结构
* 目录表记录了目录的数目，以及用来存储目录的列表
*一个目录表只占用一个盘块，一个目录项大小为64B，所以一个目录表中最多可含15个目录项，
*DirCount 记录每个目录表中已含有的目录项数目。
*系统在初始化时，会自动生成一个空的根目录表存放于磁盘中，作为用户的初始位置，
*用户所有的目录和文件都这个表为根进行树状目录结构的展开。
*当创建一个目录表时，系统会自动为目录表加上一项名为”..”的目录项，指示父目录表的位置
*/
typedef struct{
    int DirCount;                   //目录数目
    DirUnit dirs[DIRS_LENGTH];      //目录表
}DirTable;


/*FCB结构
*文件控制块包含了文件数据的起始位置和大小。
*dataSize,readptr是为文件的读写操作而准备的，记录文件已写入的内容长度（不可超过文件大小），和当前读取的位置。
*Link记录了文件的链接数，用于文件的共享，当文件的链接数为0时，系统可以回收文件的空间。
*一个FCB大小为20B，但也用一个盘块保存。
*由于采用的是连续分配方式，所以系统规定文件被创建时，必须给出文件的大小，而且后期也不能修改文件的大小。
*/
typedef struct {
    int DataSize;          //已写入的内容的大小，字节为单位
    int FileSize;          //文件的大小, 盘块为单位
    int BlockNum;          //文件数据起始盘块
    int ReadPtr;           //读指针
    int link;              //文件链接数
}FCB;

//初始化根目录
void InitRootDir();

//获得绝对路径
string GetPath();

//展示当前目录————dir
void ShowDir();

//切换目录————cd
bool ChangeDir(string DirName);

//修改文件名和目录名————mv
bool ChangeName(string OldName, string NewName);

//创建文件————create
bool CreateFile(string FileName, int FileSize);

//创建目录————mkdir
bool CreateDir(string DirName);

//删除文件————rm
bool DeleteFile(string FileName);

//释放文件内存
bool ReleaseFile(int FcbBlock);

//删除目录项
bool DeleteDirUnit(DirTable* MyDirTable, int UnitIndex);

//删除目录————rmdir
bool DeleteDir(string DirName);

//删除文件/目录项
bool DeleteFileOrTable(DirTable* MyDirTable, int UnitIndex);

//创建FCB
bool CreateFCB(int FcbBlockNum, int FileBlockNum, int FileSize);

//添加目录项
bool AddDirUnit(DirTable* MyDirTable, string FileName, char type, int FcbBlockNum);

//从目录表中查找目录
int FindUnitInTable(DirTable* MyDirTable, string UnitName);

#endif // FILEOPERATE_H_INCLUDED
