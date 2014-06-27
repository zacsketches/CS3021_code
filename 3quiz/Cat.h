//============================================================================
// Name        : Cat.cpp
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : The full Cat class (both header and implementation)
//
//============================================================================

#ifndef CAT_H_
#define CAT_H_

#include <string>
#include "Person.h"
using namespace std;

class Cat {

private:
	string name;
	Person* owner;

public:

	Cat(string aName);

	~Cat();

	string getName( );

	void   setName(string aName);

	Person* getOwner( );

	void   setOwner(Person* anOwner);

	string getOwnerName( );
};

#endif
