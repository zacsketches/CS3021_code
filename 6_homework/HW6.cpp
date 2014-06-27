//============================================================================
// Name        : HW6.cpp	
// Author      : Zac Staples
// Assignment  : CS3021 Homework assignment 6
//============================================================================

#include <iostream>
#include "Student.h"
using namespace std;

#define DEBUG_AVG 0
#define DEBUG_TEST 0

const int MAX_SCORE_COUNT = 10;

int main() {
	// creating an array of 10 pointers to student objects
	Student* (students[10]);

	// Task 1:
	// create 4 student objects with the following information and
	// assign them into the first entries of the students array
	//
	// student 1
	// name = "John"
	// ssn = "111-11-1111"
	// test scores = 100, 80, 27
	
	Student* s1 = new Student("111-11-1111");
	s1->setName("John");
	s1->setTestScore(0, 100);
	s1->setTestScore(1, 80);
	s1->setTestScore(2, 27);

	// student 2
	// name = "Jill"
	// ssn = "222-22-2222"
	// test scores = 89, 100, 97
	Student* s2 = new Student("222-22-2222");
	s2->setName("Jill");
	s2->setTestScore(0, 89);
	s2->setTestScore(1, 100);
	s2->setTestScore(2, 97);
	
	// student 3
	// name = "Peter"
	// ssn = "333-33-3333"
	// test scores = 70, 80, 100
	Student* s3 = new Student("333-33-3333");
	s3->setName("Peter");
	s3->setTestScore(0, 70);
	s3->setTestScore(1, 80);
	s3->setTestScore(2, 100);
	
	// student 4
	// name = "Dawn"
	// ssn = "444-44-4444"
	// test scores = 75, 85, 91
	Student* s4 = new Student("444-44-4444");
	s4->setName("Dawn");
	s4->setTestScore(0, 75);
	s4->setTestScore(1, 85);
	s4->setTestScore(2, 91);

	students[0] = s1;
	students[1] = s2;
	students[2] = s3;
	students[3] = s4;
	
	// Task 2:
	// compute and output the average test score of for each student in
	// the students array
	cout<<endl;
	for (int i = 0; i < Student::getInstanceCnt(); i++) {
		if(i == 0) cout<<"There are "<<Student::getInstanceCnt()<<" students."
			<<" Their average test grades are: "<<endl;
		cout<<'\t'<<students[i]->getName()<<": ";
			//compute average
			double avg = 0.0;
			double samples = 0.0;
			for(size_t j = 0; j < MAX_SCORE_COUNT; ++j)
			{
				float tmp = students[i]->getTestScore(j);
				if(tmp != Student::NO_SCORE && tmp!=0){
					++samples;
					//iterative mean algorithm
					avg = (samples - 1)/samples * avg + 1.0/samples * tmp;
				}
			}
		cout<<avg<<endl;
	}

	// Task 3:
	// compute and output the class average of the first test
	double avg2 = 0.0;
	double samples2 = 0.0;
	for (int i = 0; i < Student::getInstanceCnt(); i++) {
		if(i == 0) cout<<"\nThe average test score for test 1 is: ";
			//compute average using iterative mean algorithm
			++samples2;
			float tmp = students[i]->getTestScore(0);
			avg2 = (samples2 - 1)/samples2 * avg2 + 1.0/samples2 * tmp;
	}
	cout<<avg2<<endl<<endl;
	
	
	cout << "!!!Done!!!" << endl;
	return 0;
}
