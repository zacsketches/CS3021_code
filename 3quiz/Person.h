/*
 * Person.h
 *
 *  Created on: Apr 29, 2014
 *      Author: twotani
 */
#ifndef PERSON_H_
#define PERSON_H_

#include <string>
using namespace std;

class Person {

private:
	string name;

public:
	Person(string name);

	string getName( );

	void   setName(string name);
};

#endif

