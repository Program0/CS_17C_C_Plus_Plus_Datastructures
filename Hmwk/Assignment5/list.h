/* 
 * File:   list.h
 * Author: Marlo Zeroth
 * Created on October 5, 2015, 10:16 PM
 * This is the list.h file. It is the linked list class 
 * implemented by Marlo Zeroth as assignment 4 for CSC17C.
 * modified from SimpleVectorLList used in assignment 4 to 
 * implement first, last, prepend, append insertBefore, 
 * insertAfter, extract, assignment = operator, array 
 * operator [], and copy constructor.  * 
 */

#ifndef LIST_H
#define	LIST_H

#include "emptylist.h" // For throwing an empty list exceptions.

class List{

public:

    /******* Constructors and Destructor *******/

    // Default constructor
    List():size(0),head(0){}

    // Main constructor
    List(const int &input);

    // Copy constructor
    List(const List &obj);

    // Destructor
    ~List();

    /* Overloaded Operators */

    // Overload [] operator declaration
    int &operator[](const int & input) throw (EmptyList);

    // Overload [] operator declaration
    const int& operator[](const int & input) const throw (EmptyList);

    // Overload = operator declaration
    List& operator =(const List &input);

    /* Mutators and Accessors*/

    // Adds an input to the end of the list
    void append(const int &input);

    // Adds an input to the beginning of the list
    void prepend(const int &input);

    // Returns the element at the end of the vector
    int last();

    // Returns the element at the end of the vector
    int first();

    // Inserts an input before the element. If insertion
    // was successful returns true, false otherwise
    bool insertBefore(const int &entry, const int& input);

    // Inserts an input after the element. If insertion was
    // successful returns true, false otherwise
    bool insertAfter(const int &entry, const int& input);

    // Clears the elements in the list
    void extract();
    
    void clear();

    // Returns true if the list is empty, false otherwise
    bool empty();

    // Returns the size of the list
    int length() const {return size;}

private:

    // Node struct to hold data
    // and link individual links in the list
    struct Node{
        int data;
        Node *next;
    };

    Node *head;      // To point to the top of the vector
    int size;       // Size of the list
    void memError() const; // Handles memory allocation errors
    void subError() const; // Handles subscripts out of range
};

#endif	/* LIST_H */

