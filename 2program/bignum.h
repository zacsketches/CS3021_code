/*
 * BigNum.cpp
 *
 *  Created on: Aug 13, 2011
 *      Author: twotani
 */

#include <sstream>
#include <iostream>
using namespace std;

const short MAX_NODE_VALUE = 1000; //node value ranges 0..999
const unsigned int MAX_DIGIT = 3; //number of digits to store in a node

struct BigNode {
	short	 data; //0 ... 999
	BigNode* link;
};


struct BigNum {
	short    sign; //+1 for positive and -1 for negative
	BigNode* mag;
};

//*********************************************************************************
//                               Modification 1 Additions
//
//	increment the passed BigNum, num.
//		- assume num is positive
//		- return num+1
//		- do not implement by calling add or add_abs
//
//*********************************************************************************
BigNum* incr(BigNum* num);

/*
 * Convert a given string representation to a BigNum and return it.
 * Allows leading zeroes and leading and trailing spaces, but does
 * not perform any error checking. The parameter val do not contain
 * invalid characters.
 *
 */
BigNum* convert(string val);

/*
 * Return the string representation of a given BigNum value. Assume
 * the passed BigNum is a valid value. This function is an inverse
 * of the convert function.
 */
string toString(BigNum* bigNum);


/*
 * Compare leftOperand and rightOperand
 *
 * Return  negative if L < R
 *         0        if L == R
 *         positive if L > R
 */
int compare(BigNum* leftOperand, BigNum* rightOperand);


/*
 * Add two BigNum numbers and returns the sum.
 *
 * 		+L  +  +R =    +L  +  +R
 * 		+L  +  -R =    +L  -  +R
 * 		-L  +  +R =    +R  -  +L
 * 		-L  +  -R =  -(+L  +  +R)
 */
BigNum* add(BigNum* leftOperand, BigNum* rightOperand);


/*
 * Subtract right operand from left operand and returns the difference.
 *
 * 		+L - +R =    +L  -  +R
 * 		+L - -R =    +L  +  +R
 * 		-L - +R =  -(+L  +  +R)
 * 		-L - -R =    +R  -  +L
 */
BigNum* sub(BigNum* leftOperand, BigNum* rightOperand);

/*
 * Multiply two operands and return their product.
 *
 * 		+L * +R =    +L  *  +R
 * 		+L * -R =  -(+L  *  +R)
 * 		-L * +R =  -(+L  *  +R)
 * 		-L * -R =    +R  *  +L
 */
BigNum* mult(BigNum* leftOperand, BigNum* rightOperand);

