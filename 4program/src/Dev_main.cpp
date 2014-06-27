#include "Set.h"
#include "treeset.h"
#include "hashset.h"
#include <iostream>

using namespace std;

int test_treeset() {
    int err_count = 0;

    cout<<"Testing TreeSet constructor\n";
    Set* ts = new TreeSet();

//*********************************************************************************
//                               Empty Set
//*********************************************************************************

    cout<<"Testing TreeSet .size()\n";
    cout << "\tSize of empty set: " << ts->size() << endl;
    if(ts->size() != 0) ++err_count;

    cout<<"Testing .isEmpty()\n";
    cout << "\tEmpty set is empty: " << ts->isEmpty() << endl;
    if(ts->isEmpty() != true) ++err_count;
    
    cout<<"Testing .scan() returns an empty vector<string> not NULL:\n";
    vector<string> empty_vec = ts->scan();
    for(int i = 0; i < empty_vec.size(); ++i) {
        cout<<"\tthis should never get printed!!!"<<endl;
    }
    if(empty_vec.size() != 0) ++err_count;

//*********************************************************************************
//                               Singleton
//*********************************************************************************
    ts->insert("One");

    cout<<"Testing insert of 'One'\n";
    cout<<"\tSize of singleton is: "<<ts->size()<<endl;
    if(ts->size() != 1) ++err_count;
    cout<<"\tSingleton is empty: "<<ts->isEmpty()<<endl;
    if(ts->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<ts->in("One")<<endl;
    if(ts->in("One") != true) ++err_count;

    ts->insert("One");
    cout<<"Testing rejection of another 'One'\n";
    cout<<"\tSize of singleton is: "<<ts->size()<<endl;
    if(ts->size() != 1) ++err_count;
    cout<<"\tSingleton is empty: "<<ts->isEmpty()<<endl;
    if(ts->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<ts->in("One")<<endl;
    if(ts->in("One") != true) ++err_count;

//*******************************************************************
//*                         Small Set
//*******************************************************************

    ts->insert("Two");
    ts->insert("One");
    ts->insert("One");
    ts->insert("Two");
    ts->insert("One");

    cout<<"Testing TreeSet .size() and .isEmpty() after 2 unique inserts\n";    
    cout << "\tSize of set: " << ts->size() << endl;
    if(ts->size() != 2) ++err_count;
    cout << "\tEmpty set?: " << ts->isEmpty() << endl;
    if(ts->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<ts->in("One")<<endl;
    if(ts->in("One") != true) ++err_count;
    cout<<"\tset contains 'Two': "<<ts->in("Two")<<endl;
    if(ts->in("Two") != true) ++err_count;
    cout<<"\tset contains 'Three': "<<ts->in("Three")<<endl;
    if(ts->in("Three") == true) ++err_count;

    cout<<"Testing .remove('One')\n";
    ts->remove("One");
    cout << "\tSize of set: " << ts->size() << endl;
    if(ts->size() != 1) ++err_count;
    cout << "\tEmpty set?: " << ts->isEmpty() << endl;
    if(ts->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<ts->in("One")<<endl;
    if(ts->in("One") == true) ++err_count;
    cout<<"\tset contains 'Two': "<<ts->in("Two")<<endl;
    if(ts->in("Two") != true) ++err_count;

    cout<<"Testing .remove('Two')\n";
    ts->remove("Two");
    cout << "\tSize of set: " << ts->size() << endl;
    if(ts->size() != 0) ++err_count;
    cout << "\tEmpty set?: " << ts->isEmpty() << endl;
    if(ts->isEmpty() != true) ++err_count;
    cout<<"\tset contains 'One': "<<ts->in("One")<<endl;
    if(ts->in("One") == true) ++err_count;
    cout<<"\tset contains 'Two': "<<ts->in("Two")<<endl;
    if(ts->in("Two") == true) ++err_count;

    cout<<"Attempt to remove another 'Two'\n";
    ts->remove("Two");
    cout << "\tSize of set: " << ts->size() << endl;
    if(ts->size() != 0) ++err_count;
    cout << "\tEmpty set?: " << ts->isEmpty() << endl;
    if(ts->isEmpty() != true) ++err_count;
    cout<<"\tset contains 'One': "<<ts->in("One")<<endl;
    if(ts->in("One") == true) ++err_count;
    cout<<"\tset contains 'Two': "<<ts->in("Two")<<endl;
    if(ts->in("Two") == true) ++err_count;


//*******************************************************************
//*                         scan
//*******************************************************************
    ts->insert("Three");
    ts->insert("Four");
    ts->insert("Five");

    cout<<"After 3 inserts, ts now contains: \n";
    vector<string> res = ts->scan();
    for(int i = 0; i < res.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res[i]<<endl;
    }
    if(ts->size() != 3) ++err_count;
    

    Set* ts2 = new TreeSet();
    ts2->insert("Five");
    ts2->insert("Six");
    ts2->insert("Seven");

    cout<<"ts2 contains: \n";
    vector<string> res2 = ts2->scan();
    for(int i = 0; i < res2.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res2[i]<<endl;
    }
    if(ts2->size() != 3) ++err_count;

    Set* ts3 = new TreeSet;
    ts3->insert("Three");
    ts3->insert("Seven");

    cout<<"ts3 constains: \n";
    vector<string> res3 = ts3->scan();
    for(int i = 0; i < res3.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res3[i]<<endl;
    }
    if(ts3->size() != 2) ++err_count;
        
//*******************************************************************
//*                         set operations
//*******************************************************************

    Set* ts4 = ts->set_intersect(ts2);
    cout<<"Intersection of ts and ts2 is: \n";
    vector<string> res4 = ts4->scan();
    for(int i = 0; i < res4.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res4[i]<<endl;
    }
    if(ts4->size() != 1) ++err_count;   //intersect on 'Five'

    cout<<"Testing set_union ts and ts2 with results in ts5: \n";
    Set* ts5 = ts->set_union(ts2);
    vector<string> res5 = ts5->scan();
    for(int i = 0; i < res5.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res5[i]<<endl;
    }
    if(ts5->size() != 5) ++err_count;   //union on three, four, five, six, seven

    cout<<"Testing set_diff ts5 and ts3: \n";
    Set* ts6 = ts5->set_diff(ts3);
    vector<string> res6 = ts6->scan();
    for(int i = 0; i < res6.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res6[i]<<endl;
    }
    if(ts6->size() != 3) ++err_count;   //dif on four, five, six


//*******************************************************************
//*                         Corner Cases
//*******************************************************************
    cout<<"Testing set_union, set_intersect and set_diff of empty sets  ts7 and ts8: \n";

    Set* ts7 = new TreeSet;
    Set* ts8 = new TreeSet;

    Set* ts9 = ts7->set_union(ts8);
    vector<string> res9 = ts9->scan();
    for(int i = 0; i < res9.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res9[i]<<endl;
    }

    Set* ts10 = ts7->set_intersect(ts8);
    vector<string> res10 = ts10->scan();
    for(int i = 0; i < res10.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res10[i]<<endl;
    }

    Set* ts11 = ts7->set_diff(ts8);
    vector<string> res11 = ts11->scan();
    for(int i = 0; i < res11.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res11[i]<<endl;
    }

    cout<<"Testing set_union, set_intersect and set_diff of ts2 with empty set: \n";

    ts9 = ts2->set_union(ts8);
    res9 = ts9->scan();
    for(int i = 0; i < res9.size(); ++i) {
        cout<<"\tunion element at "<<i<<" is: "<<res9[i]<<endl;
    }

    ts10 = ts2->set_intersect(ts8);
    res10 = ts10->scan();
    for(int i = 0; i < res10.size(); ++i) {
        cout<<"\tintersect element at "<<i<<" is: "<<res10[i]<<endl;
    }

    ts11 = ts2->set_diff(ts8);
    res11 = ts11->scan();
    for(int i = 0; i < res11.size(); ++i) {
        cout<<"\tdiff element at "<<i<<" is: "<<res11[i]<<endl;
    }

    cout<<"Testing set_union, set_intersect and set_diff of empty set with ts3: \n";

    Set* ts12 = ts7->set_union(ts3);
    vector<string> res12 = ts12->scan();
    for(int i = 0; i < res12.size(); ++i) {
        cout<<"\tunion element at "<<i<<" is: "<<res12[i]<<endl;
    }

    Set* ts13 = ts7->set_intersect(ts3);
    vector<string> res13 = ts13->scan();
    for(int i = 0; i < res13.size(); ++i) {
        cout<<"\tintersect element at "<<i<<" is: "<<res13[i]<<endl;
    }

    Set* ts14 = ts7->set_diff(ts3);
    vector<string> res14 = ts14->scan();
    for(int i = 0; i < res14.size(); ++i) {
        cout<<"\tdiff element at "<<i<<" is: "<<res14[i]<<endl;
    }    

    cout<<"Testing to make sure the base sets haven't been altered:\n";
    res = ts->scan();
    res2 = ts2->scan();
    res3 = ts3->scan();
    for(int i = 0; i < res.size(); ++i) {
        cout<<"\tts element at "<<i<<" is: "<<res[i]<<endl;
    }    
    for(int i = 0; i < res2.size(); ++i) {
        cout<<"\tts2 element at "<<i<<" is: "<<res2[i]<<endl;
    }    
    for(int i = 0; i < res3.size(); ++i) {
        cout<<"\tts3 element at "<<i<<" is: "<<res3[i]<<endl;
    }    

    delete ts, ts2, ts3, ts4, ts5, ts6, ts7, ts8, ts9, ts10, ts11, ts12, ts13, ts14;

    cout<<"Exiting TreeSet test with "<<err_count<<" errors\n";    
    
    return err_count;
}

int test_hashset() {
    int err_count = 0;

    cout<<"Testing HashSet constructor\n";
    Set* hs = new HashSet();

//*********************************************************************************
//                               Empty Set
//*********************************************************************************

    cout<<"Testing HashSet .size()\n";
    cout << "\tSize of empty set: " << hs->size() << endl;
    if(hs->size() != 0) ++err_count;

    cout<<"Testing .isEmpty()\n";
    cout << "\tEmpty set is empty: " << hs->isEmpty() << endl;
    if(hs->isEmpty() != true) ++err_count;
    
    cout<<"Testing .scan() returns an empty vector<string> not NULL:\n";
    vector<string> empty_vec = hs->scan();
    for(int i = 0; i < empty_vec.size(); ++i) {
        cout<<"\tthis should never get printed!!!"<<endl;
    }
    if(empty_vec.size() != 0) ++err_count;
    
//*********************************************************************************
//                               Singleton
//*********************************************************************************
    hs->insert("One");

    cout<<"Testing insert of 'One'\n";
    cout<<"\tSize of singleton is: "<<hs->size()<<endl;
    if(hs->size() != 1) ++err_count;
    cout<<"\tSingleton is empty: "<<hs->isEmpty()<<endl;
    if(hs->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<hs->in("One")<<endl;
    if(hs->in("One") != true) ++err_count;

    hs->insert("One");
    cout<<"Testing rejection of another 'One'\n";
    cout<<"\tSize of singleton is: "<<hs->size()<<endl;
    if(hs->size() != 1) ++err_count;
    cout<<"\tSingleton is empty: "<<hs->isEmpty()<<endl;
    if(hs->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<hs->in("One")<<endl;
    if(hs->in("One") != true) ++err_count;

//*******************************************************************
//*                         Small Set
//*******************************************************************
    hs->insert("Two");
    hs->insert("One");
    hs->insert("One");
    hs->insert("Two");
    hs->insert("One");

    cout<<"Testing TreeSet .size() and .isEmpty() after 2 unique inserts\n";    
    cout << "\tSize of set: " << hs->size() << endl;
    if(hs->size() != 2) ++err_count;
    cout << "\tEmpty set?: " << hs->isEmpty() << endl;
    if(hs->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<hs->in("One")<<endl;
    if(hs->in("One") != true) ++err_count;
    cout<<"\tset contains 'Two': "<<hs->in("Two")<<endl;
    if(hs->in("Two") != true) ++err_count;
    cout<<"\tset contains 'Three': "<<hs->in("Three")<<endl;
    if(hs->in("Three") == true) ++err_count;

    cout<<"Testing .remove('One')\n";
    hs->remove("One");
    cout << "\tSize of set: " << hs->size() << endl;
    if(hs->size() != 1) ++err_count;
    cout << "\tEmpty set?: " << hs->isEmpty() << endl;
    if(hs->isEmpty() != false) ++err_count;
    cout<<"\tset contains 'One': "<<hs->in("One")<<endl;
    if(hs->in("One") == true) ++err_count;
    cout<<"\tset contains 'Two': "<<hs->in("Two")<<endl;
    if(hs->in("Two") != true) ++err_count;

    cout<<"Testing .remove('Two')\n";
    hs->remove("Two");
    cout << "\tSize of set: " << hs->size() << endl;
    if(hs->size() != 0) ++err_count;
    cout << "\tEmpty set?: " << hs->isEmpty() << endl;
    if(hs->isEmpty() != true) ++err_count;
    cout<<"\tset contains 'One': "<<hs->in("One")<<endl;
    if(hs->in("One") == true) ++err_count;
    cout<<"\tset contains 'Two': "<<hs->in("Two")<<endl;
    if(hs->in("Two") == true) ++err_count;

    cout<<"Attempt to remove another 'Two'\n";
    hs->remove("Two");
    cout << "\tSize of set: " << hs->size() << endl;
    if(hs->size() != 0) ++err_count;
    cout << "\tEmpty set?: " << hs->isEmpty() << endl;
    if(hs->isEmpty() != true) ++err_count;
    cout<<"\tset contains 'One': "<<hs->in("One")<<endl;
    if(hs->in("One") == true) ++err_count;
    cout<<"\tset contains 'Two': "<<hs->in("Two")<<endl;
    if(hs->in("Two") == true) ++err_count;
    
//*******************************************************************
//*                         scan
//*******************************************************************
    hs->insert("Three");
    hs->insert("Four");
    hs->insert("Five");

    cout<<"After 3 inserts, hs now contains: \n";
    vector<string> res = hs->scan();
    for(int i = 0; i < res.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res[i]<<endl;
    }
    if(hs->size() != 3) ++err_count;
    

    Set* hs2 = new TreeSet();
    hs2->insert("Five");
    hs2->insert("Six");
    hs2->insert("Seven");

    cout<<"hs2 contains: \n";
    vector<string> res2 = hs2->scan();
    for(int i = 0; i < res2.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res2[i]<<endl;
    }
    if(hs2->size() != 3) ++err_count;

    Set* hs3 = new TreeSet;
    hs3->insert("Three");
    hs3->insert("Seven");

    cout<<"hs3 constains: \n";
    vector<string> res3 = hs3->scan();
    for(int i = 0; i < res3.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res3[i]<<endl;
    }
    if(hs3->size() != 2) ++err_count;
    
//*******************************************************************
//*                         set operations
//*******************************************************************

    Set* hs4 = hs->set_intersect(hs2);
    cout<<"Intersection of hs and hs2 is: \n";
    vector<string> res4 = hs4->scan();
    for(int i = 0; i < res4.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res4[i]<<endl;
    }
    if(hs4->size() != 1) ++err_count;   //intersect on 'Five'
    
    cout<<"Testing set_union hs and hs2 with results in hs5: \n";
    Set* hs5 = hs->set_union(hs2);
    vector<string> res5 = hs5->scan();
    for(int i = 0; i < res5.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res5[i]<<endl;
    }
    if(hs5->size() != 5) ++err_count;   //union on Three, Four, Five, Six, Seven

    cout<<"Testing set_diff hs5 and hs3: \n";
    Set* hs6 = hs5->set_diff(hs3);
    vector<string> res6 = hs6->scan();
    for(int i = 0; i < res6.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res6[i]<<endl;
    }
    if(hs6->size() != 3) ++err_count;   //diff on Four, Five, Six

//*******************************************************************
//*                         Corner Cases
//*******************************************************************
    cout<<"Testing set_union, set_intersect and set_diff of empty sets  hs7 and hs8: \n";

    Set* hs7 = new TreeSet;
    Set* hs8 = new TreeSet;

    Set* hs9 = hs7->set_union(hs8);
    vector<string> res9 = hs9->scan();
    for(int i = 0; i < res9.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res9[i]<<endl;
    }

    Set* hs10 = hs7->set_intersect(hs8);
    vector<string> res10 = hs10->scan();
    for(int i = 0; i < res10.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res10[i]<<endl;
    }

    Set* hs11 = hs7->set_diff(hs8);
    vector<string> res11 = hs11->scan();
    for(int i = 0; i < res11.size(); ++i) {
        cout<<"\telement at "<<i<<" is: "<<res11[i]<<endl;
    }

    cout<<"Testing set_union, set_intersect and set_diff of hs2 with empty set: \n";

    hs9 = hs2->set_union(hs8);
    res9 = hs9->scan();
    for(int i = 0; i < res9.size(); ++i) {
        cout<<"\tunion element at "<<i<<" is: "<<res9[i]<<endl;
    }

    hs10 = hs2->set_intersect(hs8);
    res10 = hs10->scan();
    for(int i = 0; i < res10.size(); ++i) {
        cout<<"\tintersect element at "<<i<<" is: "<<res10[i]<<endl;
    }

    hs11 = hs2->set_diff(hs8);
    res11 = hs11->scan();
    for(int i = 0; i < res11.size(); ++i) {
        cout<<"\tdiff element at "<<i<<" is: "<<res11[i]<<endl;
    }

    cout<<"Testing set_union, set_intersect and set_diff of empty set with hs3: \n";

    Set* hs12 = hs7->set_union(hs3);
    vector<string> res12 = hs12->scan();
    for(int i = 0; i < res12.size(); ++i) {
        cout<<"\tunion element at "<<i<<" is: "<<res12[i]<<endl;
    }

    Set* hs13 = hs7->set_intersect(hs3);
    vector<string> res13 = hs13->scan();
    for(int i = 0; i < res13.size(); ++i) {
        cout<<"\tintersect element at "<<i<<" is: "<<res13[i]<<endl;
    }

    Set* hs14 = hs7->set_diff(hs3);
    vector<string> res14 = hs14->scan();
    for(int i = 0; i < res14.size(); ++i) {
        cout<<"\tdiff element at "<<i<<" is: "<<res14[i]<<endl;
    }    

    cout<<"Testing to make sure the base sets haven't been altered:\n";
    res = hs->scan();
    res2 = hs2->scan();
    res3 = hs3->scan();
    for(int i = 0; i < res.size(); ++i) {
        cout<<"\ths element at "<<i<<" is: "<<res[i]<<endl;
    }    
    for(int i = 0; i < res2.size(); ++i) {
        cout<<"\ths2 element at "<<i<<" is: "<<res2[i]<<endl;
    }    
    for(int i = 0; i < res3.size(); ++i) {
        cout<<"\ths3 element at "<<i<<" is: "<<res3[i]<<endl;
    }    

    delete hs, hs2, hs3, hs4, hs5, hs6, hs7, hs8, hs9, hs10, hs11, hs12, hs13, hs14;

//*******************************************************************
//*                         report errors
//*******************************************************************
    cout<<"Exiting HashSet test with "<<err_count<<" errors\n\n";   
    
    return err_count;      
}

int main() {
    
    int err_count = 0;
    
    err_count += test_treeset();
    
    cout<<"\n-------------------------------\n";
    
    err_count += test_hashset();

    cout<<"-------------------------------\n";
    cout<<"Total error count is: "<<err_count<<endl;

    return 0;
}
