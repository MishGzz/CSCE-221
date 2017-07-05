#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <list>
#include <string>
#include <vector>

#include "Edge.hpp"
using namespace std;

class Vertex {
public:
    // the label of this vertex
    int label;
    // using a linked-list to manage its edges which offers O(c) insertion
    list<Edge> edgeList;
    // is the vertex visited in DFS
	bool notVisited = true;
	bool completelyVisited = false;
    // init your vertex here
    Vertex(int label);
	//Start and end times for DFS
	int startTime = 0;
	int endTime = 0;

	bool beingVisited = false;
    
    // connect this vertex to a specific vertex (adding edge)
    void connectTo(int end);

	bool indegreeZero = true;
};

#endif /* Vertex_hpp */
