/*
*使用Doolittle矩阵分解法解下列方程组
* 10*x1 - x2 - 2*x3 = 7.2
* -x1 + 10*x2 - 2*x3 = 8.3
* -x1 - x2 + 5*x3 = 4.2
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define MAXSIZE 50

int main()
{
    double CoeA[MAXSIZE][MAXSIZE], ResY[MAXSIZE], x[MAXSIZE], y[MAXSIZE];
    double L[MAXSIZE][MAXSIZE], U[MAXSIZE][MAXSIZE];
    int n;
    cout << "请输入原方程的阶数：    ";
    cin >> n;

    cout << "请输入方程组的增广矩阵：" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> CoeA[i][j];
        cin >> ResY[i];
    }

    //定义L矩阵的对角线元素为1
    for (int i = 0; i < n; i++)
        L[i][i] = 1;

    //进行 Doolittle 分解
    for (int k = 0; k < n; k++)
    {
        //分解得到 U 矩阵，逐列进行处理
        for (int j = k; j < n; j++) {
            U[k][j] = CoeA[k][j];
            for (int i = 0; i < k; i++)
                U[k][j] -= L[k][j] * U[i][j];
        }
        //分解得到 L 矩阵，逐行进行助理
        for (int i = k + 1; i < n; i++) {
            L[i][k] = CoeA[i][k];
            for (int j = 0; j < k; j++)
                L[i][k] -= L[i][j] * U[j][k];
            L[i][k] /= U[k][k];
        }
    }

    //进行方程组的回代过程
    for(int i = 0; i < n; i++)     //对 L 进行回代，求解 Ly = ResY 的到 y
    {
        y[i] = ResY[i];
        for(int j = 0; j <= i - 1; j++)
            y[i] -= L[i][j] * y[j];
    }

    for(int i = n-1; i >= 0; i--)       //对 U 进行回代, 求解 y = Ux, 得到 x
    {
        x[i] = y[i];
        for(int j = i + 1; j < n; j++)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }

    cout << "解得方程组的根为：";
    for(int i=0; i<n; i++)
        cout << x[i] << " ";
    cout << endl;
    return 0;
}
