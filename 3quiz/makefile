# basic build for homework 6
CC=xcrun c++
CFLAGS=-c 

all: a_cat_shack
	
a_cat_shack: cat.o person.o cat_stuff.o
	$(CC) cat.o person.o cat_stuff.o -o a_cat_shack
	
cat.o: cat.cpp cat.h
	$(CC) $(CFLAGS) cat.cpp

person.o: person.cpp person.h
	$(CC) $(CFLAGS) person.cpp

cat_stuff.o: cat_stuff.cpp
	$(CC) $(CFLAGS) cat_stuff.cpp

clean:
	rm -rf *.o a_cat_shack
