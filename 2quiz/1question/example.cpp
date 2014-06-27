//============================================================================
// Name        : ListExample_LinkedListImplementation_Struct.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "List.h"
using namespace std;

int main() {
	// declare an empty list
	List myList;

	append(myList, 10);
	append(myList, 20);
	append(myList, 30);

	// scan the list
	cout<<"The original list: \n";
	for (int i = 0; i < len(myList); i++) {
		cout << "\t"<<element(myList, i) << endl;
	}
	
	Node* rev = reverse(myList.head);
	// scan the list
	cout<<"The rev list: \n";
	while(rev != NULL ){
		cout<<"\t"<<rev->data<<endl;
		rev = rev->next;
	}
	

	return 0;
}
