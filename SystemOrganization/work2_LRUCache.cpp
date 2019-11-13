/** ʵ��LRU���㷨˼�룺
*�洢���ͣ�˫������ʹ����STL��list
*�㷨˼�룺
    Ĭ��cache��ʼ��Ϊ�գ�key����Ҫ����һ��Ԫ��
    1�����cache Ϊ�գ���ֱ�Ӱ�key����cache
    2�����cache ��Ϊ�գ�
        1���� cache �в����Ƿ��� key
            ���У�ɾ����λ�õ�key��Ȼ���key��ӵ���ͷ
            ��û�С��������жϣ�
                ������δ����ֱ�Ӽ��룻
                ������������ɾ������βԪ�أ�Ȼ���key��ӵ���ͷ
*/
#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

#define MAX_SIZE 5      //cache���洢��
#define MAX_NUMBER 200

class LRU{
private:
    list<int> cache;
    int hit_count = 0;      // ͳ�����д���
    int number;             // ģ�����ݸ���
public:
    LRU(int n){
        number = n;
    }
    void LRUCache(int key);     // cache ���ʺ���
    void output();              // cache �����������
    void hit_rate();            // ����������
};

void LRU::LRUCache(int key)
{
    if (cache.empty())  // ���cacheΪ��
    {
        cache.push_front(key);      //��key��ӵ�cache��
    }
    else    //��cache��Ϊ��
    {
        list<int>::iterator it;
        it = find(cache.begin(), cache.end(), key);  // ����key

        if (it != cache.end()){         //����
            hit_count++;
            cout<<"Hit Great~~��������"<<endl;
            cache.erase(it);            //ɾ����λ�õ�keyԪ��
            cache.push_front(key);      //��key ��ӵ���ͷ
        }
        else //������
        {
            if (cache.size() < MAX_SIZE){// ��������δ��,
                cache.push_front(key);   // �Ѹ�Ԫ�ش���cacheǰ��
            }
            else{                        // ������������
                cache.pop_back();        // ɾ��cacheβ��Ԫ��
                cache.push_front(key);   // �Ѹ�Ԫ�طŵ�cacheͷ��
            }

        }
    }
}

void LRU::output()
{
    list<int>::iterator it;
    for (it = cache.begin(); it != cache.end(); it++)
        cout<<*it<<" ";
    cout<<endl;
}

void LRU::hit_rate()
{
    float _rate;
    _rate = (hit_count * 1.0) / number * 100;
    cout<<"������Ϊ��"<<_rate<<"%"<<endl;
}

int main()
{
    int a[MAX_NUMBER], n;  //������ΪҪ��������
    cout<<"��Ҫģ��������ݵĸ�����   ";
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>a[i];
    LRU _cache(n);
    for (int i = 0; i < n; i++)
    {
        int key = a[i];
        cout<<"��ʱ��Ҫ���ʵ����ݣ�   "<<key<<endl;
        _cache.LRUCache(key);
        cout<<"���ݷ��ʺ� cache �е����ݸ���Ϊ��   ";
        _cache.output();
        cout<<endl;
    }
    _cache.hit_rate();
    return 0;
}







