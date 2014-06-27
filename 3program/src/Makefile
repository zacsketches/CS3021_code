# basic build for homework 6
CC=xcrun c++
CFLAGS=-c 

all: a_ordered_list
	
a_ordered_list: Pet.o prog3tester.o
	$(CC) Pet.o prog3tester.o -o a_ordered_list
	
prog3tester.o: prog3tester.cpp  OrderedList.h
	$(CC) $(CFLAGS) prog3tester.cpp

Pet.o: Pet.cpp
	$(CC) $(CFLAGS) Pet.cpp

clean:
	rm -rf *.o a_ordered_list a.out
