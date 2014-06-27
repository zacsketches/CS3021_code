//============================================================================
// Name        : Prog2Tester.cpp
// Author      : Zac Staples
// Version     :
// Copyright   : adapted from course work provided by T. Otani
//============================================================================

#include <iostream>
using namespace std;

#include "bignum.h"

#define DEBUG_ADD 0
#define DEBUG_SUB 0
#define DEBUG_MULT 0
#define DEBUG_INCR 1

void testConvert(string numstr[ ], int size) {
	
	cout<<"Testing convert(string val)\n";
	
	stringstream ss;

	int errorCnt = 0;

	long bnum, num;

	//Uncomment the for loop to carry out the test

	for (int i = 0; i < size; i++) {

		ss << toString(convert(numstr[i]));
		ss >> bnum;
		ss.clear();

		ss << numstr[i];
		ss >> num;
		ss.clear();

		if (bnum != num) {
			cout << "error in test "<< i << endl;
			cout << "\tbnum is: "<< bnum << endl;
			cout << "\tnum is: :"<< num << endl;

			errorCnt++;
		}
	}

	cout << "\tConvert Error Cnt: " << errorCnt << endl;
}


void testAdd(string numstr[ ], int size) {

	cout<<"Testing add(BigNum*, BigNum*)\n";

	stringstream ss;
	int errorCnt = 0;
	long bnum, num, l_operand, r_operand;

	for (int i = 0; i < size-1; i++) {	//note size-1 to prevent running off array

		BigNum* lbn = convert(numstr[i]);
		BigNum* rbn = convert(numstr[i+1]);
		BigNum* res = add(lbn, rbn);
		BigNum* res2 = add(lbn, rbn);

		ss << toString(res);
		ss >> bnum;
		if(DEBUG_ADD) cout<<"bnum is: "<<bnum<<endl;
		ss.clear();
		
		ss << numstr[i];
		ss >> l_operand;
		ss.clear();
		
		ss << numstr[i+1];
		ss >> r_operand;
		ss.clear();

		num = l_operand + r_operand;

		if (bnum != num) {
			cout <<"Error: "<< i << '\t';
			cout << "bnum: "<< bnum << '\t';
			cout << "num: " << num << endl;

			errorCnt++;
		}
		
		//test continuity
		if(toString(res) != toString(res2)) {
			cout<<"\tconinuity error\n";
			cout<<"\tres is: "<<toString(res)<<endl;
			cout<<"\tres2 is:"<<toString(res2)<<endl;
			cout<<"numstrings are: "<<numstr[i]<<'\t'<<numstr[i+1]<<endl;
			++errorCnt;
		}
	}
	cout<< "\tAdd Error Cnt: " << errorCnt << endl;
}

void testSub(string numstr[ ], int size) {

	cout<<"Testing sub(BigNum*, BigNum*)\n";

	stringstream ss;
	int errorCnt = 0;
	long bnum, num, l_operand, r_operand;

	for (int i = 0; i < size-1; i++) {	//note size-1 to prevent running off array

		BigNum* lbn = convert(numstr[i]);
		BigNum* rbn = convert(numstr[i+1]);
		BigNum* res = sub(lbn, rbn);
		BigNum* res2 = sub(lbn, rbn);

		ss << toString(res);
		ss >> bnum;
		if(DEBUG_SUB) cout<<"bnum is: "<<bnum<<endl;
		ss.clear();
		
		ss << numstr[i];
		ss >> l_operand;
		ss.clear();
		
		ss << numstr[i+1];
		ss >> r_operand;
		ss.clear();

		num = l_operand - r_operand;

		if (bnum != num) {
			cout <<"Error: "<< i << '\t';
			cout << "bnum: "<< bnum << '\t';
			cout << "num: " << num << endl;

			errorCnt++;
		}
		
		//test continuity
		if(toString(res) != toString(res2)) {
			cout<<"\tconinuity error\n";
			cout<<"\tres is: "<<toString(res)<<endl;
			cout<<"\tres2 is:"<<toString(res2)<<endl;
			cout<<"numstrings are: "<<numstr[i]<<'\t'<<numstr[i+1]<<endl;
			++errorCnt;
		}
	}
	cout<< "\tSub Error Cnt: " << errorCnt << endl;
}
void test_compare(string numstr[ ], int size) {

	cout<<"Testing compare(BigNum*, BigNum*)\n";

	stringstream ss;
	int errorCnt = 0;
	long bnum, num, l_operand, r_operand;

	for (int i = 0; i < size-1; i++) {	//note size-1 to prevent running off array

		BigNum* lbn = convert(numstr[i]);
		BigNum* rbn = convert(numstr[i+1]);
		string l_str_1 = toString(lbn);
		string r_str_1 = toString(rbn);
		
		int bnum = compare(lbn, rbn);
		
		string l_str_2 = toString(lbn);
		string r_str_2 = toString(rbn);
 		
		ss << numstr[i];
		ss >> l_operand;
		ss.clear();
		
		ss << numstr[i+1];
		ss >> r_operand;
		ss.clear();
		
		if( l_operand < r_operand )
			num = -1;
		if( l_operand > r_operand)
			num = 1;
		if( l_operand == r_operand )
			num = 0;
			
		if (bnum != num) {
			cout <<"Error: "<< i << '\t';
			cout << "bnum: "<< bnum << '\t';
			cout << "num: " << num << endl;
			cout << "\ti val is: "<<numstr[i]<<"\ti+1 val is: "<<numstr[i+1]<<endl;

			errorCnt++;
		}
		
		//test continuity
		if((l_str_1 != l_str_2 ) && (r_str_1 != r_str_2)) {
			cout<<"\tconinuity error\n";
			cout<<"\tl_str_1 is: "<<l_str_1<<endl;
			cout<<"\tl_str_2 is: "<<l_str_2<<endl;
			cout<<"\tr_str_1 is: "<<r_str_1<<endl;
			cout<<"\tr_str_2 is: "<<r_str_2<<endl;
			cout<<"numstrings are: "<<numstr[i]<<'\t'<<numstr[i+1]<<endl;
			++errorCnt;
		}
		
	}
	cout<< "\tCompare Error Cnt: " << errorCnt << endl;
}

void test_mult(string numstr[ ], int size) {

	cout<<"Testing mult(BigNum*, BigNum*)\n";
	long l_max = numeric_limits<long>::max();
	cout << "Maximum value for long: " << l_max << '\n';
	cout << "Python contains no limit on number represenation.\n";
	cout << "I used the Python interactive prompt to verify long data when required.\n";
	

	stringstream ss;
	int errorCnt = 0;
	long bnum, num, l_operand, r_operand;

	for (int i = 0; i < size-1; i++) {	//note size-1 to prevent running off array

		BigNum* lbn = convert(numstr[i]);
		BigNum* rbn = convert(numstr[i+1]);
		BigNum* res = mult(lbn, rbn);
		BigNum* res2 = mult(lbn, rbn);
		
		ss << toString(res);
//		if(DEBUG_MULT) cout<<"res at the top is: "<<toString(res)<<endl;
		ss >> bnum;
		ss.clear();
		
		ss << numstr[i];
		ss >> l_operand;
//		if(DEBUG_MULT) cout<<"\tl_operand is: "<<l_operand<<endl;
		ss.clear();
		
		ss << numstr[i+1];
		ss >> r_operand;
//		if(DEBUG_MULT) cout<<"\tr_operand is: "<<r_operand<<endl;
		ss.clear();

		num = l_operand * r_operand;
			
		if (bnum != num) {
			//get a string representation for the largest possible long type
			string l_string;
			ss << l_max;
			ss >> l_string;
			ss.clear();
			
			if(toString(res).size() > l_string.size()) {
				cout<<"In test "<<i<<" BigNum contains more digits than long allows\n";
				cout<<"\t"<<numstr[i]<<" * "<<numstr[i+1]<<endl;
				cout<<"\tBigNum product is: "<<toString(res)<<endl;
			}
			else{
				cout <<"Error: "<< i << '\t';
				cout << "bnum: "<< bnum << '\t';
				cout << "num: " << num << endl;
				cout << "\tnumstr[i] is: "<<numstr[i]<<"\tnumstr[i+1] is: "<<numstr[i+1]<<endl;
				cout << "string rep of bnum is: "<<toString(res)<<endl;
				cout << endl;
				errorCnt++;
			}
		}
		
		//test continuity
		if(toString(res) != toString(res2)) {
			cout<<"\tconinuity error\n";
			cout<<"\tres is: "<<toString(res)<<endl;
			cout<<"\tres2 is:"<<toString(res2)<<endl;
			cout<<"numstrings are: "<<numstr[i]<<'\t'<<numstr[i+1]<<endl;
			++errorCnt;
		}
	}
	cout<< "\tMult Error Cnt: " << errorCnt << endl;
}

void test_incr(string numstr[ ], int size) {

	cout<<"Testing incr(BigNum* num)\n";

	stringstream ss;
	int errorCnt = 0;
	long bnum, num, l_operand;

	for (int i = 0; i < size; i++) {

		BigNum* lbn = convert(numstr[i]);
		BigNum* res = incr(lbn);
		BigNum* res2 = incr(lbn);

		ss << toString(res);
		ss >> bnum;
		if(DEBUG_INCR) cout<<"bnum is: "<<bnum<<endl;
		ss.clear();
		
		ss << numstr[i];
		ss >> l_operand;
		ss.clear();
		
		num = l_operand + 1;

		if (bnum != num) {
			cout <<"Error: "<< i << '\t';
			cout << "bnum: "<< bnum << '\t';
			cout << "num: " << num << endl;

			errorCnt++;
		}
		
		//test continuity
		if(toString(res) != toString(res2)) {
			cout<<"\tconinuity error\n";
			cout<<"\tres is: "<<toString(res)<<endl;
			cout<<"\tres2 is:"<<toString(res2)<<endl;
			cout<<"numstring is: "<<numstr[i]<<endl;
			++errorCnt;
		}
	}
	cout<< "\tAdd Error Cnt: " << errorCnt << endl;
}


int main() {

	int size = 18;

	string numStr[] = {                  "0",               "-1",            "-2",
						    "11111111111111", "-11111111111111",  "999999999999",
						    "38495859800098",  "-9098998989989",  "909899898990",
						          "-0000008",            "0010",  "123458989899",
							"12121212121212",             "-45",  "777777777777",
							"38495859800098",  "-9098998989989",  "909899898990"};

	testConvert(numStr, size);

	testAdd(numStr, size);
	
	testSub(numStr, size);
	
	test_compare(numStr, size);
	
	test_mult(numStr, size);
	
 	string numStr2[] = {                 "0",               "1",             "2",
						    "11111111111111",             "999",  "999999999999",
						    "38495859800098",                     "909899898990",
						                                 "0010",  "123458989899",
							"12121212121212",                     "777777777777",
							"38495859800098",                     "909899898990"};
	size = 14;

	test_incr(numStr2, size);
                     
	return 0;
}
