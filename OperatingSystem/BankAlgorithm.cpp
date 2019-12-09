#include <iostream>

using namespace std;

#define PROGRESS 5      //������
#define VARIETY 3       //��Դ������

int total[VARIETY];     //ϵͳ��Դ����
int result[PROGRESS];   //����ִ��˳����

//����total��maxneed��allocation��Ȼ������need��available�������
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
    for (int j = 0; j < VARIETY; j++){      // ������ͼ���û����Դ�����availabel
        int sum = 0;
        for (int i = 0; i < PROGRESS; i++){
            sum += allocation[i][j];
        }
        available[j] = total[j] - sum;
        cout<<available[j]<<" ";
    }
    cout<<endl<<endl;
}

//a ��Ԫ�� ȫ�� ���� b ��Ԫ�أ����� true; ���򣬷��� false
bool compare(int a[], int b[])
{
    bool flag = true;
    for (int i = 0; i < VARIETY; i++)
    {
        if (a[i] < b[i]){   //һ������a[i] < b[i]���ͷ���false
            flag = false;
            break;
        }
    }
    return flag;
}

//��ʼ״̬���
bool InitialState(int need[PROGRESS][VARIETY], int allocation[PROGRESS][VARIETY], int available[VARIETY])
{
    int work[VARIETY];                    //available �ĵȼ����飬��ֹ��availableֵ����
    for (int i = 0; i < VARIETY; i++){
        work[i] = available[i];
    }

    bool flag[PROGRESS] = {0};            //���ñ�־λ����Ǹý����Ƿ�����ɣ�Ϊ0��ʾû�У�1Ϊ�����
    int ans = 0;                             //result�������ļ�����
    for (int k = 0; k < PROGRESS; k++)      //��������
    {
        for (int i = 0; i < PROGRESS; i++)
        {
            int subneed[VARIETY];           //ÿһ�����̵�needֵ������Ƚ�
            if (flag[i]) continue;          //�ѱ��ҹ�������

            for (int j = 0; j < VARIETY; j++){
                subneed[j] = need[i][j];    //��ȡ���е�need����������ıȽ�
            }

            if (compare(work, subneed)) //��Դ������
            {
                flag[i] = true;     //���̱�ѡ��
                result[ans++] = i;  //���н���浽result������

                cout<<"Now the available is :"<<endl;
                for (int j = 0; j < VARIETY; j++){
                    work[j] += allocation[i][j];   //�������ڿ�������Դ����
                    cout<<work[j]<<" ";
                }
                cout<<endl;
            }
            if (flag[i])    break;      //�ҵ�����ģ�����ѭ��
        }
    }

    bool flagflag = true;
    for (int i = 0; i < PROGRESS; i++)
    {
        if (! flag[i]) flagflag = false;
    }
    return flagflag;
}

//������Դ��ȫ״̬���
void RequestState(int (&need)[PROGRESS][VARIETY], int (&allocation)[PROGRESS][VARIETY], int (&available)[VARIETY], int (&request)[VARIETY], int ans)
{
    int subneed[VARIETY];                //��������Դ����
    for (int i = 0; i < VARIETY; i++){
        subneed[i] = need[ans][i];
    }

    /* ��������������ͬʱС��subneed��available������Խ��м��*/
    if (compare(subneed, request) && compare(available, request))
    {
        for (int j = 0; j < VARIETY; j++){          //����allocation, need, available��ֵ
            allocation[ans][j] += request[j];
            need[ans][j] -= request[j];
            available[j] -= request[j];
        }

        if (InitialState(need, allocation, available))      //������ֵ����г�ʼ״̬���
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
    int maxneed[PROGRESS][VARIETY];     //���������󡪡�������Ҫ����ֵ
    int allocation[PROGRESS][VARIETY];  //�ѷ�����Դ���󡪡�������Ҫ����ֵ
    int need[PROGRESS][VARIETY];        //����Ҫ����Դ����
    int available[VARIETY];             //���ڿ����õ���Դ
    int request[VARIETY];               //������Դ����
    int ans;                            //����Ŀ�����

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
