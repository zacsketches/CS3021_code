# basic build for homework 6
CC=xcrun c++
CFLAGS=-c 

all: a_HW6
	
a_HW6: student.o HW6.o
	$(CC) student.o HW6.o -o a_HW6
	
student.o: student.cpp
	$(CC) $(CFLAGS) student.cpp

HW6.o: HW6.cpp
	$(CC) $(CFLAGS) HW6.cpp

clean:
	rm -rf *.o a_HW6
