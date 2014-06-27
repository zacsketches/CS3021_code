/*
 * hashset.h
 *
 * By Zac Staples
 * CS3021
 * Program Assignment 4
 * 23 June 2014
 *
 */

#ifndef HASHSET_H
#define HASHSET_H 

#include <string>
#include <vector>
#include "Set.h"

//*******************************************************************
//*                         HASHTABLE
//* Zac Staples, Jun 2014
//* My implementation of an unordered map to support Program 4
//* on mathematical sets
//*******************************************************************

class HashTable {
    
public:

    HashTable(const int n)
        :table_length(n), table(new HashNode*[n]) {}
        
    ~HashTable(); 
    
     //--------- Update Operations ----------------------------//
    void insert(std::string item);
    void remove(std::string item);

    //--------- Access Operations ----------------------------//
    std::vector<std::string> at(int index);
    std::vector<std::string> scan( );
    
    //----------Support Operations ------------------------------//
    int hash(std::string item);   //show the hash returned by the H() function
    
    //----------------- Queries ----------------------------//
    int size( );
    bool isEmpty( );
    bool in(std::string item);
    
private:

    struct HashNode {
        std::string* data;
        HashNode* next;
        
        explicit HashNode() {
            data = new std::string("");
            next = NULL;
        }

        explicit HashNode(std::string item) {
            data = new std::string(item);
            next = NULL;
        }

        ~HashNode() {
            delete data;
        }
        
        bool operator==(const std::string item) {return *data == item;}
    };

    const int table_length;
    HashNode** table;
    
    int H(std::string item);
};

//*******************************************************************
//*                         Implementation
//*******************************************************************
inline HashTable::~HashTable(){
    //iterate through each table bin deleting node chains
    for(int i = 0; i < table_length; ++i) {
        HashNode* tmp = table[i];
        HashNode* fwd_ptr = NULL;
        if(tmp != NULL){
            while(tmp != NULL){
                fwd_ptr = tmp->next;
                delete tmp;
                tmp = fwd_ptr;
            }
        }
    }
    //delete the table
    delete table;
}

inline void HashTable::insert(std::string item) {
    if (! this->in(item) ){
        int loc = H(item);
        HashNode* elem = new HashNode(item);
        
        HashNode* temp = table[loc];
        table[loc] = elem;
        elem->next = temp;
    }
}

inline void HashTable::remove(std::string item) {
    if (this->in(item)){
        int loc = H(item);
        HashNode* temp = table[loc];
    
        HashNode* back_ptr = NULL;
    
        HashNode* fwd_ptr = temp->next;
    
        while(temp != NULL) {
            if ( *(temp->data) == item ) {
                if(back_ptr==NULL){  //removed is the first in a chain
                    table[loc] = fwd_ptr;
                    delete temp;
                    break;
                } else 
                if(back_ptr !=NULL) {         //removed is in the midle of a chain
                    back_ptr->next = fwd_ptr;
                    delete temp;
                    break;
                }
                
            }   //close if (temp == item)
            back_ptr = temp;
            temp = temp->next;
            fwd_ptr = temp->next;
        }  //close while
    }    
}

inline std::vector<std::string> HashTable::at(int index) {
    std::vector<std::string> result;
    HashNode* tmp = table[index];
    while(tmp != NULL){
        result.push_back(*(tmp->data));
        tmp = tmp->next;
    }
    return result;
}

inline std::vector<std::string> HashTable::scan() {
    std::vector<std::string> result;
    
    // iterate through each table bin pushing back any non-null value 
    for(int i = 0; i < table_length; ++i) {
        HashNode* tmp = table[i];
        if(tmp != NULL){
            while(tmp!=NULL){
                result.push_back( *(tmp->data) );
                tmp = tmp->next;
            }
        }
    }
    
    return result;
}

inline int HashTable::hash(std::string item) {
    return H(item);
}

inline int HashTable::size() {
    std::vector<std::string> tmp = scan();
    return tmp.size();
}

inline bool HashTable::isEmpty() {
    std::vector<std::string> tmp = scan();
    return (tmp.size() == 0 ) ? true : false ;
}

inline bool HashTable::in(std::string item) {
    bool res = false;
    
    int loc = H(item);
    
    HashNode* tmp = table[loc];
    
    while(tmp != NULL){
        if( *(tmp->data) == item) res = true;
        tmp = tmp->next;
    }
    
    return res;
}

inline int HashTable::H(std::string item) {
    // Simple hash function designed for a string type that provides a pretty
    // good distribution across all bins in the table
    const char* str = item.c_str();
    
    int sum = 0;
    for(int i = 0; i < strlen(str); ++i) {
        sum += str[i];
    }
    
    return sum % table_length;
}

//*******************************************************************
//*                         HASHSET
//*******************************************************************

class HashSet: public Set {
public:
    HashSet(); 
    
    ~HashSet() { elem.~HashTable(); }
    
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
    HashTable elem; 	

};

#endif /* HASHSET_H */
