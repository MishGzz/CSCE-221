#include "Vertex.hpp"

// init your vertex here
Vertex::Vertex(int label) {
	this->label = label;
	startTime = 0;
	endTime = 0;
	notVisited = true;
	beingVisited = false;
	completelyVisited = false;
}

// connect this vertex to a specific vertex (adding edge)
void Vertex::connectTo(int end) {
	Edge e(this->label, end);
	edgeList.push_back(e);
	e.start = end;
}