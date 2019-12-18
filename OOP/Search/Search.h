#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
int binary_search(T *a, int low, int high, T elem)
{
    while (high - low >= 1)
    {
        int i = (high + low) / 2;
        if (a[i] == elem)
            return i;
        else if (a[i] < elem){
            low = i + 1;
        }
        else{
            high = i - 1;
        }
    }
    return -1;
}

template<class T>
int Search(T *array, int length, T key)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (array[i] == key)
        {
            return i;
            break;
        }
    }
    return -1;
}
#endif // SEARCH_H_INCLUDED
