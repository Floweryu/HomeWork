#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include<iostream>
using namespace std;
template<typename T>
class Node
{
public:
    Node* left;
    Node* right;

    int key;
    int height;
	T value;
    Node(int key,T value)
    {
        this->key = key;
        left = right = 0;
        height = 1;
        this->value=value;
    }
};
template<typename T>
class AVL
{
public:
    int getHeight(Node<T>* node)
    {
        if(node == 0)
            return 0;

        return node->height;
    }
    Node<T>* updateHeight(Node<T>* node)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }
    Node<T>* insert(Node<T>* root, int key,T value)
    {
        if(root == 0)
            return new Node<T>(key,value);

        if(root->key < key)
            root->right = insert(root->right, key,value);
        else if(root->key == key)
        {
            cout<<"key: "<<key<<" No duplicate vertex allowed."<<endl;
            return root;
        }
        else
            root->left = insert(root->left, key,value);

        root = updateHeight(root);

        int balance_factor = getHeight(root->left) - getHeight(root->right);

        // LR rotation
        if(balance_factor > 1 && root->left->key < key)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // RR rotation
        else if(balance_factor > 1 && root->left->key > key)
            return rightRotate(root);
        // LL rotation
        else if(balance_factor < -1 && root->right->key < key)
            return leftRotate(root);
        // RL rotation
        else if(balance_factor < -1 && root->right->key > key)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node<T>* leftRotate(Node<T>* root)
    {
        Node<T>* x = root->right;
        Node<T>* t = x->left;

        root->right = t;
        x->left = root;

        // update height
        x = updateHeight(x);
        root = updateHeight(root);

        return x;
    }
    Node<T>* rightRotate(Node<T>* root)
    {
        Node<T> *x = root->left;
        Node<T> *t = x->right;

        root->left = t;
        x->right = root;

        // update height
        root = updateHeight(root);
        x = updateHeight(x);

        return x;
    }
    void printAll(Node<T>* root)
    {
        if(root->left != 0)
            printAll(root->left);

        cout<<root->key<<" : "<<root->value<<endl;

        if(root->right != 0)
            printAll(root->right);
    }
};



#endif // MAP_H_INCLUDED
