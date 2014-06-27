/*
 * random_array.cpp
 *
 *  Created on: Jan 19, 2010
 *      Author: Localadmin
 */

#include <stdlib.h>
#include "random_array.h"

#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void initialize_random(int seed) {
	srand ( seed );
}

void create_array(int intArray[], int size) {
	// fill the array with unique numbers
	for (int i = 0; i < size; i++) {
		intArray[i] = i+1;
	}

	// shuffle the numbers into random order
	int j;
	for (int i = 0; i < size; i++) {
		j = rand() % size;
		swap(intArray[i], intArray[j]);
	}
}

void copy_array(int inputArray[], int outputArray[], int size){

	for (int i = 0; i < size; i++) {
		outputArray[i] = inputArray[i];
	}
}
