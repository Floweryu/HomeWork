#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_SIZE 7

int n;
double y[MAX_SIZE + 1];
long lamda[MAX_SIZE][MAX_SIZE / 2 + 2] = {
        {2, 1},
        {6, 1, 4},
        {8, 1, 3},
        {90, 7, 32, 12},
        {288, 19, 75, 50},
        {840, 41, 216, 27, 272},
        {17280, 751, 3577, 1323, 2989}
    };

void input(double y[], double a, double b, int n)
{
    double h = (b - a) / (n - 1);
    cout << "Please enter the ordinate of the integral node:  "<<endl;
    for (int i = 0; i < n; i++){
        cout<<"The x is : "<<setiosflags(ios::fixed)<<setprecision(6)<<a + i * h<<endl;
        cout<<"Please input y :    ";
        cin>>y[i];
    }
    cout<<endl;
}

double NewtonCotes(double y[], double a, double b, int n)
{
    double integral = 0.0;
    for (int i = 0; i < n / 2; i++){
        integral += (y[i] + y[n - i - 1]) * lamda[n - 2][i + 1] / lamda[n - 2][0];
    }
    if (n % 2){
        integral += y[n / 2] * lamda[n - 2][n / 2 + 1] / lamda[n - 2][0];
    }
    integral *= b - a;
    return integral;
}

int main()
{
    double a, b;
    cout << "Please enter the boundary of a and b :    ";
    cin >> a >> b;
    cout << "Please enter the number of points :  ";
    cin >> n;

    input(y, a, b, n);

    double result = NewtonCotes(y, a, b, n);

    cout << "Finally, The Integral value is :   "<<setiosflags(ios::fixed)<<setprecision(6)<< result << endl;
    return 0;
}

