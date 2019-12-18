#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    cout<<"*********************** int type ***********************"<<endl;
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    if (s.empty())
        cout<<"The stack is empty"<<endl;
    else
        cout<<"The stack is not empty"<<endl;
    cout<<"The size of stack is  :  "<<s.size()<<endl;
    cout<<"The top of stack:      "<<s.top()<<endl;
    s.pop();
    s.pop();
    cout<<"The top of stack:      "<<s.top()<<endl;

    cout<<endl<<"*********************** char type **********************"<<endl;
    Stack<char> str;
    str.push('a');
    str.push('b');
    str.push('c');
    str.push('d');
    str.push('e');
    if (str.empty())
        cout<<"The stack is empty"<<endl;
    else
        cout<<"The stack is not empty"<<endl;
    cout<<"The size of stack is  :  "<<str.size()<<endl;
    cout<<"The top of stack:      "<<str.top()<<endl;
    str.pop();
    str.pop();
    cout<<"The top of stack:      "<<str.top()<<endl;
    return 0;
}
