/*
 * File:   stack.h
 * Author: Marlo Zeroth
 * This is a template class implementing a stack data structure.
 *
 * Created on November 4, 2015, 4:19 PM
 */

#ifndef STACK_H
#define	STACK_H

#include <cstdlib>
#include <string>
#include <sstream>

#include "empty.h"

template<class T>
class Stack {
private:
    // Internal struct class to hold data and point to other nodes in stack

    struct Node {
        T data;
        Node *next;
    };

    /*Member Variables*/
    Node *first;
    unsigned int size;

    /*Utility functions*/
    void memError()const;
    // For generating a message if there is a problem allocating memory

public:

    /*Constructors and Destructor*/

    // Default constructor
    Stack();
    // Creates an empty stack.

    // Main constructor
    Stack(const T &entry);
    // Precondition: entry is not null
    // Postcondition: Creates a stack object with the parameter
    // at the top of the stack.

    // Copy constructor
    Stack(const Stack &obj);

    // Overloaded assignment operator
    Stack<T>& operator=(const Stack<T>& obj);

    ~Stack();
    // Deallocates memory used for the stack object

    /*Accessors and Mutators*/

    void push(const T &entry);
    // Precondition: Entry is not null
    // Postcondition: Adds an entry to the top of the stack.

    void pop()throw (Empty);
    // Precondition: The stack is not empty.
    // Postcondition: Returns and removes the element at the top of
    // the stack.

    T& top() throw (Empty);
    // Precondition: The stack is not empty.
    // Postcondition: Returns a reference without removing the top element of the stack.

    T const& top() const throw (Empty);
    // Precondition: The stack is not empty.
    // Postcondition: Returns a const reference without removing the top element of the stack.

    bool isEmpty() const;
    // Postcondition: Returns whether the stack is empty

    void clear();
    // Precondition: The stack is not empty.
    // Postcondition: Removes all elements from the stack.

    unsigned int length() {
        return size;
    }
    // Returns the size of the stack.

    std::string toString()const;
    // Precondition: The stack is not empty.
    // Postcondition: Returns a string with the stack contents.
};

/*Constructors and Destructor Implementation*/

// Creates an empty stack object. Does not allocate memory.

template<class T>
Stack<T>::Stack() {
    // Initialize to null
    size = 0;
    first = NULL;
}

// Main constructor. Creates a stack object with the passed entry. Allocates memory.

template<class T>
Stack<T>::Stack(const T &entry) {
    // Create a new link in the stack and add the entry
    // at the front/top
    Node *link;
    // Attempt to allocate memory
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    // Set its data member and pointers
    link->data = entry;
    link->next = NULL;
    first = link;
    size++;
}

// Copy constructor. Creates a copy of the passed object.

template<class T>
Stack<T>::Stack(const Stack<T>& obj) {
    if (!obj.isEmpty()) {
        size = 0;
        first = NULL;
        for (Node *cursor = obj.first; cursor != NULL; cursor = cursor->next) {
            push(cursor->data);
        }

        // Node following code to reverse contents was found at:
        // http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
        Node *result = NULL;
        Node *current = first;
        Node *next;

        while (current != NULL) {
            next = current->next; // Store the address of the next node

            current->next = result; // Swap the addresses of the current and next node
            result = current;

            current = next; // Advance to the next node
        }

        first = result;

    } else {
        size = 0;
        first = NULL;
    }
}

// Overloaded assignment operator

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& obj) {
    if (this != &obj) {
        clear();
        Node *cursor;
        // We insert the contents in reverse order
        for (cursor = obj.first; cursor != NULL; cursor = cursor->next) {
            push(cursor->data);
        }
        // Node following code to reverse contents was found at:
        // http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
        Node *result = NULL;
        Node *current = first;
        Node *next;

        while (current != NULL) {
            next = current->next; // Store the address of the next node

            current->next = result; // Swap the addresses of the current and next node
            result = current;

            current = next; // Advance to the next node
        }
        // Now set the first node address
        first = result;
    }
    return *this;
}

// Destructor

template<class T>
Stack<T>::~Stack() {
    // Iterate through the stack
    while (first) {
        Node * cursor = first;
        // Go to the next node
        first = first->next;
        // Deallocate the current node
        delete cursor;
    }
    size = 0;
}
/*Mutators and Accessors Implementation*/

// Adds an entry to the top of the stack. Allocates memory.

template<class T>
void Stack<T>::push(const T &entry) {
    // Create a new link in the stack and add the entry
    // at the front/top
    Node *link;
    // Attempt to allocate memory
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    // Set its data member and pointers
    link->data = entry;
    link->next = first;
    first = link;
    size++;
}

// Removes and returns the top element of the stack. Deallocates memory.

template<class T>
void Stack<T>::pop() throw (Empty) {
    if (first) {
        Node *cursor = first; // To deallocate later

        // Set top to be the next node.
        first = first->next;

        // Deallocate memory and decrease the size
        delete cursor;
        --size;
    } else {
        std::string message = "Stack ";
        throw Empty(message);
    }
}

// Returns the top element of the stack without removing it. Throws an
// exception if the stack is empty.

template<class T>
T& Stack<T>::top() throw (Empty) {
    if (first) {
        return first->data;
    } else {
        std::string message = "Stack ";
        throw Empty(message);
    }

}

template<class T>
T const & Stack<T>::top() const throw (Empty) {
    if (first) {
        return first->data;
    } else {
        std::string message = "Stack ";
        throw Empty(message);
    }

}

// Clears the stack if it is not empty. Throws an exception if the stack
// is empty.

template<class T>
void Stack<T>::clear() {
    // Iterate through the stack
    while (first) {
        Node * cursor = first;
        // Go to the next node
        first = first->next;
        // Deallocate the current node
        --size;
        delete cursor;
    }
}

// Returns true if the list is empty, false otherwise.

template<class T>
bool Stack<T>::isEmpty() const {
    // If first is not NULL the list is not empty
    return first == NULL;
}

// Returns a string of the stack. Requires that the class type T overload the <<
// and >> operators if an object.

template<class T>
std::string Stack<T>::toString() const {
    std::string contents;
    std::stringstream s;
    Node *cursor = first;
    while (cursor) {
        s << cursor->data << " ";
        cursor = cursor->next;
    }
    contents = s.str();
    return contents;
}

/*Utility Functions*/
template<class T>
void Stack<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

#endif	/* STACK_H */
