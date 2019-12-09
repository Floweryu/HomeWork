#include <iostream>

using namespace std;

#define PROGRESS 5      //进程数
#define VARIETY 3       //资源种类数

int total[VARIETY];     //系统资源总数
int result[PROGRESS];   //进程执行顺序结果

//输入total，maxneed，allocation，然后计算出need，available，都输出
void input(int maxneed[PROGRESS][VARIETY], int allocation[PROGRESS][VARIETY], int need[PROGRESS][VARIETY], int available[VARIETY])
{
    cout<<"Please input the total number of variety:"<<endl;
    for (int i = 0; i < VARIETY; i++){
        cin>>total[i];
    }
    cout<<"Please input max data:"<<endl;
    for (int i = 0; i < PROGRESS; i++){
        for (int j = 0; j < VARIETY; j++){
            cin>>maxneed[i][j];
        }
    }
    cout<<"Please input allocation data:"<<endl;
    for (int i = 0; i < PROGRESS; i++){
        for (int j = 0; j < VARIETY; j++){
            cin>>allocation[i][j];
        }
    }
    cout<<"The need data :"<<endl;
    for (int i = 0; i < PROGRESS; i++){
        for (int j = 0; j < VARIETY; j++){
            need[i][j] = maxneed[i][j] - allocation[i][j];
            cout<<need[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"The available data :"<<endl;
    for (int j = 0; j < VARIETY; j++){      // 按列求和计算没个资源种类的availabel
        int sum = 0;
        for (int i = 0; i < PROGRESS; i++){
            sum += allocation[i][j];
        }
        available[j] = total[j] - sum;
        cout<<available[j]<<" ";
    }
    cout<<endl<<endl;
}

//a 中元素 全都 大于 b 中元素，返回 true; 否则，返回 false
bool compare(int a[], int b[])
{
    bool flag = true;
    for (int i = 0; i < VARIETY; i++)
    {
        if (a[i] < b[i]){   //一旦出现a[i] < b[i]，就返回false
            flag = false;
            break;
        }
    }
    return flag;
}

//初始状态检查
bool InitialState(int need[PROGRESS][VARIETY], int allocation[PROGRESS][VARIETY], int available[VARIETY])
{
    int work[VARIETY];                    //available 的等价数组，防止把available值覆盖
    for (int i = 0; i < VARIETY; i++){
        work[i] = available[i];
    }

    bool flag[PROGRESS] = {0};            //设置标志位，标记该进程是否已完成，为0表示没有，1为已完成
    int ans = 0;                             //result结果数组的计数器
    for (int k = 0; k < PROGRESS; k++)      //遍历次数
    {
        for (int i = 0; i < PROGRESS; i++)
        {
            int subneed[VARIETY];           //每一个进程的need值，方便比较
            if (flag[i]) continue;          //已被找过就跳过

            for (int j = 0; j < VARIETY; j++){
                subneed[j] = need[i][j];    //提取该行的need，便于下面的比较
            }

            if (compare(work, subneed)) //资源数满足
            {
                flag[i] = true;     //进程被选择
                result[ans++] = i;  //序列结果存到result数组中

                cout<<"Now the available is :"<<endl;
                for (int j = 0; j < VARIETY; j++){
                    work[j] += allocation[i][j];   //更新现在可利用资源数量
                    cout<<work[j]<<" ";
                }
                cout<<endl;
            }
            if (flag[i])    break;      //找到满足的，跳出循环
        }
    }

    bool flagflag = true;
    for (int i = 0; i < PROGRESS; i++)
    {
        if (! flag[i]) flagflag = false;
    }
    return flagflag;
}

//请求资源安全状态检查
void RequestState(int (&need)[PROGRESS][VARIETY], int (&allocation)[PROGRESS][VARIETY], int (&available)[VARIETY], int (&request)[VARIETY], int ans)
{
    int subneed[VARIETY];                //所请求资源数组
    for (int i = 0; i < VARIETY; i++){
        subneed[i] = need[ans][i];
    }

    /* 若请求向量满足同时小于subneed和available，则可以进行检测*/
    if (compare(subneed, request) && compare(available, request))
    {
        for (int j = 0; j < VARIETY; j++){          //更改allocation, need, available的值
            allocation[ans][j] += request[j];
            need[ans][j] -= request[j];
            available[j] -= request[j];
        }

        if (InitialState(need, allocation, available))      //更改完值后进行初始状态检测
        {
            cout<<endl<<"Allow the "<<ans<<"-th process to apply for resources !!"<<endl<<endl;
            cout<<"The safety sequence is: "<<endl;
            for (int i = 0; i < PROGRESS; i++){
                cout<<"P"<<result[i]<<" ";
            }
            cout<<endl;
        }
        else{
            cout<<endl<<"Can-NOT allow the "<<ans<<"-th process to apply for resources !!"<<endl<<endl;
        }
    }
    else{
        cout<<"Can-NOT apply resources!!!"<<endl;
    }
}

int main()
{
    int maxneed[PROGRESS][VARIETY];     //最大需求矩阵————需要赋初值
    int allocation[PROGRESS][VARIETY];  //已分配资源矩阵————需要赋初值
    int need[PROGRESS][VARIETY];        //还需要的资源矩阵
    int available[VARIETY];             //现在可利用的资源
    int request[VARIETY];               //申请资源数组
    int ans;                            //申请目标进程

    input(maxneed, allocation, need, available);

    if (InitialState(need, allocation, available))
    {
        cout<<endl<<"The initial state is Safety!!"<<endl<<endl;
        cout<<"The safety sequence is: "<<endl;
        for (int i = 0; i < PROGRESS; i++){
            cout<<"P"<<result[i]<<" ";
        }
        cout<<endl<<endl;
    }
    else{
        cout<<endl<<"The initial state is UN-Safety!!"<<endl<<endl;
    }

    cout<<"Please input a request queue:"<<endl;
    for (int i = 0; i < VARIETY; i++){
        cin>>request[i];
    }
    cout<<"Please input which progress you what to apply and is between  0 -- "<<PROGRESS - 1<<"  :  "<<endl;
    cin>>ans;
    RequestState(need, allocation, available, request, ans);
    return 0;
}
