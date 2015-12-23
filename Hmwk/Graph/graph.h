/* 
 * File:   graph.h
 * Author: super0
 *
 * Created on December 20, 2015, 10:20 AM
 */

#ifndef GRAPH_H
#define	GRAPH_H

#include "pairlist.h"
#include "singlylist.h"
#include "stack.h"
#include "priorityqueue.h"

#include "vertex.h"

template<class T>
class Graph {
public:
    Graph();
    // Main/Default constructor

    bool addVertex(const T& vertex);
    // Adds a vertex to the graph

    bool addEdge(T begin, T end, int weight);
    // Adds an edge in the graph. 

    void clear();
    // Empties the graph

    int getShortestDistance(const T& begin, const T& end, Stack<T>& path);

    bool hasEdge(const T& begin, const T& end) const;
    // Returns whether the graph has the given edges

    int edgeCost(const T& begin, const T& end) const;

    bool containsVertext(const T& vertex) const;

    bool isEmpty() const;

private:

    // Utility functions
    void noSuchVertex();


    void resetVertices();
    // Resets the vertices

    // Member variables
    PairList<T, Vertex<T>*> vertices;
    int edgeCount;

};

template<class T>
Graph<T>::Graph() {
    edgeCount = 0;
}

/**
 * Adds a vertex to the graph. Returns either true if the vertex was added 
 * successfully returns false if the vertex already exists in the graph.
 */

template<class T>
bool Graph<T>::addVertex(const T& vertex) {
    // Test if the vertex is in the graph
    bool found = vertices.containsKey(vertex);
    if (!found) {
        // If it is not then add it and return that it was added
        Vertex<T>* myVertex = new Vertex<T>(vertex);
        vertices.insert(vertex, myVertex);
        return true;
    }
    // If it is not, return that it was not added
    return false;
}

/**
 * Adds an edge to the graph. Returns true if successful, false otherwise
 */
template<class T>
bool Graph<T>::addEdge(T begin, T end, int weight) {
    // To determine if the connection was successful;
    bool result = false;


    // Get the vertices associate with begin and end
    Vertex<T> *beginVertex = vertices.at(begin);
    Vertex<T> *endVertex = vertices.at(end);
    // If both begin and end are in the graph we can connect them
    if (beginVertex != NULL && endVertex != NULL) {
        result = beginVertex.connect(endVertex, weight);
    }
    // If successful update the edge count for the graph
    if (result) {
        edgeCount++;
    }
    return result;
}

/**
 * Empties the graph
 */
template<class T>
void Graph<T>::clear() {
    vertices.clear();
    edgeCount = 0;
}

/**
 * Returns whether the pass vertices have an edge
 */
template<class T>
bool Graph<T>::hasEdge(const T& begin, const T& end) const {
    bool found = false;
    Vertex<T> *beginVertex = vertices.at(begin);
    Vertex<T> *endVertex = vertices.at(end);
    // If both begin and end are in the graph go through begins neighbors
    // to see if any them are end.
    if (beginVertex != NULL && endVertex != NULL) {
        typename SinglyList<Vertex<T>*>::iterator neighbors = beginVertex.edgeList.begin();
        typename SinglyList<Vertex<T>*>::iterator finish = beginVertex.edgeList.end();
        while (!found && neighbors != finish) {
            // Get the next neighbor to test
            Vertex<T>* nextNeighbor = *(++neighbors);
            if (nextNeighbor.equals(endVertex)) {
                found = true;
            }
        }
    }

    return found;
}

/**
 * Returns the cost associated with an edge
 */
template<class T>
int Graph<T>::edgeCost(const T& begin, const T& end) const {
    int cost = 0;
    Vertex<T> *beginVertex = vertices.at(begin);
    Vertex<T> *endVertex = vertices.at(end);
    // If both begin and end are in the graph go through begins neighbors
    // to see if any them are end.
    if (beginVertex != NULL && endVertex != NULL) {
        SinglyList<Edge>::iterator i = beginVertex->edgeList.begin();
        SinglyList<Edge>::iterator finish = beginVertex->edgeList.end();
        
        for (i;i!=finish;i++) {
            if ((endVertex)) {
                cost = edge.weight;
            }
        }
    }
    // Return the cost of this edge
    return cost;
}

/**
 * Returns whether the graph contains the pass vertex
 */
template<class T>
bool Graph<T>::containsVertext(const T& vertex) const {
    return vertices.containsKey(vertex);
}

/**
 * Returns whether the graph is empty
 */
template<class T>
bool Graph<T>::isEmpty() const {
    // If the list of vertices is empty, we have an empty graph
    return vertices.isEmpty();
}

/**
 * Returns the shortest path in the graph between two vertices
 */

template<class T>
int Graph<T>::getShortestDistance(const T& begin, const T& end, Stack<T>& path) {
    // Reset all the vertices to get a new path
    resetVertices();
    // Flag to set once a path is found or we traverse the whole graph
    bool done = false;
    // Holds the vertices that occur along the path from begin to end
    PriorityQueue<PriorityVertex> priorityQueue;
    // Create vertices from begin to end
    Vertex<T> *beginVertex = vertices.at(begin);
    Vertex<T> *endVertex = vertices.at(end);
    beginVertex.cost = 0;
    beginVertex.previousVertex = NULL;
    // Add the beginning to queue to start searching for the path
    PriorityVertex temp(beginVertex, 0, NULL);
    priorityQueue.enqueue(temp);
    // Will hold the vertex entry at the front of priority queue
    PriorityVertex *frontEntry = NULL;
    // Will hold the edges for
    //MyPriorityQueue<Edge> edges = new MyPriorityQueue<Edge>();

    while (!done && !priorityQueue.isEmpty()) {
        frontEntry = priorityQueue.front();
        priorityQueue.pop_front();
        Vertex<T>* frontVertex = frontEntry.vertex;
        std::cout << "frontVertex is: " << frontVertex.label
                << " visited: " << frontVertex.visited + " cost "
                << frontVertex.cost << "\n";

        // If the front vertex has not been visited
        if (!frontVertex.visited) {

            // Mark is as visited
            frontVertex.visited = true;
            frontVertex.cost = frontEntry.cost;
            frontVertex.previousVertex = frontEntry->previousVertex;

            // If the front vertex is equal to the end we are done!
            if (frontVertex.equals(endVertex)) {
                done = true;
            }// Otherwise we have to look through the neighboring vertices
                // of front vertex
            else {

                SinglyList<Vertex>::iterator neighbors = frontVertex.edgeList.begin();
                SinglyList<Vertex>::iterator finish = frontVertex.edgeList.end();
                while (neighbors != finish) {

                    Vertex nextNeighbor = *(++neighbors);

                    std::cout << "Neighbors of " << frontVertex.label
                            << " is " << nextNeighbor.label;
                    // Get the cost of this edge
                    int weightOfEdgeToNeighbor =
                            edgeCost(frontVertex->label, nextNeighbor->label);
                    // If this vertex has not been visited update
                    // its cost and the previous vertex reference
                    if (!nextNeighbor->visited) {
                        int nextCost = frontVertex.cost
                                + weightOfEdgeToNeighbor;
                        priorityQueue.enqueue(new PriorityVertex(
                                nextNeighbor, nextCost, frontVertex));
                    }
                } // end while
            }// end else
        } // end outer if
    } // end outer while

    int pathCost = endVertex.cost;
    path.push(endVertex.label);
    Vertex vertex = endVertex;
    while (vertex->previousVertex != NULL) {
        vertex = vertex->previousVertex;
        path.push(vertex->label);
    }

    return pathCost;
}

/**
 * Resets the vertices
 */
template<class T>
void Graph<T>::resetVertices() {
    PairList<T, Vertex<T>*>::iterator vertexIterator = vertices.begin();
    PairList<T, Vertex<T*>::iterator finish = vertices.end();
    while (vertexIterator != finish) {
        Vertex<T>* nextVertex = *(++vertexIterator);
        nextVertex->visited = false;
        delete nextVertex->previousVertex;
    }
}

#endif	/* GRAPH_H */

