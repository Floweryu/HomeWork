/*  用改进的欧拉格式计算下面的微分
*   y' = y - 2 * x / y    0 <= x <= 1   h = 0.1
*   y(0) = 1
*/
#include <iostream>
#include <iomanip>
using namespace std;

const int n = 20;

double derived_f(double x, double y)
{
    return y - 2 * x / y;
}

void ModEuler(double (*derived_f)(double, double), double x0, double y0, double xn, const int n)
{
    double h = (xn - x0) / n;
    double x = x0, y = y0;
    cout << "x[0]=" << x << ",      y[0]=" << y << endl;

    for (int i = 0; i < n; i++)
    {
        double yp = y + h * derived_f(x, y);    //预报值
        x += h;
        double yc = y + h * derived_f(x, yp);   //矫正
        y = (yp + yc) / 2;

        cout << "x[" << i+1 << "]=" << x << ",      " << "y[" << i+1 << "]=" << y << endl;
    }
}

int main()
{
    double x0 = 0, y0 = 1, xn = 1;
    ModEuler(derived_f, x0, y0, xn, n);

    return 0;
}
