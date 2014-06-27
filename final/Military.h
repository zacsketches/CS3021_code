#include "Person.h"
#include <string>
#include <iostream>

#ifndef MILITARY
#define MILITARY value

class Military : public Person {
// public:
//     string computePay() {
//         cout<<"Pay from Military\n";
//     }
};

#endif

class Officer : public Military {
public:
    string computePay() {
        cout<<"pay from Officer\n";
    }
};

class Enlisted : public Military {
public:
    string computePay() {
        cout<<"pay from Enlisted\n";  
    }
};

