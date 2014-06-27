//============================================================================
// Name        : Student.h
// Author      : Otani
// Version     :
// Copyright   : MoonDeer LLC
// Description : The Student class header file for sample set 2
//============================================================================

#ifndef STUDENT_H_
#define STUDENT_H_

#import <string>
using namespace std;

class Student {

private:

    static const string DEFAULT_SSN; //need to initialize it in the implementation file
    static const int MAX_SCORE_CNT = 10; //for integral const you initialize it here
    static int instanceCnt; //how many instances are created

    string ssn;
    string name;
    float *testScore; //an array of test scores

    void init(string ssn);

public:

    static const int NO_SCORE = -1;

    Student( );
    Student(string ssn);

    ~Student();

    static int getInstanceCnt();

    string  getName();
    string  getSsn();
    float   getTestScore(int pos);

    void setName(string name);
    void setSsn(string ssn);
    bool setTestScore(int pos, float value);

};

#endif /* STUDENT_H_ */
