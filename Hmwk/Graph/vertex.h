/* 
 * File:   vertex.h
 * Author: super0
 *
 * Created on December 20, 2015, 10:59 AM
 */

#ifndef VERTEX_H
#define	VERTEX_H

#include "singlylist.h"
#include "sstream"
//#include "graph.h"

template<class T>
class Vertex {
    //friend class Graph<T>;
private:
    // Class to aid in getting the shortest distance between vertices

    class PriorityVertex {
        //friend class Graph<T>;
        friend class Vertex;
    public:
        // Main constructor
        PriorityVertex(const Vertex& currentVertex, int currentCost, const Vertex& priorVertex);

        // Compares two priority vertices

        int compareToPVertex(const PriorityVertex& that) const {
            return (cost - that.cost);
        };
    private:
        int cost; // Cost of this vertex on the path
        Vertex *vertex; // Current vertex on the path
        Vertex *previousVertex; // previous vertex on the path
    };

    class Edge {
        //friend class Graph<T>;
        friend class Vertex;
    public:
        // Main constructor
        Edge(const Vertex& vertex, int);

        // Compares two edges

        int compareTo(const Edge& that) const {
            return (weight - that.weight);
        };

        // Sets the weight

        void setWeight(int newWeight) {
            weight = newWeight;
        }

        // Returns the weight

        int getWeight()const {
            return weight;
        }

    private:
        // Weight and vertex of this edge
        Vertex *vertex;
        int weight;
    };

    // Vertex member variables
    T label;
    bool visited;
    int cost;
    SinglyList<Edge> edgeList;
    Vertex *previousVertex;

public:

    // Default constructor

    Vertex() : visited(false), cost(0) {
    }

    // Main constructor
    Vertex(const T& newLabel);

    // Copy constructor
    Vertex(const Vertex<T>& obj);

    // Destructor
    //~Vertex();

    // Assignment operator
    Vertex<T>& operator=(const Vertex<T>& obj);

    // Assignment operator    

    // Connects two vertices        
    bool connect(const Vertex<T>& end, const int& weight);

    // Returns whether this vertex has a neighbor
    bool hasNeighbor(const Vertex<T>& vertex);

    // Compares two vertices

    int compareVertexTo(const Vertex<T>& that) const {
        return (label == that.label);
    }

    // Returns whether two vertices are equal
    bool equals(const Vertex<T>& vertex);

    std::string vertexToString() const;

    // Sets visited to true

    void visit() {
        visited = true;
    }

    // Sets visited to false

    void unvisit() {
        visited = false;
    }

    // Returns whether this vertex has been visited

    bool isVisited()const {
        return visited;
    }

    // Sets the label

    void setLabel(const std::string& s) {
        label = s;
    }

    // Returns the vertex label

    std::string getLabel()const {
        return label;
    }

    // Sets the cost

    void setCost(const int& newCost) {
        cost = newCost;
    }

    // Returns the cost

    int getCost() const {
        return cost;
    }

};

template<class T>
Vertex<T>& Vertex<T>::operator=(const Vertex<T>& obj) {
    label = obj.label;
    cost = obj.cost;
    visited = obj.visited;
    return *this;
}

/*Edge definitions*/
// Main construcor

template<class T>
Vertex<T>::Edge::Edge(const Vertex<T>& newVertex, int newWeight) {
    vertex = newVertex;
    weight = newWeight;
}

/*PriorityVertex Definitions*/
// Main constructor

template<class T>
Vertex<T>::PriorityVertex::PriorityVertex(const Vertex<T>& currentVertex, int currentCost, const Vertex<T>& priorVertex) {
    vertex = currentVertex;
    cost = currentCost;
    previousVertex = priorVertex;
}

/*Vertex definitions*/

// Main constructor

template<class T>
Vertex<T>::Vertex(const T& newLabel) {
    label = newLabel;
    visited = false;
    previousVertex = NULL;
}

// Connects two vertices

template<class T>
bool Vertex<T>::connect(const Vertex<T>& end, const int& weight) {
    bool result = false;
    // If the end vertex is not equal to the current vertex
    // we can create an edge
    if (!equals(end)) {
        // Now we just need to make sure this end vertex is unique
        bool duplicate = false;

        typename SinglyList<Edge>::iterator neighbors = edgeList.begin();
        typename SinglyList<Edge>::iterator finish = edgeList.end();
        // Iterate through this vertex neighbors and check each
        // to see if end is one the neighbors
        while (!duplicate && neighbors != finish) {

            Vertex *nextNeighbor = (*neighbors)->vertex;
            if (end.label == nextNeighbor->label) {
                duplicate = true;
            }
        }
        // If it is not a duplicate just connect it.
        if (!duplicate) {
            Edge newEdge(end, weight);
            edgeList.append(newEdge);
            result = true;
        }
    }
    return result;
}

// Returns whether a vertex has neighbors

template<class T>
bool Vertex<T>::hasNeighbor(const Vertex<T>& vertex) {
    return !edgeList.isEmpty();
}

template<class T>
bool Vertex<T>::equals(const Vertex<T>& that) {
    return (label == that.label);
}

// Returns a string of the vector contents

template<class T>
std::string Vertex<T>::vertexToString() const {
    std::string output;
    std::stringstream s;

    s << "Label:" << label << " Cost: " << cost << " Visited: " << ((visited) ? "true\n" : "false\n");

    // Create a strip and return it.
    output = s.str();
    return output;
}

// end Vertex class

#endif	/* VERTEX_H */

