# a simple makefile for compiling C++ files

CC= g++-4.7 -std=c++11

all: main.o SkipList.o
	$(CC) main.o SkipList.o -o main

SkipList.o: SkipList.cpp SkipList.h Node.h
	$(CC) -c SkipList.cpp

main.o: main.cpp SkipList.h
	$(CC) -c main.cpp

clean:
	/bin/rm -f *.o main
