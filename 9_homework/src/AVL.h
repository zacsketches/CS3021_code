/*
 * AVL.h
 *
 *  Created on: Aug 31, 2011
 *      Author: twotani
 *
 *  Updated: May, 2014
 */

#include <vector>
#include <iostream>
using namespace std;

template<class T>
class AVL {

public:

	enum TRAVERSAL {
		PRE, IN, POST
	};

	AVL();

	~AVL();

	void remove(T* item);

	void insert(T* item);

	T* search(T* item);

	bool isEmpty();

	int size();

	int height();

	// return the average depth of the AVL;
	double avgDepth();

	vector<T*> scan(TRAVERSAL order); //inorder, preorder, or postorder traversal

private:

	enum BF {
		tallLeft, equalHeight, tallRight
	};

	class Node { //private inner class

	public:

		Node * left;
		T* data;
		Node * right;
		BF bf; //balance factor

		Node(T* item) {

			data = item;
			left = right = NULL;
			bf = equalHeight;
		}

		bool isLeaf() {
			return (left == NULL && right == NULL);
		}

		bool hasOneEmptySubtree() {
			return (left == NULL || right == NULL);
		}
	};

	Node * root;

	int count;

	void clear(Node* p);

	//--------------- insert routines -----------------------------//
	bool add(Node*& p, T* item);

	bool adjust(Node*& pivot, Node* child, T* item);

	//---------------- delete routines ----------------------------//
	bool del(Node*& p, T* item);

	bool delFromLeftAdjust(Node*& pivot);

	bool delFromRightAdjust(Node*& pivot);

	bool delPred(Node*& p, T*& item);

	bool detach(Node*& delnode);

	//------------------ rotations ---------------------------------//
	void rotate(Node*& pivot, Node* child, Node* grandchild);

	void rotateLL(Node*& pivot, Node* child);
	void rotateRR(Node*& pivot, Node* child);

	void rotateLR(Node*& pivot, Node* child, Node* grandchild);
	void rotateRL(Node*& pivot, Node* child, Node* grandchild);

	//------------------- traversals -------------------------------//
	void inorder(Node* p, vector<T*>& list);

	void preorder(Node* p, vector<T*>& list);

	void postorder(Node* p, vector<T*>& list);

	//------------------- other helper functions----------------------//

	// returns the height of the subtree rooted at p
	int height(Node * p);

	//returns the sum of the depths of each node
	int totalDepth(Node* p, int myDepth);

};

template<class T>
AVL<T>::AVL() {

	root = NULL;
	count = 0;
}

template<class T>
AVL<T>::~AVL() {

	//delete all nodes
	clear(root);
}

template<class T>
void AVL<T>::insert(T* item) {

	add(root, item);
	count++;
}

template<class T>
void AVL<T>::remove(T* item) {

	if (search(item) != NULL) {
		del(root, item);
		count--;
	}
}

template<class T>
T* AVL<T>::search(T* item) {

	Node* p = root;

	while (p != NULL) {

		if (*item == *p->data) {

			return p->data;

		} else if (*item < *p->data) {

			p = p->left;

		} else {

			p = p->right;
		}
	}

	return NULL;
}

template<class T>
bool AVL<T>::isEmpty() {

	return count == 0;
}

template<class T>
int AVL<T>::size() {

	return count;
}

template<class T>
vector<T*> AVL<T>::scan(TRAVERSAL order) {

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

//------------------ Private Methods -------------------------------//

template<class T>
bool AVL<T>::add(Node*& p, T* item) {
	//add new leaf node to the p tree. if the height of
	//p increases after the insertion, return true.
	//Otherwise return false
	bool hasGrown = false;

	if (p == NULL) {

		p = new Node(item); //add a new leaf node

		hasGrown = true; //from empty to one node, so it became one level taller

	} else if (*item < *p->data) {

		hasGrown = add(p->left, item);

		if (hasGrown) { 					//left subtree of p has grown by 1
			hasGrown = adjust(p, p->left, item); //so adjust bf's and rotate of necessary
		}

	} else {

		hasGrown = add(p->right, item);

		if (hasGrown) {						//right subtree of p has grown by 1
			hasGrown = adjust(p, p->right, item); //adjust bf's and rotate if necessary
		}
	}

	return hasGrown;
}

template<class T>
bool AVL<T>::adjust(Node*& pivot, Node* child, T* item) {

	bool hasGrown;

	//CASE 1: pivot was perfectly balanced before insertion
	//        After insertion it becomes either tall left or tall right.
	//        The height of pivot grows by 1, so set hasGrown to true

	if (pivot->bf == equalHeight) {	//was equal height before insertion

		if (child == pivot->right) { //and item was added to the right subtree

			pivot->bf = tallRight; //so now it's taller on right

		} else {

			pivot->bf = tallLeft; //added to left subtree so now taller on left
		}

		hasGrown = true;

	} else if ((pivot->bf == tallLeft && child == pivot->right)
			|| (pivot->bf == tallRight && child == pivot->left)) {

		//CASE 2: pivot was off balance by 1 before insertion and the new node was added
		//        to the shorter subtree, so now pivot becomes perfectly balanced.
		//		  The height of pivot remains the same, i.e. hasGrown is false

		pivot->bf = equalHeight;

		hasGrown = false;

	} else {  //(pivot->bf == tallLeft && child == pivot->left) ||
			  //(pivot->bf == tallRight && child == pivot->right)

		//CASE 3: pivot was off balance by 1 before insertion and the new node was added
		//        to the taller subtree, so now pivot is unbalanced and need rotation
		//        After rotation, the height of pivot remains the same

		Node * grandchild = (*item < *child->data) ? child->left : child->right;

		rotate(pivot, child, grandchild);

		hasGrown = false;
	}

	return hasGrown;
}

//=========================== Delete Routines ===========================//

template<class T>
bool AVL<T>::del(Node*& p, T* item) {
	//this del function is called only when the item is in the tree
	//so we don't worry about the unsuccessful search

	bool hasShrunk = false;

	if (*item == *p->data) { //found the node to delete

		hasShrunk = detach(p); //after detaching p node, a new pointer value
		//is passed back to the reference parameter p. Which node
		//p points to, after deletion, depends on the deletion case

	} else if (*item < *p->data) {

		hasShrunk = del(p->left, item);

		if (hasShrunk) {
			hasShrunk = delFromLeftAdjust(p); //adjust balance and perhaps rotate when
		}							 //the node is deleted from p's left subtree

	} else {

		hasShrunk = del(p->right, item);

		if (hasShrunk) {
			hasShrunk = delFromRightAdjust(p);//adjust balance and perhaps rotate when
		}							//the node is deleted from p's right subtree
	}

	return hasShrunk;
}

template<class T>
bool AVL<T>::detach(Node*& delNode) {

	bool hasShrunk;

	if (delNode->isLeaf()) { //CASE 0 deletion: delNode is a leaf

		delNode = NULL;

		hasShrunk = true;

	} else if (delNode->hasOneEmptySubtree()) { //CASE 1: delNode has one nonempty subtree

		delNode = (delNode->left != NULL) ? delNode->left : delNode->right;

		hasShrunk = true;

	} else { //CASE 2 deletion: delNode has two nonempty subtrees

		//locate and delete the predecessor of delNode from the AVL.
		//Predecessor has empty right subtree; predecessor of delNode
		//comes from delNode's left subtree

		hasShrunk = delPred(delNode->left, delNode->data);

		if (hasShrunk) {
			hasShrunk = delFromLeftAdjust(delNode);
		}

	}

	return hasShrunk;
}

template<class T>
bool AVL<T>::delFromLeftAdjust(Node*& pivot) {

	bool hasShrunk;

	//CASE 1: Balanced pivot before deletion; node removed from pivot
	//        left subtree so now pivot is tallRight after deletion

	if (pivot->bf == equalHeight) {

		pivot->bf = tallRight;     //removed from left so tallRight now

		hasShrunk = false;         //height of pivot does not change

		//CASE 2: tallLeft pivot before deletion and node deleted
		//        from the taller left subtree. After deletion, pivot becomes equalHeight
		//        and its height shrinks by one

	} else if (pivot->bf == tallLeft) {

		pivot->bf = equalHeight;

		hasShrunk = true;

		//CASE 3: tallRight pivot before deletion and node deleted from shorter
		//        left subtree. Needs either RL or RR rotation. Height of pivot
		//        shrinks by one

	} else { //pivot->bf == tallRight

		Node* rchild = pivot->right; //because it was tallRight, we know rchild is not NULL

		if (rchild->bf == tallLeft) {

			rotateRL(pivot, rchild, rchild->left);

		} else {

			rotateRR(pivot, rchild);
		}

		hasShrunk = true;

	}

	return hasShrunk;
}

template<class T>
bool AVL<T>::delFromRightAdjust(Node*& pivot) {

	bool hasShrunk;

	//CASE 1: Balanced pivot before deletion; node removed from pivot
	//        right subtree so now pivot is tallLeft after deletion

	if (pivot->bf == equalHeight) {

		pivot->bf = tallLeft;     //removed from right so tallLeft now

		hasShrunk = false;         //height of pivot does not change

		//CASE 2: tallRight pivot before deletion and node deleted
		//        from the taller right subtree. After deletion, pivot becomes equalHeight
		//        and its height shrinks by one

	} else if (pivot->bf == tallRight) {

		pivot->bf = equalHeight;

		hasShrunk = true;

		//CASE 3: tallLeft pivot before deletion and node was deleted from shorter
		//        right subtree. Needs either LR or LL rotation. Height of pivot
		//        shrinks by one

	} else { //pivot->bf == tallLeft

		Node* lchild = pivot->left; //because it was tallLeft, we know lchild is not NULL

		if (lchild->bf == tallRight) {

			rotateLR(pivot, lchild, lchild->right);

		} else {

			rotateLL(pivot, lchild);
		}

		hasShrunk = true;
	}

	return hasShrunk;
}

template<class T>
bool AVL<T>::delPred(Node*& p, T*& delNodeItem) {

	bool hasShrunk;

	//This is a specialized recursive deletion routine just for removing the
	//predecessor node of delNode in CASE 2 of the detach method. This
	//function recursively calls itself while going deeper into the
	//right subtree, and as the call comes back we adjust the balance factors
	//and rotate as necessary

	if (p->right == NULL) { //found the predecessor of delNode to delete

		Node* t = p;

		delNodeItem = p->data;

		p = p->left;

		delete t;

		hasShrunk = true;

	} else { //keep going deeper into the right subtree looking for the predecessor

		hasShrunk = delPred(p->right, delNodeItem);

		if (hasShrunk) {

			hasShrunk = delFromRightAdjust(p);
		}					//if we make at least one recursive, call then
	}						//we know the predecessor of delNode is not left
							//child of delNode. Predecessor is a right child
							//of intermediate node so we use delFromRightAdjust here
	return hasShrunk;
}

//=========================== Rotations ===========================//
template<class T>
void AVL<T>::rotate(Node*& pivot, Node* child, Node* grandchild) {

	if (child == pivot->left) {

		if (grandchild == child->left) {

			rotateLL(pivot, child);

		} else {

			rotateLR(pivot, child, grandchild);
		}

	} else {

		if (grandchild == child->right) {

			rotateRR(pivot, child);

		} else {

			rotateRL(pivot, child, grandchild);
		}
	}
}

template<class T>
void AVL<T>::rotateLL(Node*& pivot, Node* child) {
	pivot->left = child->right;
	child->right = pivot;

	pivot->bf = equalHeight;
	child->bf = equalHeight;

	pivot = child;
}

template<class T>
void AVL<T>::rotateRR(Node*& pivot, Node* child) {
	pivot->right = child->left;
	child->left = pivot;

	pivot->bf = equalHeight;
	child->bf = equalHeight;

	pivot = child;
}

template<class T>
void AVL<T>::rotateLR(Node*& pivot, Node* child, Node* grandchild) {
	child->right = grandchild->left;
	pivot->left = grandchild->right;

	grandchild->left = child;
	grandchild->right = pivot;

	if (grandchild->bf == tallLeft) {

		child->bf = equalHeight;
		pivot->bf = tallRight;

	} else if (grandchild->bf == tallRight) {

		child->bf = tallLeft;
		pivot->bf = equalHeight;

	} else { //grandchild->bf == equalHeight
		//this case happens only when the grandchild is the newly inserted node

		child->bf = equalHeight;
		pivot->bf = equalHeight;

	}

	grandchild->bf = equalHeight;

	pivot = grandchild;
}

template<class T>
void AVL<T>::rotateRL(Node*& pivot, Node* child, Node* grandchild) {
	child->left = grandchild->right;
	pivot->right = grandchild->left;

	grandchild->left = pivot;
	grandchild->right = child;

	if (grandchild->bf == tallLeft) {

		child->bf = tallRight;
		pivot->bf = equalHeight;

	} else if (grandchild->bf == tallRight) {

		child->bf = equalHeight;
		pivot->bf = tallLeft;

	} else { //grandchild->bf == equalHeight
		//this case happens only when the grandchild is the newly inserted node

		child->bf = equalHeight;
		pivot->bf = equalHeight;
	}

	grandchild->bf = equalHeight;

	pivot = grandchild;
}

template<class T>
void AVL<T>::clear(Node* p) {

	if (p == NULL)
		return;

	clear(p->left);
	clear(p->right);

	delete p;
}

//=========================== Traversals ===========================//

template<class T>
void AVL<T>::inorder(Node* p, vector<T*>& orderlist) {

	if (p != NULL) {

		inorder(p->left, orderlist);

		orderlist.push_back(p->data);

		inorder(p->right, orderlist);
	}
}

template<class T>
void AVL<T>::preorder(Node* p, vector<T*>& orderlist) {

	if (p != NULL) {

		orderlist.push_back(p->data);

		preorder(p->left, orderlist);

		preorder(p->right, orderlist);
	}
}

template<class T>
void AVL<T>::postorder(Node* p, vector<T*>& orderlist) {

	if (p != NULL) {

		postorder(p->left, orderlist);

		postorder(p->right, orderlist);

		orderlist.push_back(p->data);
	}
}


template<class T>
int AVL<T>::height() {
	return height(root);
}

template<class T>
int AVL<T>::height(Node * p) {
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
double AVL<T>::avgDepth() {
	return (double) totalDepth(root, 0)/count;
}

//returns the sum of the depths of each node
template<class T>
int AVL<T>::totalDepth(Node* p, int myDepth) {
	if (p == NULL)
		return 0;
	else {
		int leftDepth = totalDepth(p->left, myDepth+1);
		int rightDepth = totalDepth(p->right, myDepth+1);
		return leftDepth + rightDepth + myDepth;
	}
}
