/*
 * VectorSet.h
 *
 *  Created on: Jun 4, 2014
 *      Author: twotani
 */

#ifndef VECTORSET_H_
#define VECTORSET_H_

#include <vector>
#include "Set.h"

class VectorSet: public Set {
public:
	VectorSet();

	~VectorSet();

	//--------- Update Operations ----------------------------//
	 void insert(string item);

	 void remove(string item);

	//--------- Set Operations ----------------------------//
	 Set* set_union(Set* s2); //set union

	 Set* set_intersect(Set* s2); //set intersection

	 Set* set_diff(Set* s2); //set difference


	//--------- Access Operations --------------------//
	 vector<string> scan( );

	//--------- Queries ----------------------------//
	 int size( );

	 bool isEmpty( );

	 bool in(string item);

private:

	 vector<string> element;

};

#endif /* VECTORSET_H_ */
