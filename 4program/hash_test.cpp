/*
 * hash_test.cpp
 *
 */

#include "HashTable.h"
#include <vector>
#include <iostream>

using namespace std;

void do_nothing_table() {
    HashTable table(10);
}

int main (int argc, char const *argv[])
{
    int table_len = 100;
    cout<<"Testing the hash functions for a table of length "<<table_len<<endl;
    
    HashTable table1(table_len);
    
    int h1 = table1.hash("One");            //hash 90
    cout<<"\thash of 'One' is: "<<h1<<endl;
    int h2 = table1.hash("Two");
    cout<<"\thash of 'Two' is: "<<h2<<endl;
    int h3 = table1.hash("Three");
    cout<<"\thash of 'Three' is: "<<h3<<endl;
    int h4 = table1.hash("Z");              //hash 90
    cout<<"\thash of 'Z' is: "<<h4<<endl;
    int h5 = table1.hash("--");             //hash 90
    cout<<"\thash of '--' is: "<<h5<<endl;

    h5 = table1.hash("Six");             
    cout<<"\thash of 'Six' is: "<<h5<<endl;
    h5 = table1.hash("Four");             
    cout<<"\thash of 'Four' is: "<<h5<<endl;
    h5 = table1.hash("<,");             
    cout<<"\thash of '<,' is: "<<h5<<endl;
    h5 = table1.hash("08");             
    cout<<"\thash of '08' is: "<<h5<<endl;
    
    //*******************************************************************
    //*                         insert
    //*******************************************************************
    table1.insert("One");
    table1.insert("Z");
    table1.insert("One");
    table1.insert("Three");
    table1.insert("--");
    
    //*******************************************************************
    //*                         at
    //*******************************************************************
    vector<string> loc1 = table1.at(90);
    cout<<"Testing the at(int) function:\n";
    cout<<"\tthe strings at 90 are: \n";    //should print 'Z' and 'One'
    for(int i = 0; i < loc1.size(); ++i) {
        cout<<"\t\telement "<<i<<" is: "<<loc1[i]<<endl;
    }
    
    //*******************************************************************
    //*                         in
    //*******************************************************************
    cout<<"Testing the in() function: \n";
    cout<<"\t'One' is in table1: "<<table1.in("One")<<endl;
    cout<<"\t'Z' is in table1: "<<table1.in("Z")<<endl;
    cout<<"\t'Three' is in table1: "<<table1.in("Three")<<endl;
    cout<<"\t'Four' is in table1: "<<table1.in("Four")<<endl;

    //*******************************************************************
    //*                         remove
    //*******************************************************************
    cout<<"Tesing  remove('--'): \n";
    table1.remove("--");
    loc1 = table1.at(90);
    cout<<"\tthe strings at 90 are: \n";    //should print 'just Z'
    for(int i = 0; i < loc1.size(); ++i) {
        cout<<"\t\telement "<<i<<" is: "<<loc1[i]<<endl;
    }
    
    cout<<"Tesing  remove('One'): \n";
    table1.remove("One");
    loc1 = table1.at(90);
    cout<<"\tthe strings at 90 are: \n";    //should print 'just Z'
    for(int i = 0; i < loc1.size(); ++i) {
        cout<<"\t\telement "<<i<<" is: "<<loc1[i]<<endl;
    }

    cout<<"Tesing  remove('Z'): \n";
    table1.remove("Z");
    loc1 = table1.at(90);
    cout<<"\tthe strings at 90 are: \n";    //should print 'just Z'
    for(int i = 0; i < loc1.size(); ++i) {
        cout<<"\t\telement "<<i<<" is: "<<loc1[i]<<endl;
    }
    
    //*******************************************************************
    //*                         scan
    //*******************************************************************
    cout<<"Testing scan() after inserting 'Four', 'Five', and 'Six':\n";
    table1.insert("Four");
    table1.insert("Five");
    table1.insert("Six");
    vector<string> scan1 = table1.scan();
    cout<<"\tthe scan contains:\n";
    for(int i = 0; i < scan1.size(); ++i) {
        cout<<"\t\tthe element at "<<i<<" is: "<<scan1[i]<<endl;
    }
    
    //*******************************************************************
    //*                         size
    //*******************************************************************
    cout<<"Testing size():\n";
    cout<<"\tthe table size is: "<<table1.size()<<endl;
    table1.remove("Five");
    cout<<"\tafter removing 'Five' the table size is: "<<table1.size()<<endl;
    
    //*******************************************************************
    //*                         isEmpty
    //*******************************************************************
    cout<<"Testing isEmpty(): \n";
    cout<<"\ttable1 is empty: "<<table1.isEmpty()<<endl;
    HashTable table2(100);
    cout<<"\ttable2, newly constructed table, is empty: "<<table2.isEmpty()<<endl;
    
    //*******************************************************************
    //*                         destructor
    //*******************************************************************
    cout<<"Adding '<,' to table1 so it will have a linked destruction req't: \n";
    table1.insert("<,");    //hash 4
    table1.insert("08");    //hash 4
    
    return 0;
} 
 