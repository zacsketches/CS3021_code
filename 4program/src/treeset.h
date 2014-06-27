/*
 * treeset.h
 *
 * By Zac Staples
 * CS3021
 * Program Assigment 4
 * 23 June 2014
 *
 */

#ifndef TREESET_H
#define TREESET_H 

#include <vector>
#include "Set.h"

 using namespace std;

//*******************************************************************
//*                         OrderedList Data Structure
//*******************************************************************

//============================================================================
// Name        : OrderedList.h
// Author      : T. Otani  
//			   : Modified by Z. H. Staples, June 2014.
// 
// Description : An ordered binary tree list
//============================================================================

template <class T>
class OrderedList {

public:

	OrderedList();
	~OrderedList();

	//--------- Update Operations ----------------------------//
	void insert(T* item);
	void remove(T* item);

	//--------- Access Operations ----------------------------//
	T* first( );
	T* last( );

	T* next( );
	T* prev( );

	T* at(int idx);
			
	T* search(T* item);

	vector<T*> scan( );
	vector<T*> scan_rev( );

	//----------------- Queries ----------------------------//
	int size( );
	bool isEmpty( );
	
	//T* get_current() method used in testing to check the behavior of current in 
	//situations where I was calling next() and prev() at the ends of the list.
	//included only for compatibility with some of my test engines.
	//
	//  COMMENT OUT FOR SUBMISSION OR PUBLIC USE
	//
	//access the private current BSTNode*
	//T* get_current() { if(current != NULL) return current->data; return NULL; }

private:

	/*
	 * Unmodified BSTNode class provided in the assignment.
	 */

	class BSTNode { //private inner class

	public:
		BSTNode* left;
		T*    data;
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

	BSTNode* root;    //points to the root BSTNode
	int      count;   //number of BSTNodes in this list
	BSTNode* current; //points to the current BSTNode when scanning


	//========  H E L P E R  functions ===============//

	//locate the parent BSTNode of a BSTNode with item
	BSTNode* findParent(T* item);

	//traverse the BSTNodes in inorder and store into a vector vector<T*>
	void traverse(BSTNode* p, vector<T*>& list);
	
	//traverse the BSTNodes in reverse order and store into a vector<T*>
	void traverse_rev(BSTNode* p, vector<T*>& vec);
	
	//overloaded traverse to support at()
	void traverse(BSTNode* p, int& index, const int target, T*& ret_val);
	
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
	
	//move to the far left node recursively
	BSTNode* move_left(BSTNode* p);

	//move to the far right node recursively
	BSTNode* move_right(BSTNode* p);

};

//+++++++++++++++++++++  I M P L E M E N T A T I O N    +++++++++++++++++++++//

template <class T>
OrderedList<T>::OrderedList() {
	root = NULL;
	current = NULL;
	count = 0;
}

template <class T>
OrderedList<T>::~OrderedList() {
	clear(root);
}

template <class T>
void OrderedList<T>::insert(T* item){

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
	current = NULL;	//there is no current node after an insert operation

}


template <class T>
void OrderedList<T>::remove(T* item) {

	BSTNode* delNode = findNode(root, item);

    if (delNode != NULL) {

	   BSTNode* parent = findParent(item);

	   if (!delNode->hasOneEmptySubtree()) {
		 case2Delete(delNode);

	   } else {
		 case0or1Delete(parent, delNode);
	   }

	    count--;
		current = NULL;	//there is no current node after a remove operation
   }
}

template <class T>
T* OrderedList<T>::first( ) {

	BSTNode* p = move_left(root);
	
	// current becomes the first node after a call to first()
	current = p;
	
	return p->data;
}

template <class T>
T* OrderedList<T>::last( ) {

	BSTNode* p = move_right(root);
	
	// current becomes the last node after a call to last()
	current = p;
	
	return p->data;
}

template <class T>
T* OrderedList<T>::next( ) {
	
	//next on empty list returns NULL
	if(count == 0) return NULL;
	
	//when current is null we want to return the first node
	if(current == NULL ){
		return this->first();
	}
	
	//from the specification, when the last node is current and next is
	//called then return NULL and the last node remains the current node
	if(current == move_right(root)){
		return NULL;
	}
	
	BSTNode* target = current;

	/*
		Algorithm based on explanation at
		http://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
	*/

	/* Next has two cases:
		1. There is a right node attached to current (easy)
			a. Find minimum value in right subtree
		2. There is not a right node attached to current (hard)
			a. start from root and use a search technique where
			   we travel down the tree.  If the target node's value is 
			   greater than root then go right.  If the target node
			   is less than root then go left.  Update root on each
			   iteration. 
	*/
	//case 1.
	if(target->right != NULL ){
		BSTNode* p =  move_left(target->right);
		
		//update notion of current
		current = p;
		
		return p->data;
	}
	
	//case 2.
	T* res;
	BSTNode* next = NULL;
	BSTNode* search_point = root;
	while (search_point != NULL){
		if(*(target->data) == *(search_point->data)) {
			break;
		} else if (*(target->data) < *(search_point->data)){
			next = search_point;
			search_point = search_point->left;
		} else {
			search_point = search_point->right;
		}
	}
	res = next->data;
	
	current = next;	//update notion of current
	
	return res;
}

template <class T>
T* OrderedList<T>::prev( ) {

	//prev on empty list returns NULL
	if(count == 0) return NULL;
	
	//when current is null we want prev to return the last node
	if(current == NULL ){
		return this->last();
	}
	
	//from the specification, when the first node is current and prev is
	//called then return NULL and the first node remains the current node
	if(current == move_left(root)){
		return NULL;
	}
	
	BSTNode* target = current;
	
	/* Next has two cases:
		1. There is a left node attached to current (easy)
			a. Find maximum value in left subtree
		2. There is not a left node attached to current (hard)
			a. start from root and use a search technique where
			   we travel down the tree.  If the target node's value is 
			   greater than the search_point then go right.  If the target node
			   is less than the search_point then go left.  Update 
			   search_point on each iteration. 
	*/
	//case 1.
	if(target->left != NULL ){
		BSTNode* p =  move_right(target->left);
		
		current = p; //update notion of current
		
		return p->data;
	}
	
	//case 2.
	T* res;
	BSTNode* prev = NULL;
	BSTNode* search_point = root;
	
	while (search_point != NULL){
		if(*(target->data) == *(search_point->data)){
			break;
		} else if (*(target->data) < *(search_point->data)){
			search_point = search_point->left;
		} else {
			prev = search_point;
			search_point = search_point->right;
		} 
	}
	
	res = prev->data;
	
	current = prev;	//update notion of current
	
	return res;
}

template <class T>
T* OrderedList<T>::at(int i) {
	//return null for i outside legal range
	if(i<0 || i >= count) return NULL;
	
	//define reference variables
	int index = 0;
	const int target = i;
	T* ret_val;
	
	//call overlaoded version of traverse
	traverse(root, index, target, ret_val);
	
	return ret_val;
}

template <class T>
T* OrderedList<T>::search(T* item) {

	return findItem(item);
}

template <class T>
vector<T*> OrderedList<T>::scan( ) {
	vector<T*> v;

	traverse(root, v);

	return v;
}

template <class T>
vector<T*> OrderedList<T>::scan_rev( ) {
	vector<T*> v;
	
	traverse_rev(root, v);
	
	return v;
}

template <class T>
int OrderedList<T>:: size( ) {
	return count;
}

template <class T>
bool OrderedList<T>::isEmpty( ) {
	return size() == 0;
}

//*******************************************************************
//*                         HELPER FUNCTIONS
//*******************************************************************
template <class T>
typename OrderedList<T>::BSTNode* OrderedList<T>::findParent(T* item){

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
void OrderedList<T>::traverse(BSTNode* p, vector<T*>& vec) {

   if (p != NULL) {
      traverse(p->left, vec);

      vec.push_back(p->data);

      traverse(p->right, vec);
   }
}

template <class T>
void OrderedList<T>::traverse_rev(BSTNode* p, vector<T*>& vec) {
	if (p != NULL){
		traverse_rev(p->right, vec);
	
		vec.push_back(p->data);
		
		traverse_rev(p->left, vec);
	}
	
}

template <class T>
void OrderedList<T>::traverse(BSTNode* p, int& index, const int target, T*& ret_val){
	//overloaded version of traverse uses reference variables to keep track of index
	//as index is incremented.  The reference T*& return_value
	//is set to the correct index and is accessible in the calling function after
	// the traverse is complete.
	//
	//In solving this problem, I went from a 40 line solution down to six
	//lines of code.
	
	if(p != NULL){
		traverse(p->left, index, target, ret_val);

		if(index == target) {
			ret_val = p->data;
		}
		++index;				
		
		traverse(p->right, index, target, ret_val);
	}
}

template <class T>
T* OrderedList<T>::findItem(T* item) {

  BSTNode* p = findNode(root, item);

  return p == NULL ? NULL : p->data;
}

template <class T>
typename OrderedList<T>::BSTNode* OrderedList<T>::findNode(BSTNode* p, T* item) {

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
void OrderedList<T>::case0or1Delete(BSTNode* parent, BSTNode* delNode) {

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
void OrderedList<T>::case2Delete(BSTNode* delNode) {

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

template <class T>
void OrderedList<T>::clear(BSTNode* p) {
	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
}

template <class T>
typename OrderedList<T>::BSTNode* OrderedList<T>::move_left(BSTNode* p){
	BSTNode* res;
	if(p->left == NULL ){
		res = p;
	} else {
		res = move_left( p->left );
	}
	return res;
}

template <class T>
typename OrderedList<T>::BSTNode* OrderedList<T>::move_right(BSTNode* p){
	BSTNode* res;
	if(p->right == NULL ){
		res = p;
	} else {
		res = move_right( p->right );
	}
	return res;
}


//*******************************************************************
//*                         TREESET
//*******************************************************************
class TreeSet: public Set {
public:
    TreeSet();

    ~TreeSet() { elem.~OrderedList<string>(); }
    
	//--------- Update Operations ----------------------------//
	 void insert(string item);

	 void remove(string item);

	//--------- Set Operations ----------------------------//
	 Set* set_union(Set* s2); //set union

	 Set* set_intersect(Set* s2); //set intersection

	 Set* set_diff(Set* s2); //set difference


	//--------- Access Operations --------------------//
	 vector<string> scan( );

	//--------- Queries ----------------------------//
     int size( );

	 bool isEmpty( );

	 bool in(string item);

private:
    OrderedList<string> elem; 	

	//copy constructor
	TreeSet(TreeSet* ts);
};

#endif /* TREESET_H */
