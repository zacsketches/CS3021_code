//devmain.cpp

#include "OrderedList.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T>
void print_list ( OrderedList<T>* ol) {	
	vector<T*> scanlist;
	
	scanlist = ol->scan();
	cout<<'\t';
	for(int i = 0; i < scanlist.size(); ++i){
		int* val = scanlist[i];
		cout<< *val<<" ";
	}
	cout<<endl;
}

int main (int argc, char const *argv[])
{
	OrderedList<int>* ol = new OrderedList<int>();
		
	
	//*******************************************************************
	//*                         Testing At
	//*******************************************************************
	cout<<"testing at:\n";
	ol->insert(new int(45)); cout<<"\tinsert";
	ol->insert(new int(35)); cout<<"\tinsert";
	ol->insert(new int(25)); cout<<"\tinsert";
	ol->insert(new int(60)); cout<<"\tinsert";
	cout<<endl;

	print_list(ol);

	int* c = ol->at(0);
	cout<<"\tindex 0 is: "<<*c<<endl;
	c = ol->at(2);
	cout<<"\tindex 2 is: "<<*c<<endl;
	c = ol->at(ol->size()-1);
	cout<<"\tindex at the end is: "<<*c<<endl;
	
	cout <<"Scan in reverse:\n";
	vector<int*> v = ol->scan_rev();
	for (int i = 0; i < v.size(); ++i) { //olist->scan() returns a vector of pointers
		int* p = v[i];
		cout << *p << endl;        //to ints
	}
	cout<<endl;
	
	
}