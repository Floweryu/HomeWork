#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include<iostream>
#include<algorithm>
using namespace std;

#define MAXNUM 1000

//直接插入排序————从小到大
template<class T>
void Direct_InsertSort(T *array, const int length)
{
    int i, j;
    for (i = 2; i <= length; i++)                      //从第二个位置开始寻找
    {
        if (array[i] < array[i-1])
        {
            array[0] = array[i];                       //将该值存储
            array[i] = array[i-1];                     //把前一个值向后移动一位
            for (j = i - 2; array[j] > array[0]; --j)  //从待插入值的前两个值起，把比 L.list[i] 大的值向后移动一位
            {
                array[j+1] = array[j];
            }  //跳出循环时 j 已经指到小于或等于L.list[0]的位置
            array[j+1] = array[0];
        }
    }
}

//折半插入排序
template<class T>
void Binary_InsertSort(T *array, const int length)
{
    int low, high, half;
    int i, j;
    for (i = 2; i <= length; i++)
    {
        array[0] = array[i];
        low = 1; high = i-1;
        while(high >= low)
        {
            half = (high + low) / 2;
            if (array[0] < array[half])
                high = half - 1;
            else
                low = half + 1;
        }   //跳出循环时 high 已经指到小于或等于L.list[0]的位置
        for (j = i - 1; j > high; j--)
            array[j+1] = array[j];
        array[high+1] = array[0];
    }
}

template<class T>
void Shell_Array(T *array, T dlta[], int len, int &k)
{
    while(len >=2)
    {
        dlta[k] = len / 2;
        k++;
        len /= 2;
    }
}

//希尔插入
template<class T>
void Shell_Insert(T *array, int dk, const int length)
{
    int i, j;

    for (i = dk + 1; i <= length; i++)
    {
        if (array[i] < array[i-dk])
            swap(array[i], array[i-dk]);
    }
}

//希尔排序
template<class T>
void Shell_InsertSort(T *array, T dlta[], const int t)
{
    int k;
    for (k = 0; k < t; k++)
        Shell_Insert(array, dlta[k], t);
}


//直接选择排序
template<class T>
void Select_Sort(T *array, const int length)
{
    int i, j;
    for (i = 1; i <= length-1; i++)
    {
        int min = i;                            //最小值得位置编号
        for (j = i+1; j <= length; j++)
        {
            if (array[j] < array[min])
                min = j;
        }                                       //每次遍历完都找到未排序序列中最小值的下标
        swap(array[i], array[min]);
    }
}

template<class T>
void Bubble_Sort(T *array, int length, const string &str)
{
    int i, j;

    for (i = 1; i <= length - 1; i++)       //排序次数为 L.length-1
    {
        for (j = 1; j <= length - i; j++)   //每排序一次，确定一个元素位置
        {
            if (array[j] > array[j+1] && str == "up")
                swap(array[j], array[j+1]);
            if (array[j] < array[j+1] && str == "down")
                swap(array[j], array[j+1]);
        }
    }
}

//对每次排序，求得枢轴的位置
template<class T>
int partition(T *array, int low, int high, const string &str)
{
    int pivotkey;

    pivotkey = array[low];
    if (str == "up")
    {
        while (low < high)
        {
            while (low < high && array[high] >= pivotkey)     //从后寻找比枢轴小的值，交换位置
                high--;
            swap(array[low], array[high]);

            while (low < high && array[low] <= pivotkey)      //从前寻找比枢轴大的值，交换位置
                low++;
            swap(array[low], array[high]);
        }
    }
    if (str == "down")
    {
        while (low < high)
        {
            while (low < high && array[high] <= pivotkey)     //从后寻找比枢轴大的值，交换位置
                high--;
            swap(array[low], array[high]);

            while (low < high && array[low] >= pivotkey)      //从前寻找比枢轴小的值，交换位置
                low++;
            swap(array[low], array[high]);
        }
    }

    return low;     // 返回枢轴的位置
}

template<class T>
void Quick_Sort(T *array, int low, int high, const string &str)
{
    int pivotloc;

    if (low < high)
    {
        pivotloc = partition(array, low, high, str);
        Quick_Sort(array, low, pivotloc - 1, str);                  //对枢轴前面数据进行排序
        Quick_Sort(array, pivotloc+1, high, str);                   //对枢轴后面数据进行排序
    }
}

//堆调整
template<class T>
void AdjustHeap(T *array, int s, int m, const string &str)        //每次判断该节点的左右子树，将值大的与节点交换位置
{
    int j;
    int rc = array[s];
    for (j = 2*s; j <= m; j *= 2)
    {
        if (str == "up")
        {
            if (j < m && array[j] < array[j+1])   //寻找最大子节点
                j++;
            if (rc >= array[j])
                break;
            array[s] = array[j];
            s = j;
        }
        if (str == "down")
        {
            if (j < m && array[j] > array[j+1])   //寻找最小子节点
                j++;
            if (rc <= array[j])
                break;
            array[s] = array[j];
            s = j;
        }

    }
    array[s] = rc;
}

template<class T>
void Heap_Sort(T *array, int length, const string &str)
{
    int i;
    for (i = length/2; i >= 1; i--)       //调整数组为大顶堆
        AdjustHeap(array, i, length, str);
    for (i = length; i >= 2; i--)         //除去最后一个元素，其他的继续调整为大顶堆
    {
        swap(array[1], array[i]);         //将最大值与最后一个元素交换位置
        AdjustHeap(array, 1, i-1, str);
    }
}

#endif // SORT_H_INCLUDED
