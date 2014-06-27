#include <map>
#include "Person.h"

using namespace std;

int main (int argc, char const *argv[])
{
    map<string, Person> msp;
    
    Person p1("111-22-3333");
    Person p2("111-33-4444");
    Person p3("111-44-5555");
    
    msp[p1.getSSN()] = p1;
    msp[p2.getSSN()] = p2;
    msp[p3.getSSN()] = p3;
    
    return 0;
}