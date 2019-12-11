#include<iostream>
using namespace std;

int main()
{
    cout << "请输入进行插值的点的数目：";
    int n;
    cin >> n;

    float *x, *y, *cs;
    x = new float[n];
    y = new float[n];
    cs = new float[n];

    cout << "请依次输入各点的自变量值和函数值：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    //开始利用牛顿插值法计算差商，即计算多项式的各个系数
    for (int k = 0; k < n; k++)     // n 个点，n - 1阶差商
    {
        //当前要求的是第k阶差商
        cs[k] = 0;
        //k代表当前多项式累加的值
        for (int i = 0; i < k + 1; i++)
        {
            float temp = y[i];
            for (int j = 0; j < k + 1; j++)
            {
                if (j == i)
                    continue;
                temp *= 1.0 / (x[i] - x[j]);    //根据线性组合的那个公式，而不是正常的差商计算
            }
            cs[k] += temp;
        }
        cout << k << " " << cs[k] << endl;      //输出各阶差商
    }

    cout << "请输入要进行预测的自变量的值：";
    float test;
    cin >> test;
    float result = 0;
    for (int i = 0; i < n; i++)
    {
        float temp = cs[i];
        for (int j = 0; j < i; j++) {
            temp *= (test - x[j]);
        }
        result += temp;
    }
    cout << "用插值法求出的结果为：" << result << endl;
    return 0;
}
