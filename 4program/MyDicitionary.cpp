//============================================================================
// Name        : MyDicitionary.cpp
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Dictionary.h"
#include <iostream>
using namespace std;

void test1( ) {

	Dictionary<int,int> * intDict = new Dictionary<int,int>(101);

	intDict->add(new int(10), new int(4000));
	intDict->add(new int(20), new int(5000));
	intDict->add(new int(30), new int(4500));
	intDict->add(new int(40), new int(3400));
	intDict->add(new int(50), new int(2300));

	int * answer;

	answer = intDict->get(new int(10));
//cout << "main : " <<  *answer << endl;
	if (answer == NULL) {
		cout << "Error !!" << endl;
	} else {
		cout << "Got it: " << *answer << endl;
	}

	cout << "Test 1 Done" << endl;
}

void test2() {
	int bound = 1000;
	int range = 50000;

	int** keys = new int*[bound];
	int** values = new int*[bound];

	Dictionary<int,int> * dict = new Dictionary<int,int>(3 * bound);

	//create data and put them into a dictionary
	for (int i = 0; i < bound; i++) {
		keys[i] = new int(i+10);
		values[i] = new int(rand() % range);

		dict->add(keys[i], values[i]);
	}

	//search for random data values in keys and ensure they are found
	int errorCnt = 0;
	for (int i = 0; i < bound / 2; i++) {
		if (!dict->in(keys[rand() % bound])) {
			errorCnt++;
		}
	}

	cout << "Test 2 Error Cnt : " << errorCnt << endl;
}

int main() {
	cout << "!!!Go MoonDeer!!" << endl;

//	test1();

	test2();

	return 0;
}
