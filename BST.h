
#pragma once
#include <iostream>
#include "TreeNode.h"
#include <cstddef>
#include <fstream>
#define MARKER -1
using namespace std;

template <class T, class V>
class BST{

    private:
        

    public:
		TreeNode<T,V> *root;
        BST();
        ~BST();
    
        V searchKey(T key );
        bool insert(T key, V value);
        V deleteNode(T key);

        //helper function
        bool isEmpty();
        TreeNode<T,V>*getMin();
        TreeNode<T,V>*getMax();
        void recPrint(TreeNode<T,V> *node);
        TreeNode<T,V>* getSuccessor(TreeNode<T,V>* d);
        void printTree();
		void serialize(TreeNode<T,V>* root, FILE *fp);

};

template <class T, class V>
BST<T,V>::BST()
{
    root = NULL; //empty tree
}

template <class T, class V>
BST<T,V>::~BST()
{

}

//NOTE: This function is not my code, it was taken from https://www.geeksforgeeks.org/serialize-deserialize-binary-tree/
//I really didn't understand what serilization was but now looking at this code I think I get it 
template <class T, class V>
void BST<T,V>::serialize(TreeNode<T,V>* root, FILE *fp) 
{ 
    // If current node is NULL, store marker 
    if (root == NULL) 
    { 
        fprintf(fp, "%d ", MARKER); 
        return; 
    } 
  
    // Else, store current node and recur for its children 
    fprintf(fp, "%d ", root->key); 
    serialize(root->left, fp); 
    serialize(root->right, fp); 
}

//recursively prints TreeNode, in order traversal
template <class T, class V>
void BST<T,V>::recPrint(TreeNode<T,V> *node)
{
    if(node == NULL)
        return;

    recPrint(node->left);
    cout << node->value->to_string() << endl;
    recPrint(node->right);
}

template <class T, class V>
void BST<T,V>::printTree()
{
    recPrint(root);
}

//finds the Max in a tree
template <class T, class V>
TreeNode<T,V>*BST<T,V>::getMax()
{
    TreeNode<T,V>*current = root;
    if(root == NULL) //empty TREENODE
        return NULL;

    while(current->right != NULL)
    {
        current = current->right;
    }

    return current;
}

//inserts a node into the tree given a key and a value, 
//returns bool on wether or not the key given was vallid
template <class T, class V>
bool BST<T,V>::insert(T key, V value){

    TreeNode<T,V>*node = new TreeNode<T,V>(key, value);
    if (root == NULL){
        //empty Tree
        root = node;
    }
    else
    {
        //tree is not empty, we need to find the insertion location 
        TreeNode<T,V>*current = root;
        TreeNode<T,V>*parent = NULL;

        while(true)
        {
			
            parent = current;
			// if the key is equal to another key then the user should choose another key
			if (key == current->key)
			{
				cout << "ERROR: ID already exists, choose a different ID" << endl;
				return false;
			}

            if(key < current->key)
            {
                current = current->left;
                //going left
                if (current == NULL)
                {
                    //we found our insertion point
                    parent->left = node;
                    break;
                }
            }
            else
            {
                //go right
                current = current->right;
                if (current == NULL)
                {
                    //we found our insertion point
                    parent->right = node;
                    break;
                }
            }
            
        }

    }
	return true;
    
}

//searches tree given a key and returns the value 
template <class T, class V>
V BST<T,V>::searchKey(T key)
{
    if(root == NULL)//empty tree
	{
        return NULL;
	}
    else{
        //tree is not empty, lets attempt to look for it
        TreeNode<T,V> *current = root;
        while (current->key != key)
        {
            if(key < current->key)
                current = current->left;
            else
                current = current->right;

            if(current == NULL)// we did not find the value 
                return NULL;
            
        }
		return current->value;
    }
   
}

// delete a node given a key, returns the value that was deleted 
template <class T, class V>
V BST<T,V>::deleteNode(T key)
{
	//check to see if the tree is empty
	if (root == NULL)
	{
		return NULL;
		
	}
	TreeNode<T,V>* current = root;
	TreeNode<T,V>* parent = root;
	bool isLeft = true; // determines whether the node is a left child or not
	//now were going to search for the node
	while (current->key != key)
	{
		parent = current;
		if (key < current->key)
		{
			isLeft = true;
			current = current->left;
		}
		else
		{
			isLeft = false;
			current = current->right;
		}
		if (current == NULL)
		{
			//did not find the value
			return NULL;
		}
	}
		//if we make it here, we have found the node that needs to be deleted
		//now check the different cases
	V deletedObject = current->value;
	//no children
	//check if node to be deleted is a leaf node
	if (current->left == NULL && current->right == NULL)
	{

		if (current == root)
		{
			root = NULL;
		}
		else if (isLeft)
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;
		}
	}
	//node to be deleted has one child, we need to determine if child is left or right and continue
	else if (current->right == NULL) //child has no right child
	{
		if (current == root)
		{
			root = current->left;
		}
		else if (isLeft)
		{
			parent->left = current->left;
		}
		else
		{
			parent->right = current->left;
		}
	}
	//has no left child
	else if (current->left == NULL) //child has no right child
	{
		if (current == root)
		{
			root = current->right;
		}
		else if (isLeft)
		{
			parent->left = current->right;
		}
		else
		{
			parent->right = current->right;
		}
	}

	//the node to be deleted has two children
	else
	{
		TreeNode<T,V>* successor = getSuccessor(current);

		if (current == root)
		{
			root = successor;
		}
		else if (isLeft)
		{
			parent->left = successor;
		}
		else
		{
			parent->right = successor;
		}

		successor->left = current->left;
	}
	return deletedObject;
	
}

template <class T, class V>
TreeNode<T,V>* BST<T,V>::getSuccessor(TreeNode<T,V>* d) // d is the node to be deleted
{
	//sp = successor parent
	TreeNode<T, V>* sp = d; //node to be deleted
	TreeNode<T, V>* successor = d;
	//start one right
	TreeNode<T, V>* current = d->right;

	//one right and all the way left
	while (current != NULL)
	{
		sp = successor;
		successor = current;
		current = current->left;
	}

	if (successor != d->right)
		//successor is a descendant of the right child
	{
		sp->left = successor->right;
		successor->right = d->right;
	}

	return successor;
}