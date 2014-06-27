# basic build for homework 6
CC=xcrun c++

CFLAGS=-c 

all: a_sets
	
a_sets: Dev_main.o treeset.o hashset.o
	$(CC) Dev_main.o treeset.o hashset.o -o a_sets
	
Dev_main.o: Dev_main.cpp
	$(CC) $(CFLAGS) Dev_main.cpp
	
hashset.o: hashset.cpp hashset.h
	$(CC) $(CFLAGS) hashset.cpp
	
treeset.o: treeset.cpp treeset.h
	$(CC) $(CFLAGS) treeset.cpp
	
clean:
	rm -rf *.o *.out a_sets
