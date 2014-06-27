//============================================================================
// Name        : HW9.cpp
// Author      : Zac Staples
//============================================================================

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <time.h>
#include "BST.h"
#include "AVL.h"
#include "random_array.h"

struct Record {
    enum type {BST, AVL};
    type t;
    int sz;
    int ht;
    double avg_d;
    double avg_i;
    double avg_s;

    Record(Record::type T, int size, int height,
           double avg_depth, double avg_insert, double avg_search)
           : t(T), sz(size), ht(height), avg_d(avg_depth), avg_i(avg_insert), avg_s(avg_search)
    {}
};

ostream& operator<<(ostream& os, const Record& r){
    string T;
    T = (r.t == Record::BST) ? "BST" : "AVL";
    os<<T<<", "<<r.sz<<", "<<r.ht<<", "<<r.avg_d<<", "<<r.avg_i<<", "<<r.avg_s<<endl;
    return os;
}

using namespace std;

void traverseInt(AVL<int>* avl, AVL<int>::TRAVERSAL order) {

	vector<int*> vec;

	vec = avl->scan(order);

    for (int i = 0; i< vec.size(); ++i) {
        int* item  = vec[i];
		cout << *item << " ";
	}

	cout << endl;
}

void traverseInt(BST<int> *bst, BST<int>::TRAVERSAL order) {

	vector<int*> vec;

	vec = bst->scan(order);

    for (int i = 0; i< vec.size(); ++i) {
        int* item  = vec[i]; 
		cout << *item << " ";
	}

	cout << endl;
}

void run(int val[], int size, vector<Record*>& v) {

	clock_t start;	// variable to mark start time
	clock_t stop;	// variable to mark stop time
	int insert_time;	// variable to hold the elapse time (in sec) of insert
	int search_time;	// variable to hold the elapse time (in sec) of search

	AVL<int>* avl = new AVL<int>;
	BST<int>* bst = new BST<int>;

	// mark the start time
	start = clock();

	// insert the numbers into the AVL tree
	for (int i = 0; i < size; i++) {
		avl->insert(new int(val[i]));
	}

	// mark the stop time
	stop = clock();

	// compute the elapsed time
	insert_time = stop - start;

	// mark the start time
	start = clock();

	// search the numbers in the AVL tree
	for (int i = 0; i < size; i += 2) {
		avl->search(new int(val[i]));
	}

	// mark the stop time
	stop = clock();

	// compute the elapsed time
	search_time = stop - start;

	cout << "Size of AVL after inserting " << size << " items: " << avl->size()
			<< endl;

    // cout << "Height of AVL = " << avl->height() << endl;
    // cout << "Avg Depth = " << avl->avgDepth() << endl;
    // cout << "Avg time per insertion = " << (double) insert_time / size << endl;
    // cout << "Avg time per search = " << (double) search_time / (size / 2.0)
    //      << endl;


    //push r into a vector
    v.push_back( new Record(Record::AVL, avl->size(), avl->height(), avl->avgDepth(),
                           ( (double)insert_time/size ), ( (double)search_time/(size/2.0) ) )
    );


	// clean up
	delete avl;

	cout << endl;

	// mark the start time
	start = clock();

	// insert the numbers into the bst tree
	for (int i = 0; i < size; i++) {
		bst->insert(new int(val[i]));
	}

	// mark the stop time
	stop = clock();

	// computer the elapse time
	insert_time = stop - start;

	// mark the start time
	start = clock();

	// search the numbers into the AVL tree
	for (int i = 0; i < size; i += 2) {
		bst->search(new int(val[i]));
	}

	// mark the stop time
	stop = clock();

	// computer the elapse time
	search_time = stop - start;

	cout << "Size of BST after inserting " << size << " items: " << bst->size()
			<< endl;

    // cout << "Height of BST = " << bst->height() << endl;
    // cout << "Avg Depth = " << bst->avgDepth() << endl;
    // cout << "Avg time per insertion = " << (double) insert_time / size << endl;
    // cout << "Avg time per search = " << (double) search_time / (size / 2.0)
    //      << endl;

    v.push_back( new Record(Record::BST, bst->size(), bst->height(), bst->avgDepth(),
                           ( (double)insert_time/size ), ( (double)search_time/(size/2.0) ) )
    );
    
	// clean up
	delete bst;
}



int main() {

	initialize_random(0);
	
    vector<Record*> results;

	for (int i = 10000; i < 100000; i += 10000) {
		int* intArray = new int[i];
		create_array(intArray, i);
		run(intArray, i, results);
		delete intArray;
		cout << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl;
	}
	
    ofstream ofs("results4.txt");
    if(!ofs) throw runtime_error("unable to open output file");
	
	for(int i = 0; i < results.size(); ++i) {
        cout<< *(results[i]);
        ofs << *(results[i]);
	}
	
    clock_t t = 1.0;
    cout<<"1 tick is equal to "<<CLOCKS_PER_SEC<<endl;
    cout<<"or 1 tick is equal to "<<t/CLOCKS_PER_SEC<<" seconds\n";
	

	return 0;
}
