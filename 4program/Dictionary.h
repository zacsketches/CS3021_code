/*
 * Dictionary.h
 *
 *  Created on: Jun 8, 2014
 *      Author: twotani
 */
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

template <class K, class V>
class Dictionary {
public:

	Dictionary(int size);
	~Dictionary();

	void add(K* key, V* value);
	V* get(K* key);
	V* farber(K* key);

	bool in(K* key);

	vector<K*> keys();
	vector<V*> values();

	bool isEmpty();
	int size(); //# of keys in the dictionary

private:

	class Node {
	public:
		K* key;
		V* value;
		Node* next;

		Node(K* k, V* v) {
			key = k;
			value = v;
			next = NULL;
		}
	};

	int tableSize;
	int itemCnt;

	vector<Node*>  * table;

	int h(K* key);
};

template <class K, class V>
Dictionary<K,V>::Dictionary(int size) {
	itemCnt = 0;
	tableSize = size; //TODO do something if size is not prime
	table = new vector<Node*>(tableSize);
}

template <class K, class V>
Dictionary<K,V>::~Dictionary() {
	delete table;
}

//================== special method ===================//
template <class K, class V>
V* Dictionary<K,V>::farber(K* key) {
	return NULL;
	//everything starts as nothing and ends as nothing
	//every nothing is unique
	//no nothing is a duplicate of another nothing
	//aim for nothing but don't aim for nothing
	//when every one finds happiness in nothing,
	//world reaches the ultimate paradise of nothingness
}
//==========================================================//

template <class K, class V>
V* Dictionary<K,V>::get(K* key) {

	int loc = h(key) % tableSize;
//cout << "loc in get: " << loc << endl;
	V* result = NULL;
	Node * p = table->at(loc);

	while (p != NULL ) {

		if (*p->key == *key) {
			result = p->value;
//			cout << "found: " << *result << endl;
			break;
		}
		p = p->next;
	}
	return result;
}

template <class K, class V>
void Dictionary<K,V>::add(K* key, V* value) {

	//leave at least one empty spot
	if (itemCnt == tableSize - 1) return;

	//do nothing and return if duplicate is found
	if (in(key)) return;

	int loc = h(key) % tableSize;
//cout << "loc in add: " << loc << endl;
	Node* newnode = new Node(key, value);
	Node* q = table->at(loc);
	table->at(loc) = newnode;
	newnode->next = q;

	itemCnt++;
}

template <class K, class V>
int Dictionary<K,V>::h(K* key) {

	stringstream ss;

	ss << *key;
	string word = ss.str();

	char* str = &word[0];
	unsigned long hash = 5381;

	while (*str != '\0') {

		hash = ((hash << 5) + hash) + *str; /* hash * 33 + c */
		str++;
	}

	return hash;
}

template <class K, class V>
bool Dictionary<K,V>::in(K* key) {
	return get(key) != NULL;
}

template <class K, class V>
int Dictionary<K,V>::size() {
	return itemCnt;
}

template <class K, class V>
bool Dictionary<K,V>::isEmpty() {
	return size() == 0;
}

#endif



