/*
 * hashset.cpp
 *
 * By Zac Staples
 * CS3021
 * Program Assignment 4
 * 23 June 2014
 *
 */
 
#include "hashset.h"

HashSet::HashSet() : elem(HashTable(100)) {}

void HashSet::insert(string item) {    
    if (!in(item)) {
        elem.insert( item );
    }
}

void HashSet::remove(string item){
    elem.remove(item);
}

Set* HashSet::set_union(Set* s2){
    //make a copy of s2 
    Set* result = new HashSet;
    vector<string> temp = s2->scan();
    for(int i = 0; i < temp.size(); ++i) {
        result->insert(temp[i]);
    }
            
    //insert the elements of this set that are not in the result yet
    vector<string> s1 = scan();
    for(int i = 0; i < s1.size(); ++i) {
        if(! s2->in(s1[1]) ) result->insert(s1[i]);
    }     
    
    return result;
}

Set* HashSet::set_intersect(Set* s2) {
    Set* result = new HashSet;
    
    vector<string> s1 = scan();
    
    for(int i = 0; i < s1.size(); ++i) {
        if( s2->in(s1[i]) ) result->insert(s1[i]);
    }
    
    return result;
}


Set* HashSet::set_diff(Set* s2) {
 	//union minus inersection is diff
	Set* result = set_union(s2);
	Set* hs_intersect = set_intersect(s2);
	vector<string> vs = hs_intersect->scan();
		
	for(int i = 0; i < vs.size(); ++i) {
		result->remove(vs[i]);
	}
	
    delete hs_intersect;
    
	return result;
}

vector<string> HashSet::scan() {
    return elem.scan();
}

int HashSet::size() {
	if (this == NULL) return 0;
	
    return elem.size();
}

bool HashSet::isEmpty() {
    return ( size() == 0 )? true : false;
}

bool HashSet::in(string item) {
    return (elem.in(item)) ? true : false;
}
