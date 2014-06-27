/*
 * VectorSet.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: twotani
 */


#include "VectorSet.h"

VectorSet::VectorSet() {

}


VectorSet::~VectorSet() {

}

void VectorSet::remove(string item) {

}

Set* VectorSet::set_union(Set* s2) {

	VectorSet* result = new VectorSet();
	vector<string> element2;
	VectorSet* local = static_cast<VectorSet*>(result);

	if (size() > s2->size()) {
		local->element = scan();
		element2 = s2->scan();

	} else {
		local->element = s2->scan();
		element2 = scan();
	}

	for (string val : element2) {
		result->insert(val);
	}

	return result;
}


Set* VectorSet::set_intersect(Set* s2) {
	VectorSet *result = new VectorSet();

	return result;
}

Set* VectorSet::set_diff(Set* s2) {
	VectorSet *result = new VectorSet();

	return result;
}


vector<string> VectorSet::scan() {
	//vector<string> result;
	return element;
	//return result;
}

int VectorSet::size() {

	return element.size();
}

bool VectorSet::isEmpty() {

	return element.empty();
}

bool VectorSet::in(string item) {
	bool result = false;

	for (string val : element) {
		if (val == item) return true;
	}

	return result;
}

void VectorSet::insert(string item) {

	if (!in(item)) {
		element.push_back(item);
	}
}
