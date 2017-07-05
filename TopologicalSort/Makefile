# a simple makefile for compiling C++ files

CC= g++-4.7 -std=c++11

all: main.o Graph.o Vertex.o Edge.o
	$(CC) main.o Graph.o Vertex.o Edge.o -o main

Edge.o: Edge.cpp Edge.hpp
	$(CC) -c Edge.cpp

Vertex.o: Vertex.cpp Vertex.hpp
	$(CC) -c Vertex.cpp

Graph.o: Graph.cpp Graph.h Vertex.hpp Edge.hpp
	$(CC) -c Graph.cpp

main.o: main.cpp Graph.h
	$(CC) -c main.cpp

clean:
	/bin/rm -f *.o main
