/*
 * BigNum.cpp
 *
 *  Created on: Aug 13, 2011
 *      Author: twotani
 *  Last modified on 5/15/2014 by Zac Staples, zhstaple@nps.edu
 *  CS3021, Programming assignment #2, including mod1 for increment function
 *
 */
#define DEBUG 0	
#define CONVERT_DEBUG 0		//set DEBUG to 1 for verbose debug to stdout
#define ADD_ABS_DEBUG 0		//set DEBUG to 1 for verbose debug to stdout
#define SUB_ABS_DEBUG 0		//set DEBUG to 1 for verbose debug to stdout
#define COMPARE_DEBUG 0		//set DEBUG to 1 for verbose debug to stdout
#define INCR_DEBUG 0		//set to 1 for verbose debug to stdout

#include "bignum.h"

//*********************************************************************************
//                               HELPER FUNCTIONS
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
// void clear(BigNum* number)
//		Purpose: 		release memory back to the free store
//		Algorithm:		provided by T. Otani
//		Input:			BigNum pointer
//		Output:			NA
//		Precondition:	BigNum pointer is not null
//		Postcondition:	memory released and object cleaned up
//********************************************************************
void clear(BigNum* number) { 
	BigNode* p = number->mag;
	BigNode* q;
	while (p != NULL) {
		q = p;
		p = p->link;
		delete q;
	}
	delete number;
}


//********************************************************************
// string trim_zeros(string val)
//		Purpose: 		trim leading zeros from val, preserve a + or - sign
//		Algorithm:		iterate through the string and trim all leading zeros
//		Input:			string val representing an arbitrarily long integer
//						with optional leading + or -
//		Output:			string with all leading zeros removed
//		Precondition:	none
//		Postcondition:	cannot return a NULL string.  Correct for the string
//						"000000" to return "0" instead of ""	
//********************************************************************
string trim_zeros(string val){
	typedef string::iterator it;
	string res;
	it p = val.begin();
	if(*p=='-' || *p=='+') {
		res += *p;
		++p;
	}
	//iterate over p until the first non-zero char is reached
	while (*p=='0'){
		++p;
	}
	//iterate over the ramaining chars until the end is reached and apend to
	//res
	while(p!=val.end()){
		res += *p;
		++p;
	}

	//cannot return a NUll string or just a sign
	if(res.size() == 1 && *res.begin()=='-' )
		res = "0";
	if(res.size() == 1 && *res.begin()=='+' )
		res = "0";
	if(res.size() == 0)
		res = "0";
		
	return res;
}

//********************************************************************
// int get_sign(string val)
//		Purpose: 		return the sign of a string representation of an int
//		Algorithm:		NA
//		Input:			string represenation of an int
//		Output:			1 or -1
//		Precondition:	val is all digits with a leading -, + or digit
//		Postcondition:	none
//********************************************************************
int get_sign(const string val){
	int res = 1;
	char ch = *val.begin();
	if (ch=='-')
		res = -1;
	return res;
}

//********************************************************************
// string trim_sign(string val)
//		Purpose: 		remove the sign character from a string rep of a number	
//		Algorithm:		user iterator positions to remove the first char
//		Input:			string representation of a number, only digits
//		Output:			string rep of a number without a leading sign
//		Precondition:	val contains only digits and a leading sign char
//		Postcondition:	val contains only digits
//********************************************************************
string trim_sign(string val){
	char ch = *val.begin();
	 if( (ch=='-') || (ch=='+') ) {
		val = string(val.begin()+1, val.end());	//get rid of the leading sign character
	}
	return val;
}

//******************************************************************************
// BigNode* make_node(const string tri_graph)
//		Purpose: 		create a new node and return a pointer to it
//		Algorithm:		convert the tri_graph to an int and build a node
//		Input:			string intended to become int data
//		Output:			a new BigNode with a NULL link
//		Precondition:	tri_graph will convert to int
//		Postcondition:	New Node created on Free Store
//******************************************************************************
BigNode* make_node(const string tri_graph){
	BigNode* result;
	result = new BigNode;
	
	int i;
	stringstream ss;
	ss << tri_graph;
	ss >> i;
	ss.clear();
	
	result->data = i;
	result->link = NULL;
	
	return result;	
}

//******************************************************************************
// string to_string(const int n)
//		Purpose: 		convert an integer to a string
//		Algorithm:		use stringstream to make conversion
//		Input:			int
//		Output:			string
//		Precondition:	valid int...not testing for int done in function
//		Postcondition:	none
//******************************************************************************
string to_string(const int n) {
	stringstream ss;
	ss << n;
	string res;
	ss >> res;
	
	return res;
}


//******************************************************************************
// BigNum* add_abs(BigNode* left, BigNode* right)
//		Purpose: 		mag of left and right
//		Algorithm:		iterate through each BigNode*->data and add/carryover as req'd
//		Input:			two non-Null BigNode*
//		Output:			a new BigNum*
//		Precondition:	none
//		Postcondition:	none
//******************************************************************************
BigNum* add_abs(BigNum* orig_lbn, BigNum* orig_rbn){
	BigNum* res;
	res = new BigNum;
	res->sign = 1; //abs results is always positive
	
	//create local copies so we don't alter the passed pointers
	BigNum* lbn = convert(toString(orig_lbn));
	BigNum* rbn = convert(toString(orig_rbn));

	int carryover = 0;
	
	//if right is longer than left, switch the pointers
	//this is necessary so the while loop below doesn't run off the end of the left
	//list while there are nodes to add to res in the right list
	if (toString(lbn).size() < toString(rbn).size()) {
		BigNum* temp = rbn;
		rbn = lbn;
		lbn = temp;
	}
	
	//get the magnitudes regardless of sign to work in absolute value terms
	BigNode* l_tri = lbn->mag;
	BigNode* r_tri = rbn->mag;
	
	// constants and local vars to link new nodes back into result
	BigNode* q = NULL;		//following pointer to link new Nodes
	int nodes_added = 0;	//keep track of how many nodes are added
	
	while(l_tri != NULL) {
		//calculate raw addition including carryover value
		int tmp = l_tri->data;
		if(r_tri != NULL)
		 	tmp += r_tri->data;
		tmp += carryover;			//add carryover from previous trigraph
		
		//adjust temp value for carryover
		if(tmp > 999) {
			carryover = 1;
			tmp = tmp % 1000;
		} else {
			carryover = 0;
		}

		//create a new node from the tmp value
		string tmp_str = to_string(tmp);
		BigNode* new_node = make_node(tmp_str);
		new_node->link = NULL;
		
		//if this is the first node added then link the result mag to it
		if(nodes_added==0){
			res->mag = new_node;
			if(ADD_ABS_DEBUG) cout<<"\tfirst node added!\n";
		}

		//if this is not the first node then link the previous node to the new one
		if(nodes_added != 0) {
			q->link = new_node;
			if(ADD_ABS_DEBUG) cout<<"\tlinked the node back to q\n";
		}
		
		//advance q to the last node added
		q = new_node; ;
	
		//increment our node counter
		++nodes_added;
		
		//walk the pointers
		l_tri = l_tri->link;
		if(r_tri != NULL)
			r_tri = r_tri->link;
	}
	//account for a 'hung' 1 in the carryover after all other addition is complete
	if(carryover){
		BigNode* final_node = make_node("1");
		final_node->link = NULL;
		q->link = final_node;	//
	}
	if(ADD_ABS_DEBUG) cout<<"\tcompleting add_abs routine\n";
	return res;
}

//******************************************************************************
// BigNum* sub_abs(BigNode* lbn, BigNode* rbn)
//		Purpose: 		abs diff betwen lbn and rbn
//		Algorithm:		iterate through each BigNode*->data and sub/borrow as req'd
//		Input:			two non-Null BigNode*
//		Output:			a new BigNum*
//		Precondition:	sign of lbn and rgn is ignored
//		Postcondition:	none
//******************************************************************************
BigNum* sub_abs(BigNum* orig_lbn, BigNum* orig_rbn){
	BigNum* result;
	result = new BigNum;
	result->sign = 1;	//expect positive, but switch if right > left
	
	//create local copies so we don't alter the passed pointers
	BigNum* lbn = convert(toString(orig_lbn));
	BigNum* rbn = convert(toString(orig_rbn));
	
	//compare for equality considering sign
	//return a BigNum with zero mag for equality
	if(SUB_ABS_DEBUG) cout<<"\tabout to test compare from sub_abs\n";
	int comparison = compare(lbn, rbn);
	if(SUB_ABS_DEBUG) cout<<"\tjust returned from compare...int is: "<<comparison<<endl;
	if (comparison == 0) {
		BigNode* tmp;
		tmp = new BigNode;
		tmp->data = 0;
		tmp->link = NULL;
		result->mag = tmp;
		return result;
	}
	
	//adjust the signs to positive for absolute value subraction
	lbn->sign = 1;
	rbn->sign = 1;
	//right mag greater than left mag then swap lbn and rbn and set sign to neg
	comparison = compare(lbn, rbn);
	if(comparison == -1){
		BigNum* tmp = rbn;
		rbn = lbn;
		lbn = tmp;
		result->sign = -1;
	}
	
	//subraction requires that you:
	//	1. compute the result of lbn->mag minus rbn->mag for the current trigraph (tri_low)
	//	2. compute the result of the next most significant trigraph (tri_high)
	// 	3. if tri_low is negative then tri_high and tri_low must be adjusted
	//  4. adjust for neg:
	//			a.	tri_high = tri_high -1
	//			b. 	tri_low = 1000 - abs(tri_low)
	//  5. add tri_low to the result BigNum
	//  6. advance the iteration
	
	//get the magnitudes regardless of sign to work in absolute value terms
	BigNode* l_tri = lbn->mag;
	BigNode* r_tri = rbn->mag;
	
	// constants and local vars to link new nodes back into result
	int tri_low = 0;		//default initialization for the intermediate value of the subtraction
	BigNode* q = NULL;		//following pointer to link new Nodes
	int nodes_added = 0;	//keep track of how many nodes are added
	
	
	while(l_tri != NULL) {
		//conduct the subraction
		tri_low = l_tri->data;
		if(r_tri != NULL)
		 	 tri_low -= r_tri->data;
		
		//adjust for negative...we know that l_mag > r_mag so there
		//must be another trigraph
		if(tri_low < 0) {
			//keep track of the current pointer
			BigNode* current = l_tri;
			
			//borrow 1 from tri_high
			l_tri = l_tri->link;
			l_tri->data -= 1;
			if(SUB_ABS_DEBUG) cout<<"l_tri data is: "<<l_tri->data<<endl;

			//now put the l_tri pointer back in the current location and adjust tri_low
			l_tri = current;
			tri_low = 1000+tri_low;
		}

		//create a new node from the tri_low value
		string tmp_str = to_string(tri_low);
		BigNode* new_node = make_node(tmp_str);
		new_node->link = NULL;

		//if this is the first node added then link the result mag to it
		if(nodes_added==0){
			result->mag = new_node;
			if(SUB_ABS_DEBUG) cout<<"\tfirst node added!\n";
		}

		//if this is not the first node then link the previous node to the new one
		if(nodes_added != 0) {
			q->link = new_node;
			if(SUB_ABS_DEBUG) cout<<"\tlinked the node back to q\n";
		}

		//advance q to the newest node in the list
		q = new_node;

		//increment our node counter
		++nodes_added;
		
		//walk the pointers
		l_tri = l_tri->link;
		if(r_tri != NULL)
			r_tri = r_tri->link;
	}
	
	//trim leading zeros and then return
	result = convert(trim_zeros(toString(result)));
		
	return result;	
}

//******************************************************************************
// BigNum* mult_abs_direct(BigNum* lbn, BigNum* rbn)
//		Purpose: 		multiply two BigNum*
//		Algorithm:		multiply in the same style as gradeschool arithmatic
//		Input:			two non-null BigNum pointers
//		Output:			BigNum*
//		Precondition:	none
//		Postcondition:	new BigNum* created on teh free store
//******************************************************************************
BigNum* mult_abs_direct(BigNum* lbn, BigNum* rbn){
	//the general idea is to conduct multiplication like in gradeschool:
	/*
              lbn               231
            x rbn             x  16
           ________        ___________
              res              1386
	                         + 2310
	                       __________  
	                           3696
	
	*/
	
	//set up the string for rbn and other
	//loop control variables	
	string rbn_str = toString(rbn);
	long rbn_size = rbn_str.size();
	long index = rbn_size -1;
//	cout<<"orig index is: "<<index<<endl;
	
	
	long place = 1;		//place value for the least sig digit
	BigNum* running_total = convert("0");
	
	//iterate over the digits in rbn
	while(index > -1){			//allow a 0 index
		char digit = rbn_str[index];
//		cout<<"digit is: "<<digit<<endl;
		
		stringstream ss;
		ss << digit;
		int repeats;
		ss >> repeats;
//		cout<<"repeats is: "<<repeats<<endl;		
		ss.clear();
		
		BigNum* digit_mult = repeated_add(repeats, place, lbn);
		running_total = add(running_total, digit_mult);
//		cout<<"running total is: "<<toString(running_total)<<endl;
		
		++place;
		--index;
//		cout<<"place and index are: "<<place<<'\t'<<index<<endl;
	}
	
	return running_total;
}

//******************************************************************************
// BigNum* repeated_add(int repeats, unsigned long repeats_place, BigNum* lbn)
//		Purpose: 		repeatedly add a number to itself
//		Algorithm:		looped addition
//		Input:			the number of times to loop, the place value of the result
//		Output:			BigNum*
//		Precondition:	lbn points to a valid BigNum
//						res points to allocated free store memory
//		Postcondition:	pointer to res returned with proper value in pointer loc.
//						Caller responsible for memory mgmt
//******************************************************************************
BigNum* repeated_add(int repeats, long repeats_place, BigNum* lbn) {
	BigNum* res;
	
	//zero case
	if(repeats == 0){
		res = convert("0");
		return res;
	}
		
	//times 1
	if(repeats ==1) {
		res = lbn;
	}
	
	//times 2 through 9
	if (repeats > 1){
		res = convert("0");
		while(repeats) {
			if(DEBUG)
				cout<<"in the while loop and res is: "<<toString(res)<<endl;
			res = add(res, lbn);
			--repeats;
		}
	}
	
	//pad zeros to reflect the place value of repeats in old school multiplication.
	//subract 1 from place to reflect that there are no pads for the ones place.
	repeats_place -= 1;
	string str = toString(res);
	while(repeats_place) {
		str += '0';
		--repeats_place;
	}
	
	res = convert(str);
	if(DEBUG)
		cout<<"returning from mult_add: "<<toString(res)<<endl;
	return res;
}


//*********************************************************************************
//                               PUBLIC FUNCTIONS
//							SIGNATURES FROM BIGNUM_H
//*********************************************************************************

//******************************************************************************
// BigNum* incr(BigNum* num)
//		Purpose: 		increment num by 1
//		Algorithm:		num + 1
//		Input:			BigNum* to positive value
//		Output:			num + 1
//		Precondition:	num is positive
//		Postcondition:	num is unchanged
//******************************************************************************
BigNum* incr(BigNum* num){
	BigNum* res;
	res = new BigNum;
	res->sign = 1; //result of incr is always positive since num is positive
	
	//create a local copy so we don't alter the passed pointers
	BigNum* orig = convert(toString(num));
	
	//create the number we are adding.
	BigNum* one = convert("1");

	//initialize the carryover variable
	int carryover = 0;
	
	//get the magnitudes
	BigNode* orig_mag = orig->mag;
	BigNode* one_mag = one->mag;
	
	// constants and local vars to link new nodes back into result
	BigNode* q = NULL;		//following pointer to link new Nodes
	int nodes_added = 0;	//keep track of how many nodes are added
	
	while(orig_mag != NULL) {
		//calculate the addition including carryover value
		int tmp = orig_mag->data;
		
		if(one_mag != NULL)
		 	tmp += one_mag->data;
		tmp += carryover;			//add carryover from previous trigraph
		
		//adjust temp value for carryover
		if(tmp > 999) {
			carryover = 1;
			tmp = tmp % 1000;
		} else {
			carryover = 0;
		}

		//create a new node from the tmp value
		string tmp_str = to_string(tmp);
		BigNode* new_node = make_node(tmp_str);
		new_node->link = NULL;
		
		//if this is the first node added then link the result mag to it
		if(nodes_added==0){
			res->mag = new_node;
			if(INCR_DEBUG) cout<<"\tfirst node added!\n";
		}

		//if this is not the first node then link the previous node to the new one
		if(nodes_added != 0) {
			q->link = new_node;
			if(INCR_DEBUG) cout<<"\tlinked the node back to q\n";
		}
		
		//advance q to the last node added
		q = new_node; ;
	
		//increment our node counter
		++nodes_added;
		
		//walk the pointers
		orig_mag = orig_mag->link;
		if(one_mag != NULL)
			one_mag = one_mag->link;
	}
	//account for a 'hung' 1 in the carryover after all other addition is complete
	if(carryover){
		BigNode* final_node = make_node("1");
		final_node->link = NULL;
		q->link = final_node;	//
	}
	if(INCR_DEBUG) cout<<"\tcompleting add_abs routine\n";
	return res;
}

//********************************************************************
// BigNum* convert(string val)
//		Purpose: 		convert an abitrarily long string into a linked list
//						of BigNodes with each data member in the range [0, 999]
//		Algorithm:		1. trim away leading zeros from the string
// 						2. get the sign and assign to the result
// 						3. trim away the string representation for the sign
// 						4. iterate through the string making a new node after 3 chars
// 						5. link the BigNodes and point result at the first BigNode
// 						5. return the result
//		Input:			string val
//		Output:			Pointer to a BigNum struct
//		Precondition:	val contains only digits preceeded by optional '-' or '+'
//		Postcondition:	free store memory taken for BigNum and BigNodes
//********************************************************************
BigNum* convert(string val) {                 
	
	BigNum * result;
	result = new BigNum;
	
	//deal with signs
	val = trim_zeros(val);	
	result->sign = get_sign(val);
	val = trim_sign(val);
	
	if(CONVERT_DEBUG) cout<<"val is: "<<val<<endl;
	
	//constants for tracking the iteration
	typedef string::reverse_iterator rit;
	string trigraph;	//a 
	int place = 0;		//keep track of how many chars we've added to the trigraph
	int nodes_added = 0;//keep track of how many nodes are added
	BigNode* q = NULL;	//q is a leading placeholder to link new Nodes

	//reverse iterate through the string making new nodes as required
	for(rit p = val.rbegin(); p != val.rend(); ++p)
	{
		trigraph.insert(trigraph.begin(), *p);
		++place;
		
		if(CONVERT_DEBUG) cout<<"p is: "<<*p<<"\tplace is: "<<place<<endl;
		if(CONVERT_DEBUG) cout<<"trigraph is: "<<trigraph<<endl;
		
		//if the trigraph is full or if it's the last character then add a Node
		if(place == MAX_DIGIT || p==(--val.rend())) {
			BigNode* tmp = make_node(trigraph);
			tmp->link = NULL;
			
			//if this is not the first node then link the previous node to the new one
			if(nodes_added != 0) {
				q->link = tmp;
				if(CONVERT_DEBUG) cout<<"\tlinked the node back to q\n";
			}
			//clear the trigraph and reset place if we just created a Node
			place = 0;
			trigraph = "";
			
			//advance q to the last node added
			q = tmp; ;
		
			//if this is the first node added then link the result mag to it
			if(nodes_added==0){
				result->mag = q;
				if(CONVERT_DEBUG) cout<<"\tfirst node added!\n";
			}
			++nodes_added;
		}
	}

	if(CONVERT_DEBUG) cout<<endl;		//create a more legible debug print out
	return result;
}

//******************************************************************************
// string toString(BigNum* bn)
//		Purpose: 		convert a BigNum opject into a string representation
//		Algorithm		1. get BigNode* to bn->mag
//						2. iterate following links in bn
//						3. pad each node if it needs leading zeros
//						4. insert the string value into the front of the result str
//						5. check the sign and insert '=' if required
//						6. return result
//		Input:			BigNum*
//		Output:			string with leading sign indictor
//		Precondition:	bn is not NULL
//		Postcondition:	none
//******************************************************************************
string toString(BigNum* bn){
	stringstream ss;

	string result = "";
	string nodeVal;

	BigNode* p = bn->mag;

	while (p != NULL) {

		ss << p->data;      //int (short) to string conversion
		nodeVal = ss.str();

		if (p->link != NULL) { //if this is not the last node, pad 0's
			while (nodeVal.size() < MAX_DIGIT) {
				nodeVal.insert(0, "0");
			}
		}

		result.insert(0, nodeVal);

		ss.str("");
		p = p->link;
	}

	if (bn->sign < 0) {
		result.insert(0, "-");
	}

	return result;
	
}

//******************************************************************************
// int compare(BigNum* leftOperand, BigNum* rightOperand)
//		Purpose: 		make relative comparisons with BigNum objects
//		Algorithm:		solve by cases:
//						case 1: obvious solution by diff't signs
//						case 2: both negative then compare by size then by
//								lexicographical order
//						case 3: both positive then compare by size then by 
//								lexicographical order
//		Input:			two BigNum pointers
//		Output:			return: -1 for left less than right
//								0 for equality
//								1 for left greater than right							
//		Precondition:	none
//		Postcondition:	none
//******************************************************************************
int compare(BigNum* left, BigNum* right) {
	int result;

	//obvious cases determined by sign
	if(left->sign == -1 && right->sign == 1)
		return -1;
	if(left->sign == 1 && right->sign == -1)
		return 1;
	
	//get signless strings to use in lexicographical comparisons
	string left_str = toString(left);
	left_str = trim_sign(left_str);
	int left_size = left_str.size();
	
	string right_str = toString(right);
	right_str = trim_sign(right_str);
	int right_size = right_str.size();
	
	//Both negative, then compare using lexicographical comparison
	if(left->sign == -1 && right->sign == -1) {
		//if the left string is longer then the right then it is further from zero to the left
		if(left_size != right_size) {
			if(left_size > right_size) result = -1;
			if(left_size < right_size) result = 1;
		}
		if(left_size == right_size) {
			if(COMPARE_DEBUG) cout<<"\tboth negative and the two size are equal\n";			
			if(left_str > right_str) result = -1; 	    //larger val is further from zero and a smaller value
			if(left_str < right_str) result = 1;		//small val is closer to zero and a larger value
			if(left_str == right_str) result = 0;
		}
	} // close case where both BigNum objects are negative
	
	//Both positive, then compare starting with most significant digit
	if(left->sign == 1 && right->sign == 1) {
		//if the left string is longer then the right then it is further from zero to the right
		if(left_size != right_size) {
			if(left_size > right_size) result = 1;
			if(left_size < right_size) result = -1;
		}
		if(left_size == right_size) {			
			if(left_str > right_str) result = 1; 	    //larger val is further from zero and a smaller value
			if(left_str < right_str) result = -1;		//small val is closer to zero and a larger value
			if(left_str == right_str) result = 0;
		}
	} // close both positive

	return result;
}


//******************************************************************************
// BigNum* add(BigNum* lbn, BigNum* rbn)
//		Purpose: 		add to BigNum objects together
//		Algorithm:		Use add_abs and sub_abs to support four cases
//		Input:			two non-null BigNum* objects
//		Output:			BigNum*
//		Precondition:	none
//		Postcondition:	returns a BigNum* to memory on the free store
//******************************************************************************
BigNum* add(BigNum* lbn, BigNum* rbn){
	BigNum* res;
	
	// CASE 1 +L  +  +R
	if(lbn->sign == 1 && rbn->sign == 1) {
		res = add_abs(lbn, rbn);
	}
	
	// CASE #2: +L + -R == +L - +R
	if(lbn->sign == 1 && rbn->sign == -1) {
		res = sub_abs(lbn, rbn);
	}
	
	// CASE #3 -L  +  +R == +R - +L
	if(lbn->sign == -1 && rbn->sign == 1) {
		res = sub_abs(rbn, lbn);
	}
	
	// CASE #4  -L  +  -R == -(L + R)
	if(lbn->sign == -1 && rbn->sign == -1) {
		res = add_abs(rbn, lbn);
		res->sign = -1;
	}
	
	return res;
}

//******************************************************************************
// BigNum* sub(BigNum* lbn, BigNum* rbn)
//		Purpose: 		subtract rbn from lbn:  lbn - rbn
//		Algorithm:		Use add_abs and sub_abs to support four cases
//		Input:			to non-null BigNum pointers
//		Output:			BigNum*
//		Precondition:	none
//		Postcondition:	returns a BigNum* to memory on the free store
//******************************************************************************
BigNum* sub(BigNum* lbn, BigNum* rbn){
	BigNum* res;
	
	// CASE #1: +L - +R =    +L  -  +R
	if(lbn->sign == 1 && rbn->sign == 1) {
		res = sub_abs(lbn, rbn);
	}
	
	// CASE #2: +L - -R =    +L  +  +R
	if(lbn->sign == 1 && rbn->sign == -1) {
		res = add_abs(lbn, rbn);
	}
	
	// CASE #3: -L - +R =  -(+L  +  +R)
	if(lbn->sign == -1 && rbn->sign == 1) {
		res = add_abs(lbn, rbn);
		res->sign = -1;
	}
	
	// CASE #4: -L - -R =    +R  -  +L
	if(lbn->sign == -1 && rbn->sign == -1) {
		res = sub_abs(rbn, lbn);
	}
	
	return res;
}

//******************************************************************************
// BigNum* mult(BigNum* lbn, BigNum* rbn)
//		Purpose: 		multiply two arbitrarily long BibNum objects
//		Algorithm:		add in loop
//		Input:			to non-NULL BigNum pointers
//		Output:			BigNum*
//		Precondition:	none
//		Postcondition:	creates a BigNum object on the free store
//******************************************************************************
BigNum* mult(BigNum* lbn, BigNum* rbn){
	BigNum* res;
	
	// CASE #1: +L * +R =    +L  *  +R
	if(lbn->sign == 1 && rbn->sign == 1) {
		res = mult_abs_direct(lbn, rbn);
	}
	
	// CASE #2: +L * -R =  -(+L  *  +R)
	if(lbn->sign == 1 && rbn->sign == -1) {
		//get right abs value
		string rbn_copy = toString(rbn);
		rbn_copy = trim_sign(rbn_copy);
		BigNum* rbn_abs = convert(rbn_copy);
		
		res = mult_abs_direct(lbn, rbn_abs);
		res->sign = -1;
	}
	
	// CASE #3: -L * +R =  -(+L  *  +R)
	if(lbn->sign == -1 && rbn->sign == 1) {
		//get left abs value
		string lbn_copy = toString(lbn);
		lbn_copy = trim_sign(lbn_copy);
		BigNum* lbn_abs = convert(lbn_copy);
		
		res = mult_abs_direct(lbn_abs, rbn);
		res->sign = -1;
	}
	
	// CASE #4: -L * -R =    +R  *  +L
	if(lbn->sign == -1 && rbn->sign == -1) {
		//get right abs value
		string rbn_copy = toString(rbn);
		rbn_copy = trim_sign(rbn_copy);
		BigNum* rbn_abs = convert(rbn_copy);
		
		//get left abs value
		string lbn_copy = toString(lbn);
		lbn_copy = trim_sign(lbn_copy);
		BigNum* lbn_abs = convert(lbn_copy);
		
		res = mult_abs_direct(lbn_abs, rbn_abs);
	}
	
	//catch case where zero comes back with negative sign
	res = convert(toString(res));

	return res;
}










