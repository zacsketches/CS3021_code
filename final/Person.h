#include <string>
#include <iostream>

#ifndef PERSON_H
#define PERSON_H value

using namespace std;

class Person {
    
private: 
    string ssn;
    string name;
    
public:
    Person(string social)
        :ssn(social) {}
        
    Person() {};
    string getName() { return name;}
    string getSSN() { return ssn; }
    
    void setName(string n) { name = n; }
    void setSSN(string social) {ssn = social; }
    
    virtual string computePay() = 0;       //pure virtual
};

#endif

