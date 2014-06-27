/*
 * BST.h
 *
 *  Created on: May 6, 2014
 *      Author: twotani
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <class T>
class BST {
public:
	BST();
   ~BST();

	void remove(T* item);

	void insert(T* item);

	T* search(T* item);

	void print( );
	
	void print_non();

	bool isEmpty();

	int size();

private:

	class BSTNode { //private inner class

	public:
		BSTNode* left;
		T*       data;
		BSTNode* right;

		BSTNode(T* item) {

			data = item;
			left = NULL;
			right = NULL;
		}

		~BSTNode( ) {
			delete data;
		}

		bool isLeaf( ) {
			return (left == NULL && right == NULL);
		}

		bool hasOneEmptySubtree( ) {
			return (left == NULL || right == NULL);
		}
	};

	BSTNode* root; //points to the root node
	int     count; //number of nodes in this bst

	//========   H E L P E R  functions ===============//

	//locate the parent node of a node with item
	BSTNode* findParent(T* item);

	//traverse the nodes in inorder
	void traverse(BSTNode* p);
	
	//non-recursive traverse in order
	void traverse();

	//return the data found in this bst
	T* findItem(T* item);

	//return the node that contains item
	BSTNode* findNode(BSTNode* p, T* item);

	//delete a node with 0 or 1 subtree
	void case0or1Delete(BSTNode* parent, BSTNode* delNode);

	//delete a node with 2 subtrees
	void case2Delete(BSTNode* delNode);

	//clear all nodes
	void clear(BSTNode* p);

};

template <class T>
BST<T>::BST() {
	root = NULL;
	count = 0;
}

template <class T>
BST<T>::~BST() {
	clear(root);
}

template <class T>
void BST<T>::remove(T* item) {

	BSTNode* delNode = findNode(root, item);

    if (delNode != NULL) {

	   BSTNode* parent = findParent(item);

	   if (!delNode->hasOneEmptySubtree()) {
		 case2Delete(delNode);

	   } else {
		 case0or1Delete(parent, delNode);
	   }

	   count--;
   }
}

template <class T>
void BST<T>::insert(T* item) {

	BSTNode * p = new BSTNode(item);
	BSTNode * parent = findParent(item);

    if (parent == NULL) {
    	root = p;

    } else if (*item < *parent->data) {
    	parent->left = p;

    } else {
	    parent->right = p;
    }

    count++;
}

template <class T>
T* BST<T>::search(T* item) {
	return findItem(item);
}

template <class T>
void BST<T>::print( ) { //public
	traverse(root);
}

template <class T>
void BST<T>::print_non( ) { //public
	traverse();
}

template <class T>
bool BST<T>::isEmpty( ) {
	return size() == 0;
}

template <class T>
int BST<T>:: size( ) {
	return count;
}


//==============  HELPER function ================//

template <class T>
typename BST<T>::BSTNode* BST<T>::findParent(T* item){

	BSTNode* p      = root;
	BSTNode* parent = NULL;

	while (p != NULL) {

		if (*p->data == *item) break;

		parent = p; //move down the tree

		if (*item < *p->data) {
			p = p->left;

		} else {
			p = p->right;
		}
	}

	return parent;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::findNode(BSTNode* p, T* item) {

	if (p == NULL) {
	  return NULL;

   } else if (*item == *p->data ) {
	  return p;

   } else if (*item < *p->data) {
	  return findNode(p->left, item);

   } else {
	  return findNode(p->right, item);
   }
}

template <class T>
T* BST<T>::findItem(T* item) {

  BSTNode* p = findNode(root, item);

  return p == NULL ? NULL : p->data;
}

template <class T>
void BST<T>::traverse(BSTNode* p) {

   if (p != NULL) {
      traverse(p->left);

      cout << *p->data << " ";

      traverse(p->right);
   }
}

template <class T>
void BST<T>::traverse() {
	
	stack<BSTNode*> v;
	BSTNode* p = root;
		
	while(true){
		while (p != NULL){
//			cout<<"back to the top\n";
			v.push(p);
			p = p->left;
//			cout<<"just pushed "<<*p->data<<endl;
//			if(p==NULL) cout<<"p is NULL\n";
		}
//		cout<<"got out of the while loop "<<endl;
		if( v.empty() ) break;
		
		p  = v.top();
		cout<<*p->data<<" ";
		v.pop();		
		
		p = p->right;
	}
}

template <class T>
void BST<T>::clear(BSTNode* p) {

	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
}


template <class T>
void BST<T>::case0or1Delete(BSTNode* parent, BSTNode* delNode) {

   BSTNode* child;

   if (delNode->left == NULL) {
      child = delNode->right;
   } else {
      child = delNode->left;
   }

   if (parent == NULL) { //removing the root node
	   root = child;

   } else if (*delNode->data < *parent->data) {
      parent->left = child;

   } else {
      parent->right = child;
   }

   delete delNode;
}

template <class T>
void BST<T>::case2Delete(BSTNode* delNode) {

   BSTNode* predParent = delNode;
   BSTNode* pred = delNode->left;

   while (pred->right != NULL) { //find the predecessor
      predParent = pred;
      pred = pred->right;
   }

   delNode->data = pred->data; //copy ptr to pred data

   if (delNode->left != pred) {
      predParent->right = pred->left;
   } else {
      predParent->left = pred->left;
   }

   pred->data = NULL; //clear the link so data value won't get erased
   delete pred;
}


#endif /* BST_H_ */
