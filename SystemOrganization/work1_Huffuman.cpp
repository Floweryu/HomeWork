/**
* Author : ZhangJunFeng
* Date : 2018-11-28-18.32.05
* Function: �շ���������
* Description :
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

#define MAX 10000

typedef struct
{
	unsigned int weight;		//����Ȩֵ
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char * *HuffmanCode;

//ѡ��parentΪ 0 ��weight��С�������ڵ�
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int minni = MAX, i;       //MAX�ĳ�ʼֵ����Ϊ��Ȩֵ�����

    for (i = 1; i <= n; i++)
    {
        if (HT[i].weight < minni && HT[i].parent == 0)     //��ȨֵС��ʱ �� ���ڵ�Ϊ 0 ʱ
        {
            minni = HT[i].weight;
            s1 = i;
        }
    }
//    cout<<s1<<endl;
    minni = MAX;
    for (i = 1; i <= n; i++)
    {
        if (HT[i].weight < minni && HT[i].parent == 0 && i != s1)
        {
            minni = HT[i].weight;
            s2 = i;
        }
    }
//    cout<<s2<<endl;
    int temp;       //��С�ķŵ����
    if (HT[s1].weight >= HT[s2].weight)
    {
        temp = s1;
        s1 = s2;
        s2 = temp;
    }
//    cout<<n<<"!!!"<<s1<<"@@@"<<s2<<endl;
//    cout<<HT[s1].weight<<"~~~"<<HT[s2].weight<<endl;
}


//����շ�����
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int start;
	unsigned f;

	int m, i;
	unsigned c;
	HuffmanTree p;
	char *cd;

	if (n <= 1)
		return;

	m = 2 * n - 1;
	HT = (HuffmanTree) malloc ((m + 1) * sizeof(HTNode));

	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)			    //��һ�ŵ�Ԫ��ʼ�� n �ŵ�Ԫ����Ҷ�ӽ�㸳ֵ
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)	             // i �� n + 1�� m
		(*p).parent = 0;		    //�������˫�����ֵΪ 0

	for (i = n + 1; i <= m; i++)	//���շ�����
	{
	    int s1, s2;
		Select(HT, i - 1, s1, s2);	                    //s1��s2 Ϊ��ѡ��ڵ��λ��
		HT[s1].parent = HT[s2].parent = i;	            // i �ŵ�Ԫ�� s1 s2 ��˫��
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;	// i �ŵ�Ԫ��Ȩֵ�� s1 �� s2 ��Ȩֵ֮��
	}

	HC = (HuffmanCode) malloc ((n + 1) * sizeof(char*));

	cd = (char*) malloc (n * sizeof(char));              //���� n ���ַ������ͷָ������
	cd[n - 1] = '\0';	                                 //�����������

	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//��Ҷ�ӵ������������
		{
			if (HT[f].rchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*) malloc ((n - start) * sizeof (char));
		strcpy(HC[i], &cd[start]);		//�� cd ��ֵ���뵽 HC
	}
	free(cd);			//�ͷſռ�
}

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int *w, n, i, j;
	printf("������Ȩֵ�ĸ���(>1) ��    ");
	scanf("%d", &n);

	w = (int*) malloc (n * sizeof(int));		//���ɴ�� n ��Ȩֵ�Ŀռ�
	printf("���������� %d ��Ȩֵ�����Σ�:\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", w + i);

	HuffmanCoding(HT, HC, w, n);				//����w����� n ��Ȩֵ����շ�������n ���շ����������HC

	float aver = 0;
	float H = 0;
	for (i = 1; i <= n; i++)
    {
        cout<<*(w + i - 1)<<" �Ĺ����������ǣ�";
        puts(HC[i]);
        int len = strlen(HC[i]);
        cout<<"�����볤��Ϊ��"<<len<<endl;
//        bitset<10> bit(HC[i]);  //��Ϊ������
//        cout<<*(w + i - 1)<<" �Ĺ����������Ӧ�����ƣ�"<<bit<<endl;
//
//        int a = bit.to_ulong();    //��Ϊʮ����
//        cout<<*(w + i - 1)<<" �Ĺ����������Ӧʮ���ƣ�"<<a<<endl;

        float data = (*(w + i - 1) * 1.0) / 100;    //Ƶ�ʻ�ΪС��
        cout<<"ָ��ʹ�õ�Ƶ��Ϊ��"<<data<<endl<<endl;
        aver += data * len;

        H -= data * log2(data);
    }
    cout<<"�����������ƽ���볤��"<<aver<<endl;
    cout<<"��Ϣ��Ϊ��"<<H<<endl;
    float ry;
    ry = (aver - H) / aver;
    cout<<"��Ϣ������Ϊ��"<<ry<<endl;
    return 0;
}


