#include "Person.h"
#include "Military.h"

using namespace std;

int main (int argc, char const *argv[])
{
    Military* o = new Officer();
    Military* e = new Enlisted();
    
    e->computePay();

    cout<<"in the middle\n";

    o->computePay();
    
    
    return 0;
}