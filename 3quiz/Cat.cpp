/*
 * Cat.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: twotani
 */
#include "Cat.h"

Cat::Cat(string aName) {
	name = aName;
	owner = NULL;
}

Cat::~Cat() {
	delete owner;
}

string Cat::getName( ) {
	return name;
}

void  Cat::setName(string aName) {
	name = aName;
}

Person* Cat::getOwner( ) {
	return owner;
}

void  Cat::setOwner(Person* anOwner){
	owner = anOwner;
}

string Cat::getOwnerName( ) { //COMPLETE THIS FUNCTION

	string result;

	/* If the cat has no owner, i.e., owner data member
	 * is not pointing to any Person object, return the string
	 * "No Owner".  If the cat has an owner, then return the name
	 * of the owner.
	 */

	return result;
}

