//***********************************************************
// SimpleVector class implementd using a linked list by     *
// Marlo Zeroth as assignment 4 for CSC17C. Implement the   *
// assignment operator =, array operator [], copy
// constructor, getElementAt(), push(), and pull() functions*
//***********************************************************


#ifndef SIMPLEVECTORLIST
#define SIMPLEVECTORLIST

#include <emptyvector.h>        // For throwing an empty vector exceptions.

class LinkedList{

public:

    /******* Constructors and Destructor *******/

    // Default constructor
    LinkedList()
        {vectorSize = 0; head = 0;}

    // Main constructor
    LinkedList(const int &input);

    // Copy constructor
    LinkedList(const LinkedList &obj);

    // Destructor
    ~LinkedList();

    /* Overloaded Operators */

    // Overload [] operator declaration
    int &operator[](const int & input) throw (EmptyVector);

    // Overload [] operator declaration
    const int& operator[](const int & input) const throw (EmptyVector);

    // Overload = operator declaration
    LinkedList& operator =(const LinkedList &input);

    /* Mutators and Accessors*/

    // Adds an input to the vector
    void push(const int &input);

    // Returns the element at the end of the vector
    int pull();

    // Returns the size of the current vector
    int size() const {return vectorSize;}

private:

    // Node struct to hold data
    // and link individual chains.
    struct Node{
        int data;
        Node *next;
    };

    Node *head;      // To point to the top of the vector
    int vectorSize;  // Size of the vector
    void memError() const; // Handles memory allocation errors
    void subError() const; // Handles subscripts out of range
};


#endif // SIMPLEVECTORLIST

