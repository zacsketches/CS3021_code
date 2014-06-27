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
	
	//*********************************************************************************
	//                          Test prev and next on empty list		
	//*********************************************************************************
	cout<<"Testing prev and next on empty list\n";
	int* c = ol->prev();
	if(c == NULL) cout<<"\tpreve returns NULL on empty list\n";
	c = ol->next();
	if(c == NULL) cout<<"\tnext returns NULL on empty list\n";
	
	//*******************************************************************
	//*                         Testing Insert
	//*******************************************************************
	cout<<"Testing insert\n";
	cout << "\tEmpty ol has "<<ol->size() << " integers" <<endl;
	
	ol->insert(new int(45)); cout<<"\tinsert";
	ol->insert(new int(15)); cout<<"\tinsert";
	ol->insert(new int(99)); cout<<"\tinsert";
	
	cout << "\n\tol now has "<<ol->size() << " integers"<<endl;
	
	//*******************************************************************
	//*                         Testing Search
	//*******************************************************************
	int* ans;
	cout<<"testing search:\n";
	ans = ol->search(new int(45));
	if(ans != NULL){
		cout<<"\tOkay found "<< *ans <<endl;
	} else {
		cout<<"\tError: element not found"<<endl;
	}
	
	ans = ol->search(new int(100));
	if(ans != NULL){
		cout<<"\tOkay found "<< *ans <<endl;
	} else {
		cout<<"\tError: element not found"<<endl;
	}
	
	//*******************************************************************
	//*                         Testing Scan
	//*******************************************************************
	vector<int*> scanlist = ol->scan();
	cout<<"testing scan:\n\t";
	for(size_t i = 0; i < scanlist.size(); ++i)
	{
		cout<< *scanlist[i]<< " ";
	}
	cout<<endl;
	
	//*******************************************************************
	//*                         Testing Remove
	//*******************************************************************
	cout<<"testing remove:\n";
	ol->remove(new int(99));
	cout<<"\telements in the ordered list: "<<ol->size()<<endl;
	scanlist.clear();
	scanlist = ol->scan();
	cout<<'\t';
	for(int i = 0; i < scanlist.size(); ++i){
		int* val = scanlist[i];
		cout<< *val<<" ";
	}
	cout<<endl;
	
	//*******************************************************************
	//*                         Testing First
	//*******************************************************************
	cout<<"testing first:\n";
	ol->insert(new int(90));
	ol->insert(new int(60));
	ol->insert(new int(70));
	ol->insert(new int(50));
	ol->insert(new int(40));
	ol->insert(new int(6));
	ol->insert(new int(2));
	ol->insert(new int(1));
	ol->insert(new int(7));
	ol->insert(new int(8));
	ol->insert(new int(9));
	ol->insert(new int(10));
	ol->insert(new int(11));
	ol->insert(new int(4));
	
	ans = ol->first();
	print_list(ol);
	cout<<"\tfirst is: "<<*ans<<endl;

	//*******************************************************************
	//*                         Testing Last
	//*******************************************************************
	cout<<"testing last:\n";
	
	ans = ol->last();
	print_list(ol);
	cout<<"\tlast is: "<<*ans<<endl;
	
	//*******************************************************************
	//*                         Testing Current
	//*******************************************************************
	/*
		TODO test for current is NULL after remove
	*/
	
	cout<<"testing current:\n";
	print_list(ol);
	cout<<"\tcall last\n";
	ol->last();
	c = ol->get_current();
	cout<<"\tcurrent is: "<<*c<<endl;
	cout<<"\tcall first\n";
	ol->first();
	c = ol->get_current();
	cout<<"\tcurrent is: "<<*c<<endl;
	
	//*******************************************************************
	//*                         Testing Next
	//*******************************************************************
	/*
		TODO test the return value of next...not just current
	*/
	cout<<"testing next:\n";
	print_list(ol);
	
	cout<<"\tinsert called\n";
	ol->insert(new int(44));
	c = ol->get_current();
	if(c == NULL) cout<<"\tcurrent is NULL after insert\n";
	
	for(size_t i = 0; i < ol->size()+3; ++i)
	{
		cout<<"\tcall next\n";
		ol->next();
		c = ol->get_current();
		cout<<"\tcurrent is: "<<*c<<endl;
	}
	
	//*******************************************************************
	//*                         Testing Prev
	//*******************************************************************
	/*
		TODO test the return value of prev...not just current
	*/
	cout<<"testing prev:\n";
	print_list(ol);
	
	cout<<"\tinsert called\n";
	ol->insert(new int(43));
	c = ol->get_current();
	if(c == NULL) cout<<"\tcurrent is NULL after insert\n";
	
	for(size_t i = 0; i < ol->size()+3; ++i)
	{
		cout<<"\tcall prev\n";
		ol->prev();
		c = ol->get_current();
		cout<<"\tcurrent is: "<<*c<<endl;
	}
	
	//*******************************************************************
	//*                         Testing At
	//*******************************************************************
	cout<<"testing at:\n";
	print_list(ol);
	
	cout<<"\tcalling a negative index\n";
	c = ol->at(-1);
	if(c != NULL) cout<<"\tat didn't return NULL\n";
	cout<<"\tcalling an index larger than size\n";
	c = ol->at(1000);
	if(c != NULL) cout<<"\tat didn't return NULL\n";
	
	c = ol->at(0);
	cout<<"\tindex 0 is: "<<*c<<endl;
	c = ol->at(3);
	cout<<"\tindex 3 is: "<<*c<<endl;
	c = ol->at(ol->size()-1);
	cout<<"\tindex at the end is: "<<*c<<endl;
	
	
}