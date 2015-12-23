/* 
 * File:   priorityvertex.h
 * Author: super0
 *
 * Created on December 20, 2015, 9:56 PM
 */


#ifndef PRIORITYVERTEX_H
#define	PRIORITYVERTEX_H

#include "graph.h"
#include "vertex.h"

template<class T> class Vertex;
template<class T> class Graph;

// Class to aid in getting the shortest distance between vertices

class PriorityVertex {
    friend class Graph;
    friend class Vertex;
public:
    // Main constructor
    PriorityVertex(const Vertex& currentVertex, int currentCost, const Vertex& priorVertex);

    // Compares two priority vertices
    int compareTo(const PriorityVertex& that);
private:
    int cost; // Cost of this vertex on the path
    Vertex vertex; // Current vertex on the path
    Vertex previousVertex; // previous vertex on the path
};

/*PriorityVertex Definitions*/
// Main constructor

template<class T>
PriorityVertex::PriorityVertex(const Vertex& currentVertex, int currentCost, const Vertex& priorVertex) {
    vertex = currentVertex;
    cost = currentCost;
    previousVertex = priorVertex;
}

// Compares two priority vertices

template<class T>
PriorityVertex::compareTo(const PriorityVertex& that) const {
    return (cost - that.cost);
}



#endif	/* PRIORITYVERTEX_H */