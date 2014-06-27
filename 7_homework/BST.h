/*
 * BST.h
 *
 *  Created on: May 6, 2014
 *      Author: twotani
 *  Modified on: May 19, 2014
 * 		Author: Zac Staples
 *		Changes: added int avgDepth();
 *				 added int maxHeightDifference();
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
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

	bool isEmpty();

	int size();
	
	int depth(int item);
	
	double avgDepth();
	
	int maxHeightDifference();
	//I need to ask about this one in class.  I'm not sure
	//how to compute the max difference. Is this the abosolute
	//differnece between the node's height and its most distance
	//grandchild, or some other measure.  If it's the first choice
	//then the max height difference will always be the height of
	//root measured to the farthest leaf.

private:

	class BSTNode { //private inner class

	public:
		BSTNode* left;
		T*       data;
		BSTNode* right;

		BSTNode(T* item) {

			data = item;
			left = right = NULL;
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
	
	//find the depth of an int
	int node_depth(int item) {
		return get_depth_util(root, item, 0);
	}
	
	//utility supporting node_depth for int nodes
	int get_depth_util(BSTNode* p, int data, int level){
		//I got stuck on this one because i am still learning how to 
		//implement recursive functions.  So I had to search the web for
		//some help and found this reference that I used as an outline for
		//the function below.
		//credit: http://www.geeksforgeeks.org/get-level-of-a-node-in-a-binary-tree
		if (p == NULL){
			return 0;
		}
		
		if(*(p->data) == data) {
			return level;
		}
		
		int downlevel = get_depth_util(p->left, data, level+1);
		if (downlevel != 0){
			return downlevel;
		}
		
		downlevel = get_depth_util(p->right, data, level+1);
		return downlevel;
	}
	
	//sum the depths of all nodes int nodes in the tree
	double sum_of_depths(BSTNode* p, double sum) {
		//I solved this one without searching the web.
		if (p != NULL) {
      sum = sum_of_depths(p->left, sum);

			sum += node_depth(*(p->data));
			//just use count while searching for p->data

			sum = sum_of_depths(p->right, sum);
   }
	 return sum;
	}
	
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
int BST<T>::depth(int item) {
	return node_depth(item);
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
bool BST<T>::isEmpty( ) {
	return size() == 0;
}

template <class T>
int BST<T>:: size( ) {
	return count;
}

template <class T>
double BST<T>:: avgDepth( ) {
	double sum = sum_of_depths(root, 0.0);
	double avg = sum / count;
	return avg;
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
	//I'm not sure how to build a non-recursive implementation of 
	//find node.  I'm trying to figure out how you would move
	//down the tree if you don't call p->left and p->right
	//as parameters of the search function.

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
