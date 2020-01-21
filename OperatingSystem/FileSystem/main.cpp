#include <iostream>
#include <string>
#include <vector>
#include "FileOperate.h"
#include "DiskOperate.h"

using namespace std;

//字符串分割函数
vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if(str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

int main()
{
    InitSystem();       //初始化系统
    InitRootDir();      //初始化根目录

    string path = "";                    //路径
    string shell = ">>>";
    while (cout << path << shell)
    {
        string str;                     //输入的字符串
        string command[10];
        bool flag;

        getline(cin, str);
        vector<string> ch = split(str, " ");      //把字符串分割成命令
        vector<string>::iterator it;
        int i = 0;
        for (it = ch.begin(); it != ch.end(); it++)
            command[i++] = *it;

        /*****************文件管理命令*******************/
        if (command[0] == "pwd")
        {
            path = GetPath();
            cout << "当前路径为： " << path << endl;
        }
        else if (command[0] == "dir")
        {
            ShowDir();
        }
        else if (command[0] == "cd")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as :  cd FileName !!!" << endl;
            else{
                flag = ChangeDir(command[1]);
                path = GetPath();
                if (! flag)
                    cout << "进入目录失败！！！" << endl;
            }
        }
        else if (command[0] == "mv")
        {
            if (command[1].empty() || command[2].empty())
                cout << "ERROR!! Command as : mv OldFileName NewFileName !!!"<<endl;
            else{
                flag = ChangeName(command[1], command[2]);
                if (! flag)
                    cout << "修改文件名失败！！！" << endl;
            }
        }
        else if (command[0] == "create")
        {
            if (command[1].empty() || command[2].empty())
                cout << "ERROR!! Command as :  create FileName FileSize  !!!" << endl;
            else{
                flag = CreateFile(command[1], stoi(command[2]));
                if (! flag)
                    cout << "创建文件失败！！！"<<endl;
            }
        }
        else if (command[0] == "mkdir")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as : mkdir DirName  !!!" << endl;
            else{
                flag = CreateDir(command[1]);
                if (! flag)
                    cout << "创建目录失败！！！" << endl;
            }
        }
        else if (command[0] == "rm")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as : rm FileName  !!!" << endl;
            else{
                flag = DeleteFile(command[1]);
                if (! flag)
                    cout << "删除文件失败！！！" << endl;
            }
        }
        else if (command[0] == "rmdir")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as : rmdir DirName  !!!" << endl;
            else{
                flag = DeleteDir(command[1]);
                if (! flag)
                    cout << "删除目录失败！！！" << endl;
            }
        }
        else if (command[0] == "exit")
        {
            ExitSystem();
            exit(0);
        }
        else
        {
            cout << "ERROR!! Command not found !!!" << endl;
        }
        cout << endl << endl;
    }

    return 0;
}



