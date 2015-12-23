/* 
 * File:   edge.h
 * Author: super0
 *
 * Created on December 20, 2015, 9:52 PM
 */

#ifndef EDGE_H
#define	EDGE_H

#include "graph.h"
#include "vertex.h"



/*Edge definitions*/
// Main construcor

template<class T>
Edge::Edge(const Vertex<T>& vertex, int weight) {
    this->vertex = vertex;
    this->weight = weight;
}

// Compares the passed edge with this edge

template<class t>
int Edge::compareTo(const Edge& that) const {
    return (weight - that.weight);
}

#endif	/* EDGE_H */

