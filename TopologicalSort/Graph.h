#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Vertex.hpp"
#include "Edge.hpp"

using namespace std; 

class Graph {
public:
	//vector<Edge*> edges;
	//vector<Vertex*> vertices;

	// we use a vector to store vertices in the graph
	// and use label (int) to be a subscript to access a vertex
	ifstream inputFile;
	vector<Vertex> vertices;
	Graph(string& inputPath);
	// build a graph according to the input file
	void buildGraph();
	// display the graph
	void displayGraph();
	// does it have cycles?
	bool DAG = true;
	// DFS
	list<Vertex> TOrder(Vertex& v);
	void DFS(Vertex& v);
	Vertex& findStart();
	//topological order
	list<Vertex> topologicalOrder;
	int timeTracker = 0;
};
#endif