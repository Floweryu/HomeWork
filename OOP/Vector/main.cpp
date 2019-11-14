#include<iostream>
#include "Vector.cpp"
using namespace std;

int main()
{
    cout<<"**************** Int Type *******************"<<endl<<endl;
    Vector<int> v1;
    if (v1.empty()){
        cout<<"v1 is empty, whose size is :       "<<v1.size()<<endl;
    }
    int value, n;
    cout<<"Please input the number you what to insert:          ";
    cin>>n;
    for (int i = 0; i < n; i++){
        cin>>value;
        v1.push_back(value);
    }

    if (! v1.empty()){
        cout<<"v1 is not empty, its size is       "<<v1.size()<<endl;
    }

    cout<<"The elems of v1:      "<<endl;
    Vector<int>::iterator it;
    for (it = v1.begin(); it != v1.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    int m;  // location
    cout<<"********** Inserts a value at the specified location: **********"<<endl;
    cout<<"Please input the value and location£º   ";
    cin>>value>>m;
    if (m >= v1.size()){
        cout<<"ERROR!! Position out of range.."<<endl;
    }
    else{
        v1.insert(v1.begin() + m, value);
    }
    cout<<"The size of v1:         "<<v1.size()<<endl;

    cout<<"Elems of v1:   "<<endl;
    for (it = v1.begin(); it != v1.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"********** Delete a value  **********"<<endl;
    v1.pop_back();
    cout<<"After deleting the last element, the elems are£º        ";
        for (it = v1.begin(); it != v1.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    cout<<"Please input which location you want to delete:       ";
    cin>>m;
    v1.erase(v1.begin() + m -1);
    cout<<"The element after deleting the m-th position are£º        ";
    for (it = v1.begin(); it != v1.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    cout<<"Clear v1:   "<<endl;
    v1.clear();
    cout<<"The size of v1:        "<<v1.size()<<endl<<endl<<endl;

    // ×Ö·ûÀàÐÍ
    cout<<"**************** Character Type *******************"<<endl<<endl;

    Vector<char> v2(5, 'v');
    if (v2.empty()){
        cout<<"v2 is empty, whose size is :       "<<v2.size()<<endl;
    }
    else{
        cout<<"v2 is not empty, whose size is :       "<<v2.size()<<endl;
    }
    char ch;
    cout<<"Please input the number you what to insert:          ";
    cin>>n;
    for (int i = 0; i < n; i++){
        cin>>ch;
        v2.push_back(ch);
    }

    if (! v2.empty()){
        cout<<"v2 is not empty, its size is       "<<v2.size()<<endl;
    }

    cout<<"The elems of v2:      "<<endl;
    Vector<char>::iterator its;
    for (its = v2.begin(); its != v2.end(); ++its){
        cout<<*its<<" ";
    }
    cout<<endl;

    cout<<"********** Inserts a value at the specified location: **********"<<endl;
    cout<<"Please input the value and location£º   ";
    cin>>ch;
    cin>>m;
    if (m >= v2.size()){
        cout<<"ERROR!! Position out of range.."<<endl;
    }
    else{
        v2.insert(v2.begin() + m, ch);
    }
    cout<<"The size of v2:         "<<v2.size()<<endl;

    cout<<"Elems of v2:   "<<endl;
    for (its = v2.begin(); its != v2.end(); ++its){
        cout<<*its<<" ";
    }
    cout<<endl;
    cout<<"********** Delete a value  **********"<<endl;
    v2.pop_back();
    cout<<"After deleting the last element, the elems are£º        ";
    for (its = v2.begin(); its != v2.end(); ++its){
        cout<<*its<<" ";
    }
    cout<<endl;

    cout<<"Please input which location you want to delete:       ";
    cin>>m;
    v2.erase(v2.begin() + m - 1);
    cout<<"The element after deleting the m-th position are£º        ";
    for (its = v2.begin(); its != v2.end(); ++its){
        cout<<*its<<" ";
    }
    cout<<endl;

    cout<<"Clear v2:   "<<endl;
    v2.clear();
    cout<<"The size of v2:        "<<v2.size()<<endl;
    return 0;
}
