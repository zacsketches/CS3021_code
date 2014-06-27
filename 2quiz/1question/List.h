/*
 * List.h
 *
 *  Created on: Apr 2, 2014
 *      Author: localadmin
 */

#ifndef LIST_H_
#define LIST_H_

// declaring a list node structure
struct Node {
  int data;     // data field
  Node* next;   // link field
};

// declare the list header structure
struct List {
	int cnt;
	Node* head;
	Node* tail;
	List() {
		cnt = 0;
		head = NULL;
		tail = NULL;
	}
};


// -----------------------------------------------
// signatures of the utility functions for List
// -----------------------------------------------

// len returns the number of elements in L
int len(List L);

// add elt to the end of L
void append(List& L, int elt);

// insert elt at position index in L
void insert(List& L, int index, int elt);

// returns true if elt is in L
bool in(List L, int elt);

// return the element at position index
int element(List L, int index);

//return a new list
Node* reverse(Node* L);

#endif /* LIST_H_ */
