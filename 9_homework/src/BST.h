/*
 * BST.h
 *
 *  Created on: May 6, 2014
 *      Author: twotani
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
using namespace std;

template<class T>
class BST {
public:

	enum TRAVERSAL {
		PRE, IN, POST
	};

	BST();

	~BST();

	void remove(T* item);

	void insert(T* item);

	T* search(T* item);

	void print();

	bool isEmpty();

	int size();

	int height();

	// return the average depth of the BST();
	double avgDepth();

	vector<T*> scan(TRAVERSAL order); //inorder, preorder, or postorder traversal

private:

	class BSTNode { //private inner class

	public:
		BSTNode* left;
		T* data;
		BSTNode* right;

		BSTNode(T* item) {

			data = item;
			left = right = NULL;
		}

		~BSTNode() {
			delete data;
		}

		bool isLeaf() {
			return (left == NULL && right == NULL);
		}

		bool hasOneEmptySubtree() {
			return (left == NULL || right == NULL);
		}
	};

	BSTNode* root; //points to the root node
	int count; //number of nodes in this bst

	//========   H E L P E R  functions ===============//

	//locate the parent node of a node with item
	BSTNode* findParent(T* item);

	//traverse the nodes in inorder
	void traverse(BSTNode* p);

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

	// returns the height of the subtree rooted at p
	int height(BSTNode * p);

	//returns the sum of the depths of each node
	int totalDepth(BSTNode* p, int myDepth);

	//------------------- traversals -------------------------------//
	void inorder(BSTNode* p, vector<T*>& list);

	void preorder(BSTNode* p, vector<T*>& list);

	void postorder(BSTNode* p, vector<T*>& list);

};

template<class T>
BST<T>::BST() {
	root = NULL;
	count = 0;
}

template<class T>
BST<T>::~BST() {
	clear(root);
}

template<class T>
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

template<class T>
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

template<class T>
T* BST<T>::search(T* item) {
	return findItem(item);
}

template<class T>
void BST<T>::print() { //public
	traverse(root);
}

template<class T>
bool BST<T>::isEmpty() {
	return size() == 0;
}

template<class T>
int BST<T>::size() {
	return count;
}

//==============  HELPER function ================//

template<class T>
typename BST<T>::BSTNode* BST<T>::findParent(T* item) {

	BSTNode* p = root;
	BSTNode* parent = NULL;

	while (p != NULL) {

		if (*p->data == *item)
			break;

		parent = p; //move down the tree

		if (*item < *p->data) {
			p = p->left;

		} else {
			p = p->right;
		}
	}

	return parent;
}

template<class T>
typename BST<T>::BSTNode* BST<T>::findNode(BSTNode* p, T* item) {

	if (p == NULL) {
		return NULL;

	} else if (*item == *p->data) {
		return p;

	} else if (*item < *p->data) {
		return findNode(p->left, item);

	} else {
		return findNode(p->right, item);
	}
}

template<class T>
T* BST<T>::findItem(T* item) {

	BSTNode* p = findNode(root, item);

	return p == NULL ? NULL : p->data;
}

template<class T>
void BST<T>::traverse(BSTNode* p) {

	if (p != NULL) {
		traverse(p->left);

		cout << *p->data << " ";

		traverse(p->right);
	}
}

template<class T>
void BST<T>::clear(BSTNode* p) {

	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
}

template<class T>
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

template<class T>
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

template<class T>
int BST<T>::height() {
	return height(root);
}

template<class T>
int BST<T>::height(BSTNode * p) {
	if (p == NULL) {
		return -1;
	} else {
		int leftHeight = height(p->left);
		int rightHeight = height(p->right);
		if (leftHeight >= rightHeight) {
			return 1 + leftHeight;
		} else {
			return 1 + rightHeight;
		}
	}
}

// return the average depth of the BST()
template<class T>
double BST<T>::avgDepth() {
	return (double) totalDepth(root, 0)/count;
}

//returns the sum of the depths of each node
template<class T>
int BST<T>::totalDepth(BSTNode* p, int myDepth) {
	if (p == NULL)
		return 0;
	else {
		int leftDepth = totalDepth(p->left, myDepth+1);
		int rightDepth = totalDepth(p->right, myDepth+1);
		return leftDepth + rightDepth + myDepth;
	}
}

template<class T>
vector<T*> BST<T>::scan(TRAVERSAL order) {

	vector<T*> resultList;

	switch (order) {

	case IN:
		inorder(root, resultList);
		break;

	case PRE:
		preorder(root, resultList);
		break;

	case POST:
		postorder(root, resultList);
		break;
	}

	return resultList;
}

//=========================== Traversals ===========================//

template<class T>
void BST<T>::inorder(BSTNode* p, vector<T*>& orderlist) {

	if (p != NULL) {

		inorder(p->left, orderlist);

		orderlist.push_back(p->data);

		inorder(p->right, orderlist);
	}
}

template<class T>
void BST<T>::preorder(BSTNode* p, vector<T*>& orderlist) {

	if (p != NULL) {

		orderlist.push_back(p->data);

		preorder(p->left, orderlist);

		preorder(p->right, orderlist);
	}
}

template<class T>
void BST<T>::postorder(BSTNode* p, vector<T*>& orderlist) {

	if (p != NULL) {

		postorder(p->left, orderlist);

		postorder(p->right, orderlist);

		orderlist.push_back(p->data);
	}
}

#endif /* BST_H_ */
