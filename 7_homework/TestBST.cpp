//============================================================================
// Name        : TestBST.cpp
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : Main program for testing the BST class
//============================================================================

#include "Pet.h"
#include "BST.h"
#include <iostream>
using namespace std;

void testIntBST( ) {

	BST<int> * bst = new BST<int>( );

	cout << "BEFORE INSERT Count: " << bst->size() << endl;

//	int val[] = {80, 40, 30, 60, 50, 10, 90, 70, 20};
//	int size = 9;
	int val[] = {80, 40, 30, 90, 10, 20, 25, 22};
	int size = 8;

	int** item;

	item = new int*[size];


	for (int i = 0; i < size; i++) {

		item[i] = new int(val[i]);

		bst->insert(item[i]);
	}

	cout << "AFTER INSERT Count: " << bst->size() << endl;
	bst->print(); cout << endl;
	
	cout << "Testing get node_depth:\n";
	int d1 = bst->depth(80);
	int d2 = bst->depth(30);
	int d3 = bst->depth(90);
	
	cout<<"\ndepths are \t80: "<<d1<<"\t30: "<<d2<<"\t90: "<<d3<<endl;
	
	BST<int>* bst2 = new BST<int>();
	bst2->insert(new int(10));
	bst2->insert(new int(5));
//	bst2->insert(new int(1));
	
	cout<<"avg depth is: "<<bst2->avgDepth()<<endl;


	for (int i = 0; i < size; i++) {
		if (bst->search(item[i]) != NULL) {
			cout << *item[i] << " Found" << endl;
		} else {
			cout << *item[i] << " NOT Found" << endl;
		}
	}

	for (int i = 0; i < size; i++) {
		cout << "Remove " << *item[i] <<  "    ";
		bst->remove(item[i]);

		cout << bst->size() << endl;

		bst->print(); cout << endl;

		if (bst->search(item[i]) != NULL) {
			cout << "ERROR: " << *item[i] << " still in the BST" << endl;
		}
	}
}

void testPetBST( ) {

	Pet** kennel;
	int size = 9;

	kennel = new Pet*[size];

	kennel[0] = new Pet("1111", "One",   10, 14.5);
	kennel[1] = new Pet("2222", "Two",   12, 25.5);
	kennel[2] = new Pet("3333", "Three", 20, 14.5);
	kennel[3] = new Pet("4444", "Four",  15, 15.5);
	kennel[4] = new Pet("5555", "Five",  12, 13.5);
	kennel[5] = new Pet("6666", "Six",   11, 10.5);
	kennel[6] = new Pet("7777", "Seven", 21, 22.5);
	kennel[7] = new Pet("8888", "Eight", 22, 21.5);
	kennel[8] = new Pet("9999", "Nine",  11, 23.5);

	BST<Pet> * bst = new BST<Pet>( );

	for (int i = 0; i < size; i++) {
		bst->insert(kennel[i]);
	}

	cout << "No of Elements: " << bst->size() << endl;
	bst->print(); cout << endl;

	bst->remove(new Pet("5555"));
	bst->remove(new Pet("3333"));
	bst->remove(new Pet("6666"));

	cout << "No of Elements: " << bst->size() << endl;
	bst->print(); cout << endl;
}

int main() {
	cout << "!!!Go MoonDeer!!" << endl;

	testIntBST();

	//testPetBST();

	return 0;
}
