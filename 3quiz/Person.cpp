/*
 * Person.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: twotani
 */

#include "Person.h"

Person::Person(string aName) {
	name = aName;
}

string Person::getName( ) {
	return name;
}

void  Person::setName(string aName) {
	name = aName;
}


