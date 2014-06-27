#define BOOST_TEST_MODULE MyTest

//The .../included/... version does not require linking to work
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <vector>
#include <limits>
#include "bignum.h"

#define DEBUG 0

struct Mini_test{
	string left;
	string right;
	string product;
	Mini_test(string l, string r, string p){
		left = l;
		right = r;
		product = p;
	}
};

//*********************************************************************************
//                               HELPER SIGNATURES
//*********************************************************************************
//provided by the assignment
void clear(BigNum* number);

//helpers to convert
string trim_zeros(string val);
int get_sign(const string val);
string trim_sign(string val);
BigNode* make_node(const string trigraph);

//helpers to add and sub
string to_string(const int n);
BigNum* add_abs(BigNum* left, BigNum* right);
BigNum* sub_abs(BigNum* lbn, BigNum* rbn);

//helper to mult
BigNum* mult_abs_direct(BigNum* lbn, BigNum* rbn);
BigNum* repeated_add(int repeats, long repeats_place, BigNum* lbn);

//********************************************************************
// BOOST_AUTO_TEST_CASE(my_test)
//		Purpose: 		run unit test within Boost Test Framework	
//		Algorithm:		see Boost.org
//		Input:			test conditions 
//		Output:			test results
//		Precondition:	linked with .cpp file where production code resides
//		Postcondition:	failed tests recoded
//********************************************************************
BOOST_AUTO_TEST_CASE( my_test )
{
   /*
	* seven ways to detect and report the same error:
    * BOOST_CHECK( add( 2,2 ) == 4 );        // #1 continues on error
	* 
    * BOOST_REQUIRE( add( 2,2 ) == 4 );      // #2 throws on error
	* 
    * if( add( 2,2 ) != 5 )
    * BOOST_ERROR( "Ouch..." );            // #3 continues on error
	*
	* if( add( 2,2 ) != 4 )
    * BOOST_FAIL( "Ouch..." );             // #4 throws on error
	*
	* if( add( 2,2 ) != 4 ) throw "Ouch..."; // #5 throws on error
	* BOOST_CHECK_MESSAGE( add( 2,2 ) == 5,  // #6 continues on error
    *                     "add(..) result: " << add( 2,2 ) );
	*
	* BOOST_CHECK_EQUAL( add( 2,2 ), 4 );	  // #7 continues on error
	*
	*/
	
	
	//*********************************************************************************
	//                               TEST TRIM_ZEROS
	//*********************************************************************************
	cout<<"testing 'string trim_zeros(string val)'\n";

	string str5 = "000001230";
	string str6 = "-000001023";
	string str7 = "+000001203";
	string str8 = "12340000";
	str5 = trim_zeros(str5);
	str6 = trim_zeros(str6);
	str7 = trim_zeros(str7);
	str8 = trim_zeros(str8);
	BOOST_CHECK(str5 == "1230");
	BOOST_CHECK(str6 == "-1023");
	BOOST_CHECK(str7 == "+1203");
	BOOST_CHECK(str8 == "12340000");
	if(DEBUG){
		cout<<"str5 is: "<<str5<<endl;
		cout<<"str6 is: "<<str6<<endl;
		cout<<"str7 is: "<<str7<<endl;
		cout<<"str8 is: "<<str8<<endl;
	}
	
	//*********************************************************************************
	//                               TEST TRIM_SIGN
	//*********************************************************************************
	cout<<"testing 'string trim_sign(string val)'\n";
	string str9 = "-12345";
	string str10 = "+12345";
	string str11 = "12345";
	str9 = trim_sign(str9);
	str10 = trim_sign(str10);
	str11 = trim_sign(str11);
	BOOST_CHECK(str11 == str9);
	BOOST_CHECK(str11 == str10);
	if(DEBUG) {
		cout<<"strings 9, 10 and 11 are: \n";
		cout<<"\t"<<str9<<"\t"<<str10<<"\t"<<str11<<"\n";
	}

	//*********************************************************************************
	//                               TEST GET_SIGN
	//*********************************************************************************
	cout<<"testing 'int get_sign(string val)'\n";
	string str12 = "-12345";
	string str13 = "+12345";
	string str14 = "12345";
	int t1 = get_sign(str12);
	int t2 = get_sign(str13);
	int t3 = get_sign(str14);
	BOOST_CHECK(t1 == -1);
	BOOST_CHECK(t2 == 1);
	BOOST_CHECK(t3 == 1);
	if(DEBUG) {
		cout<<str12<<" has sign: "<<t1<<endl;
		cout<<str13<<" has sign: "<<t2<<endl;
		cout<<str14<<" has sign: "<<t3<<endl;
	}


		
	//*********************************************************************************
	//                               TEST CONVERT
	//*********************************************************************************
	cout<<"testing 'BigNum* convert(BigNum* bn)'\n";
	
	//CASE #1	
	BigNum* bn18 = convert("12345");
	BOOST_CHECK(bn18->sign == 1);
	BigNode* node18 = bn18->mag;
	BOOST_CHECK(node18->data == 345);
	node18 = node18->link;
	BOOST_CHECK(node18->data == 12);
	node18 = node18->link;
	BOOST_CHECK(node18 == NULL);
	
	//CASE #2	
	BigNum* bn19 = convert("-123456");
	BOOST_CHECK(bn19->sign == -1);
	BigNode* node19 = bn19->mag;
	BOOST_CHECK(node19->data == 456);
	node19 = node19->link;
	BOOST_CHECK(node19->data == 123);
	node19 = node19->link;
	BOOST_CHECK(node19 == NULL);
	
	//CASE #3	
	BigNum* bn20 = convert("+123456789");
	BOOST_CHECK(bn20->sign == 1);
	BigNode* node20 = bn20->mag;
	BOOST_CHECK(node20->data == 789);
	node20 = node20->link;
	BOOST_CHECK(node20->data == 456);
	node20 = node20->link;
	BOOST_CHECK(node20->data == 123);
	node20 = node20->link;
	BOOST_CHECK(node20 == NULL);
	
	//CASE #4	
	BigNum* bn21 = convert("+00000");
	BOOST_CHECK(bn21->sign == 1);
	BigNode* node21 = bn21->mag;
	BOOST_CHECK(node21->data == 0);
	node21 = node21->link;
	BOOST_CHECK(node21 == NULL);

	//CASE #5	
	BigNum* bn21b = convert("0");
	BOOST_CHECK(bn21b->sign == 1);
	BigNode* node21b = bn21b->mag;
	BOOST_CHECK(node21b->data == 0);
	node21b = node21b->link;
	BOOST_CHECK(node21b == NULL);
	

	clear(bn18);
	clear(bn19);
	clear(bn20);
	clear(bn21);
	
	//*********************************************************************************
	//                               TEST TO_STRING
	//*********************************************************************************
	cout<<"testing 'string toString(BigNum* bn)'\n";
	// CASE #1
	string str27 = "+3000789";
	BigNum* bn27 = convert(str27);
	string comeback27 = toString(bn27);
	BOOST_CHECK(comeback27 == "3000789");
	if(DEBUG){
		cout<<"comeback is: "<<comeback27<<endl;
	}
	
	// CASE #2
	string str28 = "-000789";
	BigNum* bn28 = convert(str28);
	string comeback28 = toString(bn28);
	BOOST_CHECK(comeback28 == "-789");
	if(DEBUG){
		cout<<"comeback is: "<<comeback28<<endl;
	}
	
	// CASE #3
	string str29 = "7891234568800";
	BigNum* bn29 = convert(str29);
	string comeback29 = toString(bn29);
	BOOST_CHECK(comeback29 == "7891234568800");
	if(DEBUG){
		cout<<"comeback is: "<<comeback29<<endl;
	}
	
	// CASE #4
	string str29b = "0";
	BigNum* bn29b = convert(str29b);
	string comeback29b = toString(bn29b);
	BOOST_CHECK(comeback29b == "0");
	if(DEBUG){
		cout<<"comeback is: "<<comeback29b<<endl;
	}


	//*********************************************************************************
	//                               TEST COMPARE
	//*********************************************************************************
	cout<<"testing 'int compare(BigNum* leftOperand, BigNum* rightOperand);'\n";
	
	// CASE #1
	string str30_a = "-123";
	string str30_b = "123";
	BigNum* bn30_a = convert(str30_a);
	BigNum* bn30_b = convert(str30_b);
	BOOST_CHECK(compare(bn30_a, bn30_b) == -1 );
	
	// CASE #2
	string str31_a = "-123";
	string str31_b = "123";
	BigNum* bn31_a = convert(str31_a);
	BigNum* bn31_b = convert(str31_b);
	BOOST_CHECK(compare(bn31_a, bn31_b) == -1 );
	
	// CASE #3
	string str33_a = "-123";
	string str33_b = "-123456";
	BigNum* bn33_a = convert(str33_a);
	BigNum* bn33_b = convert(str33_b);
	BOOST_CHECK(compare(bn33_a, bn33_b) == 1 );
	
	// CASE #4
	string str34_a = "-123456";
	string str34_b = "-123";
	BigNum* bn34_a = convert(str34_a);
	BigNum* bn34_b = convert(str34_b);
	BOOST_CHECK(compare(bn34_a, bn34_b) == -1 );
	
	// CASE #5
	string str35_a = "-121";
	string str35_b = "-123";
	BigNum* bn35_a = convert(str35_a);
	BigNum* bn35_b = convert(str35_b);
	BOOST_CHECK(compare(bn35_a, bn35_b) == 1 );
	
	// CASE #6
	string str36_a = "-123";
	string str36_b = "-121";
	BigNum* bn36_a = convert(str36_a);
	BigNum* bn36_b = convert(str36_b);
	BOOST_CHECK(compare(bn36_a, bn36_b) == -1 );
	
	// CASE #7
	string str37_a = "-123456789";
	string str37_b = "-123456789";
	BigNum* bn37_a = convert(str37_a);
	BigNum* bn37_b = convert(str37_b);
	BOOST_CHECK(compare(bn37_a, bn37_b) == 0 );
	if(DEBUG) {
		cout<<"str37_a sign is: "<< bn37_a->sign << endl;
		cout<<"str37_b sign is: "<< bn37_b->sign << endl;
		cout<<"Comparison is: "<<compare(bn37_a, bn37_b) <<endl;
	}
	
	// CASE #8
	string str38_a = "121";
	string str38_b = "123";
	BigNum* bn38_a = convert(str38_a);
	BigNum* bn38_b = convert(str38_b);
	BOOST_CHECK(compare(bn38_a, bn38_b) == -1 );
	
	// CASE #9
	string str39_a = "123";
	string str39_b = "121";
	BigNum* bn39_a = convert(str39_a);
	BigNum* bn39_b = convert(str39_b);
	BOOST_CHECK(compare(bn39_a, bn39_b) == 1 );
	
	// CASE #10
	string str40_a = "123456789";
	string str40_b = "123456789";
	BigNum* bn40_a = convert(str40_a);
	BigNum* bn40_b = convert(str40_b);
	BOOST_CHECK(compare(bn40_a, bn40_b) == 0 );
	
	// CASE #11
	string str41_a = "-000";
	string str41_b = "0";
	BigNum* bn41_a = convert(str41_a);
	BigNum* bn41_b = convert(str41_b);
	BOOST_CHECK(compare(bn41_a, bn41_b) == 0 );
	
	//*********************************************************************************
	//                               TEST ADD_ABS
	//*********************************************************************************
	cout<<"testing 'BigNum* add_abs(BigNode* lbn, BigNode* rbn)'\n";
	// CASE # 1
	string str42_a = "111";
	string str42_b = "222";
	BigNum* bn42_a = convert(str42_a);
	BigNum* bn42_b = convert(str42_b);
	BigNum* res42 = add_abs(bn42_a, bn42_b);
	BOOST_CHECK(toString(res42) =="333");
	
	// CASE # 2
	string str43_a = "111111";
	string str43_b = "222";
	BigNum* bn43_a = convert(str43_a);
	BigNum* bn43_b = convert(str43_b);
	BigNum* res43 = add_abs(bn43_a, bn43_b);
	BOOST_CHECK(toString(res43) =="111333");
	
	// CASE # 3
	string str44_a = "999";
	string str44_b = "2";
	BigNum* bn44_a = convert(str44_a);
	BigNum* bn44_b = convert(str44_b);
	BigNum* res44 = add_abs(bn44_a, bn44_b);
	BOOST_CHECK(toString(res44) =="1001");
	
	// CASE # 4
	string str45_a = "2548";
	string str45_b = "17893";
	BigNum* bn45_a = convert(str45_a);
	BigNum* bn45_b = convert(str45_b);
	BigNum* res45 = add_abs(bn45_a, bn45_b);
	BOOST_CHECK(toString(res45) =="20441");
	
	// CASE # 5
	string str46_a = "222";
	string str46_b = "111111";
	BigNum* bn46_a = convert(str46_a);
	BigNum* bn46_b = convert(str46_b);
	BigNum* res46 = add_abs(bn46_a, bn46_b);
	BOOST_CHECK(toString(res46) =="111333");
	
	// CASE # 6
	string str47_a = "0";
	string str47_b = "0";
	BigNum* bn47_a = convert(str47_a);
	BigNum* bn47_b = convert(str47_b);
	BigNum* res47 = add_abs(bn47_a, bn47_b);
	BOOST_CHECK(toString(res47) =="0");
	
	// CASE # 7
	string str48_a = "-0";
	string str48_b = "1";
	BigNum* bn48_a = convert(str48_a);
	BigNum* bn48_b = convert(str48_b);
	BigNum* res48 = add_abs(bn48_a, bn48_b);
	BOOST_CHECK(toString(res48) =="1");
	
	// CASE # 8
	string str49_a = "89457862563695864235";
	string str49_b = "994535628678900021";
	BigNum* bn49_a = convert(str49_a);
	BigNum* bn49_b = convert(str49_b);
	BigNum* res49 = add_abs(bn49_a, bn49_b);
	BOOST_CHECK(toString(res49) =="90452398192374764256");
	
	// CASE # 9
	string str50_a = "999999";
	string str50_b = "243";
	BigNum* bn50_a = convert(str50_a);
	BigNum* bn50_b = convert(str50_b);
	BigNum* res50 = add_abs(bn50_a, bn50_b);
	BOOST_CHECK(toString(res50) =="1000242");
	
	// CASE # 10
	string str51_a = "56878";
	string str51_b = "999999999";
	BigNum* bn51_a = convert(str51_a);
	BigNum* bn51_b = convert(str51_b);
	BigNum* res51 = add_abs(bn51_a, bn51_b);
	BOOST_CHECK(toString(res51) =="1000056877");
	
	//*********************************************************************************
	//                               TEST SUB_ABS
	//*********************************************************************************
	cout<<"testing 'BigNum* sub_abs(BigNum* lbn, BigNum* rbn)'\n";
	
	// CASE #1 EQUAL
	string str52_a = "56878";
	string str52_b = "56878";
	BigNum* bn52_a = convert(str52_a);
	BigNum* bn52_b = convert(str52_b);
	BigNum* res52 = sub_abs(bn52_a, bn52_b);
	BOOST_CHECK(toString(res52) =="0");
	
	// CASE #2 RIGHT > LEFT...no borrowing
	string str53_a = "10";
	string str53_b = "15";
	BigNum* bn53_a = convert(str53_a);
	BigNum* bn53_b = convert(str53_b);
	BigNum* res53 = sub_abs(bn53_a, bn53_b);
	BOOST_CHECK(toString(res53) == "-5");
	
	//CASE #3 LEFT > RIGHT...borrowing with nothing in right's tri_high
	string str54_a = "1050";
	string str54_b = "100";
	BigNum* bn54_a = convert(str54_a);
	BigNum* bn54_b = convert(str54_b);
	BigNum* res54 = sub_abs(bn54_a, bn54_b);
	string comeback54 = toString(res54);
	BOOST_CHECK(comeback54 == "950");
//	cout<<"comeback is: "<<comeback54<<endl;
	
	//CASE #4 LEFT > RIGHT...borrowing with data in right's tri_high
	string str55_a = "3050";
	string str55_b = "1100";
	BigNum* bn55_a = convert(str55_a);
	BigNum* bn55_b = convert(str55_b);
	BigNum* res55 = sub_abs(bn55_a, bn55_b);
	string comeback55 = toString(res55);
	BOOST_CHECK(comeback55 == "1950");
//	cout<<"comeback is: "<<comeback55<<endl;
	
	//CASE #5 RIGHT > LEFT...the hard stuff now
	string str56_a = "2134568198654";
	string str56_b = "9999999999911";
	BigNum* bn56_a = convert(str56_a);
	BigNum* bn56_b = convert(str56_b);
	BigNum* res56 = sub_abs(bn56_a, bn56_b);
	string comeback56 = toString(res56);
	BOOST_CHECK(comeback56 == "-7865431801257");
//	cout<<"comeback is: "<<comeback56<<endl;
	
	//CASE #6 LEFT > RIGHT...the hard stuff now
	string str57_a = "555000111";
	string str57_b = "999444";
	BigNum* bn57_a = convert(str57_a);
	BigNum* bn57_b = convert(str57_b);
	BigNum* res57 = sub_abs(bn57_a, bn57_b);
	string comeback57 = toString(res57);
	BOOST_CHECK(comeback57 == "554000667");
//	cout<<"comeback is: "<<comeback57<<endl;	
	
	//*********************************************************************************
	//                               TEST ADD
	//*********************************************************************************
	cout<<"testing 'BigNum* add(BigNum* lbn, BigNum* rbn)'\n";
	/*
	 * 		+L  +  +R =    +L  +  +R
	 * 		+L  +  -R =    +L  -  +R
	 * 		-L  +  +R =    +R  -  +L
	 * 		-L  +  -R =  -(+L  +  +R)
	 */
	// CASE 1 +L  +  +R
	string str58_a = "2548";
	string str58_b = "17893";
	BigNum* bn58_a = convert(str58_a);
	BigNum* bn58_b = convert(str58_b);
	BigNum* res58 = add(bn58_a, bn58_b);
	BOOST_CHECK(toString(res58) =="20441"); 


	// CASE #2: +L + -R == +L - +R
	string str59_a = "2548";
	string str59_b = "-17893";
	BigNum* bn59_a = convert(str59_a);
	BigNum* bn59_b = convert(str59_b);
	BigNum* res59 = add(bn59_a, bn59_b);
	string comeback59 = toString(res59);
	BOOST_CHECK(comeback59 == "-15345");
//	cout<<"comeback is: "<<comeback59<<endl;

	// CASE #3 -L  +  +R == +R - +L
	string str60_a = "-2548";
	string str60_b = "17893";
	BigNum* bn60_a = convert(str60_a);
	BigNum* bn60_b = convert(str60_b);
	BigNum* res60 = add(bn60_a, bn60_b);
	BOOST_CHECK(toString(res60) =="15345");

	// CASE #4  -L  +  -R == -(L + R)
	string str61_a = "-2548";
	string str61_b = "-17893";
	BigNum* bn61_a = convert(str61_a);
	BigNum* bn61_b = convert(str61_b);
	BigNum* res61 = add(bn61_a, bn61_b);
	BOOST_CHECK(toString(res61) =="-20441");
	
	//case #5
	
	//*********************************************************************************
	//                               TEST SUB
	//*********************************************************************************
	cout<<"testing 'Bignum* sub(BigNum* lbn, BigNum* rbn)'\n";
	
	/* 		+L - +R =    +L  -  +R
	 * 		+L - -R =    +L  +  +R
	 * 		-L - +R =  -(+L  +  +R)
	 * 		-L - -R =    +R  -  +L
	 */
	
	// CASE #1: +L - +R =    +L  -  +R
	string str62_a = "2548";
	string str62_b = "17893";
	BigNum* bn62_a = convert(str62_a);
	BigNum* bn62_b = convert(str62_b);
	BigNum* res62 = sub(bn62_a, bn62_b);
	string comeback62 = toString(res62);
	BOOST_CHECK(comeback62 == "-15345");
	// cout<<"comeback is: "<<comeback62<<endl;
	
	// CASE #2: +L - -R =    +L  +  +R
	string str63_a = "2548";
	string str63_b = "-17893";
	BigNum* bn63_a = convert(str63_a);
	BigNum* bn63_b = convert(str63_b);
	BigNum* res63 = sub(bn63_a, bn63_b);
	string comeback63 = toString(res63);
	BOOST_CHECK(comeback63 == "20441");
	// cout<<"comeback is: "<<comeback63<<endl;
	
	// CASE #3: -L - +R =  -(+L  +  +R)
	string str64_a = "-2548";
	string str64_b = "17893";
	BigNum* bn64_a = convert(str64_a);
	BigNum* bn64_b = convert(str64_b);
	BigNum* res64 = sub(bn64_a, bn64_b);
	string comeback64 = toString(res64);
	BOOST_CHECK(comeback64 == "-20441");
	// cout<<"comeback is: "<<comeback64<<endl;
	
	// CASE #4: -L - -R =    +R  -  +L
	string str65_a = "-2548";
	string str65_b = "-17893";
	BigNum* bn65_a = convert(str65_a);
	BigNum* bn65_b = convert(str65_b);
	BigNum* res65 = sub(bn65_a, bn65_b);
	string comeback65 = toString(res65);
	BOOST_CHECK(comeback65 == "15345");
	// cout<<"comeback is: "<<comeback65<<endl;


//*********************************************************************************
//                               TEST REPEATED ADD
//*********************************************************************************
	cout<<"testing, Bignum* repeated_add(int repeats, long rp, BigNum* lbn, BigNum* res)'\n";
	
	int i74 = 2;
	long ul74 = 3;
	BigNum* bn74 = convert("6");
	BigNum* bn74_res = repeated_add(i74, ul74, bn74);
	// cout<<"I'm back!"<<endl;
	// cout<<"the result from the test harness is: "<<toString(bn74_res)<<endl;
	string comeback74 = toString(bn74_res);
	BOOST_CHECK(comeback74 == "1200");
	// cout<<"comeback is: "<<comeback74<<endl;

	int i75 = 0;
	long ul75 = 1;
	BigNum* bn75 = convert("879667567344357092187664543");
	BigNum* bn75_res = repeated_add(i75, ul75, bn75);
	// cout<<"I'm back!"<<endl;
	// cout<<"the result from the test harness is: "<<toString(bn75_res)<<endl;
	string comeback75 = toString(bn75_res);
	BOOST_CHECK(comeback75 == "0");
	// cout<<"comeback is: "<<comeback75<<endl;

	int i76 = 9;
	long ul76 = 1;
	BigNum* bn76 = convert("123");
	BigNum* bn76_res = repeated_add(i76, ul76, bn76);
	// cout<<"I'm back!"<<endl;
	// cout<<"the result from the test harness is: "<<toString(bn76_res)<<endl;
	string comeback76 = toString(bn76_res);
	BOOST_CHECK(comeback76 == "1107");
	// cout<<"comeback is: "<<comeback76<<endl;
	
	int i77 = 1;
	long ul77 = 3;
	BigNum* bn77 = convert("6");
	BigNum* bn77_res = repeated_add(i77, ul77, bn77);
	// cout<<"I'm back!"<<endl;
	// cout<<"the result from the test harness is: "<<toString(bn77_res)<<endl;
	string comeback77 = toString(bn77_res);
	BOOST_CHECK(comeback77 == "600");
	// cout<<"comeback is: "<<comeback77<<endl;

//*********************************************************************************
//                               TEST MULT_ABS_DIRECT
//*********************************************************************************

	cout<<"Testing 'BigNum* mult_abs_direct(BigNum* lbn, BigNum* rbn);\n";
	
	BigNum* bn78_a = convert("25");
	BigNum* bn78_b = convert("4");
	BigNum* bn78_res = mult_abs_direct(bn78_a, bn78_b);
	string comeback78 = toString(bn78_res);
	BOOST_CHECK_MESSAGE(comeback78 == "100", "comeback is: "<<comeback78);
	
	vector<Mini_test*> vt;
	typedef vector<Mini_test*>::iterator vti;
	
	vt.push_back(new Mini_test("33765", "3", "101295"));
	vt.push_back(new Mini_test("0", "3234128374692784", "0"));
	vt.push_back(new Mini_test("1", "234463465", "234463465"));
	vt.push_back(new Mini_test("1", "234463465", "234463465"));
	vt.push_back(new Mini_test("234463465", "1", "234463465"));
	vt.push_back(new Mini_test("234463465", "0", "0"));
	vt.push_back(new Mini_test("1234162739", "12347812738647126349762", "15239210390187828610301341918118"));
	vt.push_back(new Mini_test("12830480", "20348", "261074607040"));
	vt.push_back(new Mini_test("10103947746", "1038475", "10492697135527350"));
	
	for(vti p = vt.begin(); p!=vt.end(); ++p){
		Mini_test* tmp = *p;
		BigNum* bn79_a = convert(tmp->left);
		BigNum* bn79_b = convert(tmp->right);
		BigNum* bn79_res = mult_abs_direct(bn79_a, bn79_b);
		string comeback79 = toString(bn79_res);
		BOOST_CHECK_MESSAGE(comeback79 == tmp->product, "\tcomeback is: "<<comeback79);
	}
	
	
	//*********************************************************************************
	//                               TEST MULT
	//*********************************************************************************
	cout<<"testing, BigNum* mult(BigNum* lbn, BigNum* rbn)'\n";
	cout << "Maximum value for int: " << numeric_limits<int>::max() << '\n';
	
	/* 		+L * +R =    +L  *  +R
	 * 		+L * -R =  -(+L  *  +R)
	 * 		-L * +R =  -(+L  *  +R)
	 * 		-L * -R =    +R  *  +L
	 */
	vt.clear();
	vt.push_back(new Mini_test("200", "2000", "400000"));
	vt.push_back(new Mini_test("1234534", "-1", "-1234534"));
	vt.push_back(new Mini_test("-234", "234463465", "-54864450810"));
	vt.push_back(new Mini_test("-9", "-234463465", "2110171185"));
	vt.push_back(new Mini_test("0", "234463465", "0"));
	vt.push_back(new Mini_test("-9", "0", "0"));
	vt.push_back(new Mini_test("-12341237846", "123046", "-1518539951998916"));
	

	for(vti p = vt.begin(); p!=vt.end(); ++p){
		Mini_test* tmp = *p;
		BigNum* bn79_a = convert(tmp->left);
		BigNum* bn79_b = convert(tmp->right);
		BigNum* bn79_res = mult(bn79_a, bn79_b);
		string comeback79 = toString(bn79_res);
//		cout<<"\tleft is: "<<tmp->left<<"\tright is: "<<tmp->right<<endl;
		BOOST_CHECK_MESSAGE(comeback79 == tmp->product, "\tcomeback is: "<<comeback79);
	}




	
	
	
	
	
	
		
}