#include "cat.h"	
#include "person.h"
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char const *argv[])
{
	Person* p1 = new Person("TomTom");
	
	Cat* c1 = new Cat("BonBon");
	c1->setOwner(p1);
	
	Cat* c2 = new Cat("ChaCha");
	c2->setOwner(p1);
	
/*
	Cat* familyPet[5];
	familyPet[0] = c1;
	familyPet[1] = c2;
	
	for(size_t i = 0; i < 2; ++i)
	{
		Cat* tmp = familyPet[i];
		Person* owner = tmp->getOwner();
		cout<<"The cat "<<tmp->getName()<<" is owned by "
			<<owner->getName()<<endl;
	}
*/
	vector<Cat*> vc;
	vc.push_back(c1);
	vc.push_back(c2);
	
	for(size_t i = 0; i < vc.size(); ++i)
	{
		Cat* tmp = vc[i];
		Person* owner = tmp->getOwner();
		cout<<"The cat "<<tmp->getName()<<" is owned by "
			<<owner->getName()<<endl;
	}
	
	cout<<"\nNew problem on a person array \n";
	
	Person* people[10];
	Person* p = NULL;
	string name;
	
	for(size_t i = 0; i < 10; ++i)
	{
		cout<<"Enter name: ";
		cin >> name;
		
		p = new Person(name);
		
		people[i] = p;
		
	}
	cout<<"The people are: \n";
	for(size_t i = 0; i < 10; ++i)
	{
		cout<<"\t"<<people[i]->getName()<<endl;
	}
	
	return 0;
}