/*
 * Set
 *
 *  Created on: May 27, 2014
 *      Author: twotani
 *
 *  Starter base code for the Set class
 */

#ifndef SET_
#define SET_

#include <vector>
#include <string>
using namespace std;

class Set {

public:

	//--------- Update Operations ----------------------------//
	 virtual void insert(string item) = 0;

	 virtual void remove(string item) = 0;

	//--------- Set Operations ----------------------------//
	 virtual Set* set_union(Set* s2) = 0; //set union

	 virtual Set* set_intersect(Set* s2) = 0; //set intersection

	 virtual Set* set_diff(Set* s2) = 0; //set difference


	//--------- Access Operations --------------------//
	 virtual vector<string> scan( ) = 0;

	//--------- Queries ----------------------------//
	 virtual int size( ) = 0;

	 virtual bool isEmpty( ) = 0;

	 virtual bool in(string item) = 0;
};



#endif /* SET_ */
