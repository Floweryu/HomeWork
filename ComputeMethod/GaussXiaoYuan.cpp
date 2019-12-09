/*
*使用高斯消元法解下列方程组
* 10*x1 - x2 - 2*x3 = 7.2
* -x1 + 10*x2 - 2*x3 = 8.3
* -x1 - x2 + 5*x3 = 4.2
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int n;      //矩阵的阶数
    cout << "请输入矩阵的阶数：      ";
    cin >> n;

    double** CoeA = new double* [n];      //系数矩阵
    for (int i = 0; i < n; i++){
        CoeA[i] = new double [n];
    }
    double* ResY = new double [n];      //方程右边数组
    double* result = new double [n];    //结果存储数组


    //输入增广矩阵
    cout << "请输入方程组的增广矩阵：   " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            cin>>CoeA[i][j];
        }
        cin>>ResY[i];
    }


    //求出消元后的增广矩阵（三角矩阵）
    for (int k = 0; k < n - 1; k++)     //遍历基准行
    {
        for (int i = k + 1; i < n; i++) //遍历将要进行消元的行
        {
            double scale = CoeA[i][k] / CoeA[k][k];     //消去每行时的比例因子
            for (int j = k + 1; j < n; j++){
                CoeA[i][j] -= CoeA[k][j] * scale;
            }
            ResY[i] -= ResY[k] * scale;  //方程右边
            CoeA[i][k] = 0;             //消去的补0
        }
    }

    //对三角矩阵进行回代
    for (int i = n - 1; i >= 0; i--)
    {
        double temp = 0.0;
        for (int j = i + 1; j < n; j++){
            temp += CoeA[i][j] * result[j];         //除未知数以外的计算后相加
        }
        result[i] = (ResY[i] - temp) / CoeA[i][i];  //求出未知数
    }

    cout << "高斯消元法的解为：   " << endl;
    for (int i = 0; i < n; i ++)
        cout << setiosflags(ios::fixed) << setprecision(6) << result[i] << " ";
    cout << endl;

    return 0;
}
