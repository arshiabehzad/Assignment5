
#pragma once
using namespace std;
#include <cstddef>

template <class T, class V>
class TreeNode
{
    public:
        TreeNode();
        TreeNode(T k, V value); //k = key, which in this example is also the value(data)
        ~TreeNode(); //when creating atemplate class destructor must be virtual

        T key;
        V value;
        TreeNode<T,V> *left;
        TreeNode<T,V>*right;
};

template <class T, class V>
TreeNode<T,V>::TreeNode()
{
    key = NULL;
    left = NULL;
    right = NULL;
    value = NULL;
}

template <class T, class V>
TreeNode<T,V>::TreeNode(T k, V value)
{
    this->key = k;
    this->value = value;
    left = NULL;
    right = NULL;
}

template <class T, class V>
TreeNode<T,V>::~TreeNode(){
    
}

