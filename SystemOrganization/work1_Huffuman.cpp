/**
* Author : ZhangJunFeng
* Date : 2018-11-28-18.32.05
* Function: 赫夫曼树编码
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
	unsigned int weight;		//结点的权值
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char * *HuffmanCode;

//选择parent为 0 且weight最小的两个节点
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int minni = MAX, i;       //MAX的初始值定义为比权值大的数

    for (i = 1; i <= n; i++)
    {
        if (HT[i].weight < minni && HT[i].parent == 0)     //当权值小于时 且 父节点为 0 时
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
    int temp;       //把小的放到左边
    if (HT[s1].weight >= HT[s2].weight)
    {
        temp = s1;
        s1 = s2;
        s2 = temp;
    }
//    cout<<n<<"!!!"<<s1<<"@@@"<<s2<<endl;
//    cout<<HT[s1].weight<<"~~~"<<HT[s2].weight<<endl;
}


//构造赫夫曼树
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

	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)			    //从一号单元开始到 n 号单元，给叶子结点赋值
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)	             // i 从 n + 1到 m
		(*p).parent = 0;		    //其余结点的双亲域初值为 0

	for (i = n + 1; i <= m; i++)	//建赫夫曼树
	{
	    int s1, s2;
		Select(HT, i - 1, s1, s2);	                    //s1、s2 为被选择节点的位置
		HT[s1].parent = HT[s2].parent = i;	            // i 号单元是 s1 s2 的双亲
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;	// i 号单元的权值是 s1 和 s2 的权值之和
	}

	HC = (HuffmanCode) malloc ((n + 1) * sizeof(char*));

	cd = (char*) malloc (n * sizeof(char));              //分配 n 个字符编码的头指针向量
	cd[n - 1] = '\0';	                                 //编码结束符号

	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//从叶子到根逆向求编码
		{
			if (HT[f].rchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*) malloc ((n - start) * sizeof (char));
		strcpy(HC[i], &cd[start]);		//从 cd 赋值编码到 HC
	}
	free(cd);			//释放空间
}

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int *w, n, i, j;
	printf("请输入权值的个数(>1) ：    ");
	scanf("%d", &n);

	w = (int*) malloc (n * sizeof(int));		//生成存放 n 个权值的空间
	printf("请依次输入 %d 个权值（整形）:\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", w + i);

	HuffmanCoding(HT, HC, w, n);				//根据w所存的 n 个权值构造赫夫曼树，n 个赫夫曼编码存于HC

	float aver = 0;
	float H = 0;
	for (i = 1; i <= n; i++)
    {
        cout<<*(w + i - 1)<<" 的哈夫曼编码是：";
        puts(HC[i]);
        int len = strlen(HC[i]);
        cout<<"操作码长度为："<<len<<endl;
//        bitset<10> bit(HC[i]);  //化为二进制
//        cout<<*(w + i - 1)<<" 的哈夫曼编码对应二进制："<<bit<<endl;
//
//        int a = bit.to_ulong();    //化为十进制
//        cout<<*(w + i - 1)<<" 的哈夫曼编码对应十进制："<<a<<endl;

        float data = (*(w + i - 1) * 1.0) / 100;    //频率化为小数
        cout<<"指令使用的频度为："<<data<<endl<<endl;
        aver += data * len;

        H -= data * log2(data);
    }
    cout<<"哈夫曼编码的平均码长："<<aver<<endl;
    cout<<"信息熵为："<<H<<endl;
    float ry;
    ry = (aver - H) / aver;
    cout<<"信息冗余量为："<<ry<<endl;
    return 0;
}


