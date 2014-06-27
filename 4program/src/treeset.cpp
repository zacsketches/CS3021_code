/*
 * treeset.cpp
 *
 * By Zac Staples
 * CS3021
 * Program asignment 4
 * 23 June 2014
 */

#include "treeset.h"

TreeSet::TreeSet() {}

void TreeSet::insert(string item) {    
    if (!in(item)) {
		string* tmp = new string(item);
        elem.insert( tmp );
    }
}

void TreeSet::remove(string item){
    if(in(item)) elem.remove(new string(item));
}

Set* TreeSet::set_union(Set* s2){
    //make a copy of s2 
    Set* result = new TreeSet;
    vector<string> temp = s2->scan();
    for(int i = 0; i < temp.size(); ++i) {
        result->insert(temp[i]);
    }
            
    //insert the elements of this set that are not in the result yet
    vector<string> s1 = scan();
    for(int i = 0; i < s1.size(); ++i) {
        if(! s2->in(s1[i]) ) result->insert(s1[i]);
    }     
    
    return result;
}

Set* TreeSet::set_intersect(Set* s2) {
    Set* result = new TreeSet;
    
    vector<string> s1 = scan();
    
    for(int i = 0; i < s1.size(); ++i) {
        if( s2->in(s1[i]) )result->insert(s1[i]);
    }
    
    return result;
}


Set* TreeSet::set_diff(Set* s2) {
	//union minus inersection is diff
	Set* result = set_union(s2);
	Set* ts_intersect = set_intersect(s2);
	vector<string> vs = ts_intersect->scan();
		
	for(int i = 0; i < vs.size(); ++i) {
		result->remove(vs[i]);
	}
	
    delete ts_intersect;
    
	return result;
}

vector<string> TreeSet::scan() {
    vector<string*> temp = elem.scan();
    vector<string> result;
    for(int i = 0; i < temp.size(); ++i) {
        result.push_back( *temp[i] );
    }
    return result;
}

int TreeSet::size() {
	if (this == NULL) return 0;
	
    return elem.size();
}

bool TreeSet::isEmpty() {
    return ( size() == 0 )? true : false;
}

bool TreeSet::in(string item) {
    string* sp = elem.search(new string(item));
    
    return (sp == NULL) ? false : true;
}