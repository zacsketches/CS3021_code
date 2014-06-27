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

int main() {
	cout << "!!!Go MoonDeer!!" << endl;

	Dictionary<int,int> * intDict = new Dictionary<int,int>(101);

	intDict->add(new int(10), new int(4000));
	intDict->add(new int(20), new int(4000));
	intDict->add(new int(30), new int(4000));
	intDict->add(new int(40), new int(4000));
	intDict->add(new int(50), new int(4000));

	cout << "!!!It didn't crashed??!!" << endl;

	return 0;
}
