#include "Graph.h"
#include "Vertex.hpp"
#include "Edge.hpp"

Graph::Graph(string& inputPath) {

	inputFile.open(inputPath);
	if (!inputFile.good()) {
		cerr << "There was an error opening the document." << endl;
	}
	else {

		int label;
		vector<int> data;

		while (inputFile >> label) {
			data.push_back(label);
		}
		//int elem;
		//Building graph
		for (int i = 0; i < data.size(); i++) {
			if (data.at(i) != -1) {
				Vertex v(data.at(i));//adding vertex
				vertices.push_back(v);
				int newLabel = 0;
				int start = data.at(i);
				while (data.at(i + 1) != -1) {
					newLabel = data.at(i + 1);
					(vertices.at(vertices.size() - 1)).connectTo(newLabel);
					i++;
				}
			}
		}
		cout << "Displaying Graph" << endl;
		displayGraph();
		TOrder(findStart());
	}
}

// build a graph according to the input file
void Graph::buildGraph() { // built the graph in the constructor

}


// display the graph
void Graph::displayGraph() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << vertices.at(i).label;
		for (list<Edge>::iterator it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
			int v = it->end;
			cout << "->" << v;
		}
		cout << endl;
	}
}

list<Vertex> Graph::TOrder(Vertex& v) { // begining the DFS process after finding a starting point
	if (DAG) {

		timeTracker++; // keeps track of the time
		v.startTime = timeTracker;
		DFS(v); // continue the DFS process with DFS function
		timeTracker++;
		v.completelyVisited = true;
		v.endTime = timeTracker;
		topologicalOrder.push_front(v);

		if (DAG) { // if it has no cycles
			cout << "Topological Order: ";
			for (list<Vertex>::iterator it = topologicalOrder.begin(); it != topologicalOrder.end(); it++) {
				int a = it->label;
				int start = it->startTime;
				int end = it->endTime;
				if (it == topologicalOrder.begin()) {
					cout << a << "[" << start << "/" << end << "]";
				}
				else {
					cout << ", " << a << "[" << start << "/" << end << "]";
				}
			}
		}
		else {//was not a DAG and contained a cycle
			cout << "Not a DAG. Has no topological order" << endl;
		}
		cout << endl;
		return topologicalOrder;
	}
	else {
		cout << "Not a DAG" << endl;
		return topologicalOrder;
	}
}
void Graph::DFS(Vertex& v) { // continues the DFS process recursively
	
	v.notVisited = false;// change visited values
	v.beingVisited = true;
	for (list<Edge>::iterator it = v.edgeList.begin(); it != v.edgeList.end(); it++) {
		int index = 0;
		if (vertices[index].edgeList.begin() == vertices[index].edgeList.end()) { // if it has no children
			for (int i = 1; i < vertices.size(); i++) {
				if (vertices.at(i).label == it->start) {
					index = i;
					break;
				}
			}
			break;
		}
		else {
			for (int i = 1; i < vertices.size(); i++) { //locate the exact vertex in the vertices
				if (vertices.at(i).label == it->end) {
					index = i;
					break;
				}
			}
		}
		if (vertices[index].notVisited) { //check if the vertex is visited
			timeTracker++;
			vertices[index].startTime = timeTracker; // update start time
			DFS(vertices[index]); //recursively check children if they have not been visited
			timeTracker++;
			vertices[index].endTime = timeTracker;//update end time
			topologicalOrder.push_front(vertices[index]);
		}
		else if(vertices[index].beingVisited) { //encountered a vertex that is already being visited, therefore there  is a cycle
			DAG = false;
		}
	}
	v.beingVisited = false;//once it breaks out of recursion we know that it has been completely visited.
	v.completelyVisited = true;
}

Vertex& Graph::findStart() { // finds the starting point
	for (int i = 0; i < vertices.size(); i++) {
		int label = vertices.at(i).label;
		for (int j = 0; j < vertices.size(); j++) {//checks the neighbors of all edges to determine if there is one with indegree zero
			for (list<Edge>::iterator it = vertices.at(j).edgeList.begin(); it != vertices.at(j).edgeList.end(); it++) {
				if (it->end == label) {
					vertices.at(i).indegreeZero = false;
				}
			}
		}
	}
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i).indegreeZero = true) { //return the starting vertex
			return vertices.at(i);
		}
	}
	DAG = false; //did not find a starting vertex, therefore this graph is not a dag
	return vertices.at(0);
}