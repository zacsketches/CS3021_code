//============================================================================
// Name        : prog3tester.cpp
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : Hello World in C++, Ansi-style
//============================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
/*
 * This is sample main program to test the OrderedList implementation.
 *
 * You cannot run this program as is until the implementation of the OrderedList
 * class is complete. But you can review the code here and use selective portion
 * to test a particular function you are developing.
 *
 * Understanding the coding style shown in this sample main program is part of the
 * assignment.
 *
 */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#include "OrderedList.h"
#include "Pet.h"
#include <iostream>
using namespace std;

void testInt() {

	cout << endl << "TESTING Ordered List with Pet objects" << endl;

	int val[] = {80, 40, 30, 90, 10, 50, 35, 70, 85, 95, 100};
	int size = 11;

	int** item; //an array of pointers to int

	item = new int*[size];

	OrderedList<int> * olist = new OrderedList<int>();

	for (int i = 0; i < size; i++) {
		item[i] = new int(val[i]); //olist accepts T* so we're adding
		olist->insert(item[i]);   //pointers to ints
	}

	cout << "AFTER INSERT Count: " << olist->size() << endl;
	for (int* p : olist->scan()) { //olist->scan() returns a vector of pointers
		cout << *p << endl;        //to ints
	}

	int* p;

	cout << "Scan forward" << endl;

	p = olist->first();  //go through the list in ascending order
	cout << *p << endl;  //by calling first and then next successively
                         //until NULL is returned
	while (true) {
		p = olist->next();
		if (p == NULL) break;
		cout << *p << endl;
	}

	cout << "Scan backward" << endl;

	p = olist->last();    //now scan in descending order
	cout << *p << endl;

	while (true) {
		p = olist->prev();
		if (p == NULL) break;
		cout << *p << endl;
	}

	//confirm the at operation returns the values correctly
	//we are going position 0, 1, 2, ... so we will get the values
	//in ascending order
	cout << endl << endl << "Check the AT operation" << endl;
	for (int i = 0; i < size; i++) {
		int* p = olist->at(i);
		cout << *p << endl;
	}

	//Now remove 70, 85, 90, 40 to test all 3 delete cases
	int* r[] = {new int(70), new int(85), new int(90), new int(40)};

	for (int i = 0; i < 4; i++) {
		olist->remove(r[i]);
	}

	cout << "SCAN after removal of 70, 85, 90, 40: " << olist->size() << endl;
	for (int* p : olist->scan()) {
		cout << *p << endl;
	}

}

void testPet() {

	cout << endl << endl << "TESTING Ordered List with Pet objects" << endl;

	Pet** kennel; //an array of pointers to Pet objects
	int size = 9;

	kennel = new Pet*[size];

	kennel[0] = new Pet("5555", "Five",  12, 13.5);
	kennel[1] = new Pet("2222", "Two",   12, 25.5);
	kennel[2] = new Pet("8888", "Eight", 22, 21.5);
	kennel[3] = new Pet("9999", "Nine",  11, 23.5);
	kennel[4] = new Pet("1111", "One",   10, 14.5);
	kennel[5] = new Pet("6666", "Six",   11, 10.5);
	kennel[6] = new Pet("7777", "Seven", 21, 22.5);
	kennel[7] = new Pet("3333", "Three", 20, 14.5);
	kennel[8] = new Pet("4444", "Four",  15, 15.5);

	//Here we are creating an ordered list of Pet objects

	OrderedList<Pet> * olist = new OrderedList<Pet>( );

	for (int i = 0; i < size; i++) {
		olist->insert(kennel[i]);  //we pass a pointer to Pet
	}

	cout << "No of Elements: " << olist->size() << endl;

	for (Pet* p : olist->scan()) { //go through the vector of pointers to Pet
		cout << *p;
	}

	cout << endl;
	cout << "Node at 4 " << *olist->at(4);  //select Pet in the ordered list
	cout << "Node at 8 " << *olist->at(8);  //by its position
	cout << "Node at 1 " << *olist->at(1);
	cout << "Node at 0 " << *olist->at(0);
	cout << endl;

	Pet* pet;

	cout << "Scan forward" << endl;

	pet = olist->first();
	cout << *pet;

	while (true) {
		pet = olist->next();
		if (pet == NULL) break;
		cout << *pet;
	}

	cout << endl;

	cout << "Scan backward" << endl;

	pet = olist->last();
	cout << *pet;

	while (true) {
		pet = olist->prev();
		if (pet == NULL) break;
		cout << *pet;
	}

	pet = new Pet("1111"); //Test remove of 3 Pet objects
	olist->remove(pet);

	pet->setId("3333");
	olist->remove(pet);

	pet->setId("5555");
	olist->remove(pet);

	cout << endl << "After remove 1111, 3333, 5555 : " << olist->size() << endl;
	for (Pet* p : olist->scan()) {
		cout << *p;
	}
}


int main() {
	cout << "!!!Go MoonDeer!!" << endl;

	testInt();

	testPet();

	return 0;
}
