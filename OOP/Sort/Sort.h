#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include<iostream>
#include<algorithm>
using namespace std;

#define MAXNUM 1000

//ֱ�Ӳ������򡪡�������С����
template<class T>
void Direct_InsertSort(T *array, const int length)
{
    int i, j;
    for (i = 2; i <= length; i++)                      //�ӵڶ���λ�ÿ�ʼѰ��
    {
        if (array[i] < array[i-1])
        {
            array[0] = array[i];                       //����ֵ�洢
            array[i] = array[i-1];                     //��ǰһ��ֵ����ƶ�һλ
            for (j = i - 2; array[j] > array[0]; --j)  //�Ӵ�����ֵ��ǰ����ֵ�𣬰ѱ� L.list[i] ���ֵ����ƶ�һλ
            {
                array[j+1] = array[j];
            }  //����ѭ��ʱ j �Ѿ�ָ��С�ڻ����L.list[0]��λ��
            array[j+1] = array[0];
        }
    }
}

//�۰��������
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
        }   //����ѭ��ʱ high �Ѿ�ָ��С�ڻ����L.list[0]��λ��
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

//ϣ������
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

//ϣ������
template<class T>
void Shell_InsertSort(T *array, T dlta[], const int t)
{
    int k;
    for (k = 0; k < t; k++)
        Shell_Insert(array, dlta[k], t);
}


//ֱ��ѡ������
template<class T>
void Select_Sort(T *array, const int length)
{
    int i, j;
    for (i = 1; i <= length-1; i++)
    {
        int min = i;                            //��Сֵ��λ�ñ��
        for (j = i+1; j <= length; j++)
        {
            if (array[j] < array[min])
                min = j;
        }                                       //ÿ�α����궼�ҵ�δ������������Сֵ���±�
        swap(array[i], array[min]);
    }
}

template<class T>
void Bubble_Sort(T *array, int length, const string &str)
{
    int i, j;

    for (i = 1; i <= length - 1; i++)       //�������Ϊ L.length-1
    {
        for (j = 1; j <= length - i; j++)   //ÿ����һ�Σ�ȷ��һ��Ԫ��λ��
        {
            if (array[j] > array[j+1] && str == "up")
                swap(array[j], array[j+1]);
            if (array[j] < array[j+1] && str == "down")
                swap(array[j], array[j+1]);
        }
    }
}

//��ÿ��������������λ��
template<class T>
int partition(T *array, int low, int high, const string &str)
{
    int pivotkey;

    pivotkey = array[low];
    if (str == "up")
    {
        while (low < high)
        {
            while (low < high && array[high] >= pivotkey)     //�Ӻ�Ѱ�ұ�����С��ֵ������λ��
                high--;
            swap(array[low], array[high]);

            while (low < high && array[low] <= pivotkey)      //��ǰѰ�ұ�������ֵ������λ��
                low++;
            swap(array[low], array[high]);
        }
    }
    if (str == "down")
    {
        while (low < high)
        {
            while (low < high && array[high] <= pivotkey)     //�Ӻ�Ѱ�ұ�������ֵ������λ��
                high--;
            swap(array[low], array[high]);

            while (low < high && array[low] >= pivotkey)      //��ǰѰ�ұ�����С��ֵ������λ��
                low++;
            swap(array[low], array[high]);
        }
    }

    return low;     // ���������λ��
}

template<class T>
void Quick_Sort(T *array, int low, int high, const string &str)
{
    int pivotloc;

    if (low < high)
    {
        pivotloc = partition(array, low, high, str);
        Quick_Sort(array, low, pivotloc - 1, str);                  //������ǰ�����ݽ�������
        Quick_Sort(array, pivotloc+1, high, str);                   //������������ݽ�������
    }
}

//�ѵ���
template<class T>
void AdjustHeap(T *array, int s, int m, const string &str)        //ÿ���жϸýڵ��������������ֵ�����ڵ㽻��λ��
{
    int j;
    int rc = array[s];
    for (j = 2*s; j <= m; j *= 2)
    {
        if (str == "up")
        {
            if (j < m && array[j] < array[j+1])   //Ѱ������ӽڵ�
                j++;
            if (rc >= array[j])
                break;
            array[s] = array[j];
            s = j;
        }
        if (str == "down")
        {
            if (j < m && array[j] > array[j+1])   //Ѱ����С�ӽڵ�
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
    for (i = length/2; i >= 1; i--)       //��������Ϊ�󶥶�
        AdjustHeap(array, i, length, str);
    for (i = length; i >= 2; i--)         //��ȥ���һ��Ԫ�أ������ļ�������Ϊ�󶥶�
    {
        swap(array[1], array[i]);         //�����ֵ�����һ��Ԫ�ؽ���λ��
        AdjustHeap(array, 1, i-1, str);
    }
}

#endif // SORT_H_INCLUDED
