/*
 * List.cpp
 *
 *  Updated on 5/1/2014 Zac Staples
 *  based on course material provided by T. Otani
 */

#include <iostream>
#include "List.h"
using namespace std;


Node* reverse(Node* L) {
	Node* p = L; 	//List iterator
	
	Node* r;		//pointer into new List
	Node* q = NULL;	//backward pointing interator

	/* original  __________        __________        __________      __________
	            |         | ----> |         | ----> |         | --> |         |-->NULL
	            |_________|       |_________|       |_________|     |_________|
	                p...iterator through the original list
	*/ 

	/* final     __________        __________        __________      __________
	     NULL<--|         | <---- |         | <---- |         | <-- |         |
	     |      |_________|       |_________|       |_________|     |_________|
	     q          r                                    
	        
	     r is a new node created in each loop
	     q provides a backward reference to link r after each addition
	*/
	
	
	while(p != NULL){
		r = new Node;
		r->data = p->data;
		r->next = q;
		
		p=p->next;  //advance through the oridinal list
		q = r;		//keep a reference to the recently created node to link backwards
	}
	
	return r;
}


// len returns the number of elements in L
int len(List L) {
	return L.cnt;
}

// add elt to the end of L
void append(List& L, int elt) {
	Node* newNode = new Node;
	newNode->data = elt;
	newNode->next = NULL;

	if (L.cnt == 0) {
		L.head = L.tail = newNode;
	}
	else {
		L.tail->next = newNode;
		L.tail = newNode;
	}
	L.cnt++;
}

// insert elt at position index in L
void insert(List& L, int index, int elt) {
	if (index < 0 or index >= L.cnt) {
		cout << "invalid index" << endl;
	}
	else {
		Node* newNode = new Node;
		newNode->data = elt;
		newNode->next = NULL;

		if (index == 0) { // insert to the front of list
			newNode->next = L.head;
			L.head = newNode;
		}
		else if (index == L.cnt) { // insert to the end of list
			append(L, elt);
		}
		else {
			// finds the (index-1)th node
			Node* current = L.head;
			for (int i = 0; i < index-1; i++) {
				current = current->next;
			}
			// perform list splicing
			newNode->next = current->next;
			current->next = newNode;
		}
		L.cnt ++;
	}
}

// returns true if elt is in L
bool in(List L, int elt) {
	bool found = false;
	Node* current = L.head;
	while (current != NULL and not found) {
		found = (current->data == elt);
		current = current->next;
	}
	return found;
}

// return the element at position index
int element(List L, int index) {
	if (index < 0 or index >= L.cnt) {
		cout << "invalid index" << endl;
		return -1;
	}
	else {
		// finds the (index)th node
		Node* current = L.head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}

		return current->data;
	}
}


