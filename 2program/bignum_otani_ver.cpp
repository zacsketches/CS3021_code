/*
 * BigNum.cpp
 *
 *  Created on: Aug 13, 2011
 *      Author: twotani
 *
 *  NOTE: Not all functions are used in the main program. Several functions
 *        such as comparing, erasing and copying big numbers are mainly for
 *        internal use.
 */

#include "bignum.h"

//------- Helper Functions -------------//

/*
 * Return true if num is positive; otherwise, return false
 */
bool isPositive(BigNum* num){			// I S P O S I T I V E

	return num->sign > 0 ;
}

/*
 * Return true if num is negative; otherwise, return false
 */
bool isNegative(BigNum* num) {			// I S N E G A T I V E

	return num->sign < 0 ;
}

/*
 * Deallocate the nodes allocated to represent the number
 */
void clear(BigNum* number) {          // C L E A R

	BigNode* p = number->mag;
	BigNode* q;

	while (p != NULL) {

		q = p;
		p = p->link;

		delete q;
	}

	delete number;
}

/*
 * Create a copy of the number
 */
BigNum* copy(BigNum* number) {			// C O P Y

	BigNum* dup = new BigNum;
	BigNode *p, *q;

	dup->sign = number->sign;

	p = number->mag;
	q = new BigNode; //dummy first node
	dup->mag = q;

	while (p != NULL) {

		q->link = new BigNode;
		q = q->link;
		q->link = NULL;

		q->data = p->data;

		p = p->link;
	}

	q = dup->mag;
	dup->mag = q->link;

	delete q; //remove dummy first node

	return dup;
}

/*
 * Negate the sign of the number. Notice that we are not creating a full copy.
 * We are just changing the sign in a new BigNum struct.
 */
BigNum* neg(BigNum* number) {			// N E G

	BigNum * temp = new BigNum;
	temp->sign = -1 * number->sign;
	temp->mag = number->mag;

	return temp;
}

/*
 * Consider adding this helper function to add two positive big numbers
 */
BigNum* absAdd(BigNum* leftOperand, BigNum* rightOperand) {	// A B S A D D

	BigNum* sum;


	return sum;
}

/*
 * Consider adding this helper function to subtract the positive rightOperand
 * from the positive leftOperrand
 */
BigNum* absSub(BigNum* leftOperand, BigNum* rightOperand) { //A B S S U B

	BigNum* diff;


	return diff;
}

//---------------- E N D  Helper Functions ---------------------//

/**
 * This function is implemented for you to give you an inspiration
 * for implementing the remaining functions.
 */
string toString(BigNum* bigNum) {                 // T O S T R I N G
	stringstream ss;

	string result = "";
	string nodeVal;

	BigNode* p = bigNum->mag;

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

	if (bigNum->sign < 0) {
		result.insert(0, "-");
	}

	return result;
}


BigNum* convert(string val) {                 // C O N V E R T

	BigNum * result;


	return result;
}


int compare(BigNum* leftOperand, BigNum* rightOperand) {	// C O M P A R E

	int result;


	return result;
}



BigNum* add(BigNum* leftOperand, BigNum* rightOperand) {	// A  D  D

	BigNum *result;


	return result;
}


BigNum* sub(BigNum* leftOperand, BigNum* rightOperand) {	// S  U  B

	BigNum* result;


	return result;
}


BigNum* mult(BigNum* leftOperand, BigNum* rightOperand) {   // M  U  L  T

	BigNum* result;


	return result;
}

