#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
    AVL<int> avl;
    Node<int>* root=0;

    root = avl.insert(root, 1,1000);
    root = avl.insert(root, 2,2000);
    root = avl.insert(root, 3,3000);
    root = avl.insert(root, 4,4000);
    root = avl.insert(root, 5,5000);

	AVL<string> map;
	Node<string>* r=0;
	r=map.insert(r,2,"two");
	r=map.insert(r,3,"three");
	r=map.insert(r,4,"four");
	r=map.insert(r,5,"five");
	r=map.insert(r,6,"six");
	r=map.insert(r,7,"seven");
    avl.printAll(root);
	map.printAll(r);
    return 0;
}
