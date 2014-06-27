//============================================================================
// Name        : Student.cpp
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : The Student class implementation file for sample set 2
//============================================================================

#include "Student.h"

const string Student::DEFAULT_SSN = "000-00-0000";

int Student::instanceCnt = 0; //initialize to 0

Student::Student( ) {
	init(DEFAULT_SSN);
}

Student::Student(string ssn) {
	init(ssn);
}

int Student::getInstanceCnt( ) { //No static designator here
	return instanceCnt;
}

string Student::getName() {

    return name;
}

string Student::getSsn() {

    return ssn;
}

float Student::getTestScore(int pos) {

	if (pos < 0 || pos >= MAX_SCORE_CNT) {

		return NO_SCORE;

	} else {

		return testScore[pos];
	}
}

void Student::setName(string aname) {

    name = aname;
}

void Student::setSsn(string assn) {

    ssn = assn;
}

bool Student::setTestScore(int pos, float value) {

	if (pos < 0 || pos >= MAX_SCORE_CNT) {

		return false;

	} else {

		testScore[pos] = value;

		return true;
	}
}

void Student::init(string ssn) {
	setSsn(ssn);

	testScore = new float[MAX_SCORE_CNT];

	instanceCnt++; //count up every time a new instance is created
}

Student::~Student() {

	delete[] testScore; //deallocate the whole array

}

