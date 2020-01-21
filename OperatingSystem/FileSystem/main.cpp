#include <iostream>
#include <string>
#include <vector>
#include "FileOperate.h"
#include "DiskOperate.h"

using namespace std;

//�ַ����ָ��
vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if(str == "")
        return res;
    //���ַ���ĩβҲ����ָ����������ȡ���һ��
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

int main()
{
    InitSystem();       //��ʼ��ϵͳ
    InitRootDir();      //��ʼ����Ŀ¼

    string path = "";                    //·��
    string shell = ">>>";
    while (cout << path << shell)
    {
        string str;                     //������ַ���
        string command[10];
        bool flag;

        getline(cin, str);
        vector<string> ch = split(str, " ");      //���ַ����ָ������
        vector<string>::iterator it;
        int i = 0;
        for (it = ch.begin(); it != ch.end(); it++)
            command[i++] = *it;

        /*****************�ļ���������*******************/
        if (command[0] == "pwd")
        {
            path = GetPath();
            cout << "��ǰ·��Ϊ�� " << path << endl;
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
                    cout << "����Ŀ¼ʧ�ܣ�����" << endl;
            }
        }
        else if (command[0] == "mv")
        {
            if (command[1].empty() || command[2].empty())
                cout << "ERROR!! Command as : mv OldFileName NewFileName !!!"<<endl;
            else{
                flag = ChangeName(command[1], command[2]);
                if (! flag)
                    cout << "�޸��ļ���ʧ�ܣ�����" << endl;
            }
        }
        else if (command[0] == "create")
        {
            if (command[1].empty() || command[2].empty())
                cout << "ERROR!! Command as :  create FileName FileSize  !!!" << endl;
            else{
                flag = CreateFile(command[1], stoi(command[2]));
                if (! flag)
                    cout << "�����ļ�ʧ�ܣ�����"<<endl;
            }
        }
        else if (command[0] == "mkdir")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as : mkdir DirName  !!!" << endl;
            else{
                flag = CreateDir(command[1]);
                if (! flag)
                    cout << "����Ŀ¼ʧ�ܣ�����" << endl;
            }
        }
        else if (command[0] == "rm")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as : rm FileName  !!!" << endl;
            else{
                flag = DeleteFile(command[1]);
                if (! flag)
                    cout << "ɾ���ļ�ʧ�ܣ�����" << endl;
            }
        }
        else if (command[0] == "rmdir")
        {
            if (command[1].empty())
                cout << "ERROR!! Command as : rmdir DirName  !!!" << endl;
            else{
                flag = DeleteDir(command[1]);
                if (! flag)
                    cout << "ɾ��Ŀ¼ʧ�ܣ�����" << endl;
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



