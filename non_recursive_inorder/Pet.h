/*
 * Pet.h
 *
 *  Created on: Aug 10, 2011
 *      Author: twotani
 */

#ifndef PET_H_
#define PET_H_

#include <iostream>
#include <string>
using namespace std;

class Pet {

private:
	string id; //four-digit id 0000 ~ 9999
	string name;
	int    age;
	float  wgt;

public:

	Pet(string id);
	Pet(string id, string name, int agt, float wgt);

	~Pet();

	string& getId( );
	string& getName( );
	int     getAge();
	float   getWgt( );

	void setId(const string& id);
	void setName(const string& name);
	void setAge(int age);
	void setWgt(float wgt);

	bool operator<(Pet& pet);
	bool operator==(Pet& pet);

	friend ostream& operator<<(ostream& os, Pet& p);
};

#endif /* PET_H_ */
