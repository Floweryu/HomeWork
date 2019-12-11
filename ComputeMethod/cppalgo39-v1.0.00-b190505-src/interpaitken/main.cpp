#include<iostream>
#include <iomanip>

using namespace std;
#define SIZE 10
int main() {
    int n,i,j,k=2;
    double xx;
    double x[SIZE];
    double y[SIZE];
    double a[SIZE][SIZE];
    for(i=0; i<SIZE; i++)
        for(j=0; j<SIZE; j++)
            a[i][j]=0;
    i=1;
    j=1;
    cout<<"**********埃特金插值***********"<<endl<<endl;
    cout<<"输入已知插值结点数目:   ";
    cin>>n;
    cout<<"依次输入结点的坐标:   x y"<<endl;
    while(i<=n) {
        cout<<"第 "<<i<<"个点的坐标为  ";
        cin>>x[i]>>y[i];
        a[i-1][0]=x[i];
        a[i-1][1]=y[i];
        i++;
    }
    cout<<"输入所求插值结点x坐标:   ";
    cin>>xx;
    for(i=1; i<=n; i++) {
        for(j=i+1; j<=n; j++) {
            y[j]=(xx-x[i])*y[j]/(x[j]-x[i])+(xx-x[j])*y[i]/(x[i]-x[j]);
        }
        for(k=n-i; k>0; k--)
            a[n-k][i+1]=y[n-k+1];
    }
    cout<<"所求y坐标为:  "<<y[n]<<endl;
    cout<<"插值表为："<<endl;
    for(i=0; i<n; i++) {
        for(j=0; j<n+1; j++)
            cout<<setw(10)<<a[i][j];
        cout<<endl;
    }
}

