/*
 * Dictionary.h
 *
 *  Created on: Jun 8, 2014
 *      Author: twotani
 */
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

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

	vector<Node*>* table;

	int h(K* key);
};

template <class K, class V>
Dictionary<K,V>::Dictionary(int size) {
	tableSize = size; //do something if size is not prime
	table = new vector<Node*>(tableSize);
}

template <class K, class V>
Dictionary<K,V>::~Dictionary() {
	delete table;
}

template <class K, class V>
void Dictionary<K,V>::add(K* key, V* value) {

	int loc = h(key) % tableSize;

	Node* newnode = new Node(key, value);
	Node* q = table->at(loc);
	table->at(loc) = newnode;
	newnode->next = q;
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

#endif



