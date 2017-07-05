#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>

class Edge {
public:
    // start vertex's label
    int start;
    // end vertex's label
    int end;
    // the weight of this edge
    int weight;
    
    Edge(int start, int end, int weight = 0);
};

#endif /* Edge_hpp */
