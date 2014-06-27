//============================================================================
// Name        : Prog4.cpp
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Set.h"
#include "VectorSet.h"
#include <iostream>
using namespace std;

int main() {

	Set * vs = new VectorSet();

	cout << "Size of empty set: " << vs->size() << endl;
	cout << "Empty set is empty: " << vs->isEmpty() << endl;

	vs->insert("One");
	vs->insert("Two");
	vs->insert("One");
	vs->insert("One");
	vs->insert("Two");
	vs->insert("One");

	cout << "Size of set: " << vs->size() << endl;
	cout << "Empty set?: " << vs->isEmpty() << endl;

	Set * vs2 = new VectorSet();

	vs2->insert("One");
	vs2->insert("Two");
	vs2->insert("Three");
	vs2->insert("Four");

	Set * unionset;

	unionset = vs->set_union(vs2);

	cout << "size of vs set: " << vs->size() << endl;
	cout << "size of vs2 set: " << vs2->size() << endl;
	cout << "size of union set: " << unionset->size() << endl;

	for (string val : unionset->scan()) {
		cout << val << endl;
	}

	return 0;
}

