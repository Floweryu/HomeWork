/*
 *《数值分析简明教程(第二版)》王能超编著
 *
 * Beijing University of Chemical Technology
 * May 19th, 2015 
 * http://www.cnblogs.com/tianyuxuepiao/archive/2012/10/24/2737572.html
 */



#include<iostream>

using namespace std;


float func(float x0) {
    cout<<"输入节点数"<<endl;
    int num,i,j;
    cin>>num;
    float *px = new float[num];
    float *py = new float[num];
    float **martrix = new float*[num];
    for(j = 0;j<num;j++)
        martrix[j] = new float[num+1];
    float result = 0.0,tmp = 1.0;
    for(i = 0;i<num;i++)
    {
        cin>>px[i]>>py[i];
        martrix[i][0] = px[i];
        martrix[i][1] = py[i];
    }
    cout<<"差商表为"<<endl;
    for(i = 1;i<num;i++)
    {
        for(j = 2;j<=i+1;j++)
        {
            martrix[i][j] = (martrix[i][j-1] - martrix[i-1][j-1])/(martrix[i][0] - martrix[i-j+1][0]);
        }
    }
    for(i = 0;i<num;i++)
    {
        for(j = 0;j<=i+1;j++)
            cout<<martrix[i][j]<<" ";
        cout<<endl;
    }
    result += py[0];
    for(i = 1;i<=num-1;i++)
    {
        for(j = 0;j<i;j++)
        {
            tmp = tmp * (x0 - px[j]);
        }
        tmp = tmp * martrix[j][j+1];
        result += tmp;
        tmp = 1.0;
    }
    return result;
}
int main()
{
    float x;
    cin>>x;
    cout<<func(x)<<endl;
    return 0;
}