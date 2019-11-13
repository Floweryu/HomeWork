/** 实现LRU的算法思想：
*存储类型：双向链表，使用了STL的list
*算法思想：
    默认cache初始化为空，key是需要访问一个元素
    1，如果cache 为空，就直接把key存入cache
    2，如果cache 不为空：
        1，在 cache 中查找是否有 key
            若有：删除该位置的key，然后把key添加到表头
            若没有————判断：
                若链表未满：直接加入；
                若链表已满：删除最后表尾元素，然后把key添加到表头
*/
#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

#define MAX_SIZE 5      //cache最大存储量
#define MAX_NUMBER 200

class LRU{
private:
    list<int> cache;
    int hit_count = 0;      // 统计命中次数
    int number;             // 模拟数据个数
public:
    LRU(int n){
        number = n;
    }
    void LRUCache(int key);     // cache 访问函数
    void output();              // cache 内容输出函数
    void hit_rate();            // 计算命中率
};

void LRU::LRUCache(int key)
{
    if (cache.empty())  // 如果cache为空
    {
        cache.push_front(key);      //把key添加到cache中
    }
    else    //若cache不为空
    {
        list<int>::iterator it;
        it = find(cache.begin(), cache.end(), key);  // 查找key

        if (it != cache.end()){         //若在
            hit_count++;
            cout<<"Hit Great~~！！！！"<<endl;
            cache.erase(it);            //删除该位置的key元素
            cache.push_front(key);      //把key 添加到表头
        }
        else //若不在
        {
            if (cache.size() < MAX_SIZE){// 若缓存区未满,
                cache.push_front(key);   // 把该元素存入cache前面
            }
            else{                        // 若缓存区满了
                cache.pop_back();        // 删除cache尾部元素
                cache.push_front(key);   // 把该元素放到cache头部
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
    cout<<"命中率为："<<_rate<<"%"<<endl;
}

int main()
{
    int a[MAX_NUMBER], n;  //假设作为要访问数据
    cout<<"将要模拟访问数据的个数：   ";
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>a[i];
    LRU _cache(n);
    for (int i = 0; i < n; i++)
    {
        int key = a[i];
        cout<<"此时需要访问的数据：   "<<key<<endl;
        _cache.LRUCache(key);
        cout<<"数据访问后 cache 中的内容更改为：   ";
        _cache.output();
        cout<<endl;
    }
    _cache.hit_rate();
    return 0;
}







