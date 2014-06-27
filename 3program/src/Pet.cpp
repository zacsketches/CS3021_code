/*
 * Pet.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: twotani
 */

#include "Pet.h"

Pet::Pet(string id) {
	setId(id);
	setName("No Name");
	setAge(0);
	setWgt(0.0);
}


Pet::Pet(string id, string name, int age, float wgt) {
	setId(id);
	setName(name);
	setAge(age);
	setWgt(wgt);
}


Pet::~Pet( ) {

}

string& Pet::getId()  {
	return id;
}

string& Pet::getName() {
	return name;
}

int Pet::getAge( ) {
	return age;
}

float Pet::getWgt()  {
	return wgt;
}


void Pet::setId(const string& id) {
	this->id = id;
}

void Pet::setName(const string& name) {
	this->name = name;
}

void Pet::setAge(int age) {
	this->age = age;
}

void Pet::setWgt(float wgt) {
	this->wgt = wgt;
}

bool Pet::operator<(Pet& pet) {
	return id < pet.getId();
}

bool Pet::operator==(Pet& pet) {
	return id == pet.getId();
}

ostream& operator<<(ostream& os, Pet& p) {

	os <<  "[" << p.getId()   << ", " << p.getName( ) << ", "
			   << p.getAge( ) << ", " << p.getWgt( )  << "]" << endl;

	return os;
}





