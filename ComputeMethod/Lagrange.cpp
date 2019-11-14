#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_SIZE 100

double x[MAX_SIZE];
double y[MAX_SIZE];
double test_x[MAX_SIZE];
int n, m;

void input(double x[], double y[], int n)
{
    cout << "The x of the all node:  ";
    for (int i = 0; i < n; i++){
        cin >> x[i];
    }
    cout << "The y of the all node:  ";
    for (int i = 0; i < n; i++){
        cin >> y[i];
    }
}

double Lagrange(double x[], double y[], double test)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        double temp = 1;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                temp *= ((test - x[j]) / (x[i] - x[j]));
        }
        sum += temp * y[i];
    }
    return sum;
}

int main()
{
    cout << "Please input the number of node : ";
    cin >> n;
    input(x, y, n);

    cout << "Please input the number of test data x : ";
    cin >> m;

    cout << "Please input the all test x:  ";
    for (int i = 0; i < m; i++)
    {
        cin >> test_x[i];
    }

    for (int i = 0; i < m; i++)
    {
        double result = Lagrange(x, y, test_x[i]);
        cout << "The rangelangian difference of this node is :   ";
        cout << setiosflags(ios::fixed) << setprecision(20) << result << endl;
    }

    return 0;
}
