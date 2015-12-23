
/*
 * Author: Marlo Zeroth
 * Assignment 5
 * October 6, 2015
 * Version 1
 * Implements a linked list This is the implementation 
 * file list.cpp for the class interface list.h
 */

#include <cstdlib>
#include "list.h"         // Interface for linked list
#include <new>            // Needed for bad allocation
#include <cstdlib>        // Needed for the exit function
#include <iostream>       // Needed for basic I/O
#include "emptylist.h"    // For throwing an exception when the vector is empty

/******* Constructors and Destructor *******/

// Main constructor

List::List(const int &input) {

    try {
        // Initialize the size to 1
        size = 1;
        // Create a new node, set its data element
        // to the input and its pointer to null
        Node *link = new Node;
        link->data = input;
        link->next = NULL;

        // Now set the head pointer to this new link
        // in the list/chain
        head = link;
    } catch (std::bad_alloc) {
        memError();
    }
}

// Copy constructor

List::List(const List &obj) {

    Node *cursor; // For navigating through the obj list
    Node *current; // Current link in the chain to be added

    // Clear the pointers
    cursor = head = NULL;
    // Now copy all the links from input into this object
    cursor = obj.head;

    // Set the size of the list
    size = obj.size;

    if (cursor) {
        try {
            // Create the head node and set its data
            Node *link = new Node;
            link->data = cursor->data;
            link->next = NULL;
            current = head = link;
            // Go to the next node to copy if any
            cursor = cursor->next;
        } catch (std::bad_alloc) {
            memError();
        }
    }

    // Traverse the rest of the nodes in obj
    while (cursor) {

        try {
            // Create a new link and set its data
            Node *link = new Node;
            link->data = cursor->data;
            // Now link it with the other links in the list
            link->next = NULL;
            // Connect the new link to the existing links
            current->next = link;
            // Now set the new link as the current link
            current = link;
            // Go to the next link in obj list
            cursor = cursor->next;
        } catch (std::bad_alloc) {
            memError();
        }
    }
}

// Destructor

List::~List() {

    // For navigating through the list

    while (head) {
        // Set the cursor to the current head
        Node const *cursor = head;       
        // Set the head pointer to the next link
        head = head->next;
        // Dealloate the current link
        delete cursor;
    }
}

/* Overloaded Operators */

// Overload [] operator declaration. The returned object can be
// modified. Throws an EmptyVector exception if the vector is empty.

int & List::operator[](const int & sub) throw (EmptyList) {

    // If the subscript is out of range give message
    // and exit
    if (sub < 0 || sub >= size)
        subError();

    // If the list is empty give a message and throw an exception
    if (size == 0 || head == NULL) {
        std::cout << "Vector is empty" << std::endl;
        throw EmptyList();
    }

    // Otherwise we traverse the list until we find the
    // desired position.
    int count = 0;
    Node *cursor = head;

    // Keep going until we reach the desired element
    while (cursor && count < sub) {

        // Go to the next one
        cursor = cursor->next;
        count++;
    }

    // We found it!
    return cursor->data;
}

// Overload [] const operator declaration. Guarantees that
// the returned object will not be modified.
// Throws an EmptyVector exception if the vector is empty

const int& List::operator[](const int & sub) const throw (EmptyList) {

    // If the subscript is out of range give message
    // and exit
    if (sub < 0 || sub >= size)
        subError();

    // If the list is empty give a message and throw an exception
    if (size == 0 || head == NULL) {
        std::cout << "Vector is empty" << std::endl;
        throw EmptyList();
    }

    // Otherwise we traverse the list until we find the
    // desired position.
    int count = 0;
    Node *cursor = head;

    // Keep going until we reach the desired subscript
    while (cursor && count < sub) {
        // Go to the next one
        cursor = cursor->next;
        count++;
    }

    // We found it!
    return cursor->data;
}

// Overload = operator declaration

List& List::operator=(const List &input) {

    // Test to make sure the passed object is not the same
    // as calling object e.g. input = input
    if (this != &input) {
        Node *cursor; // For navigating through the obj list
        Node *current; // Current link in the chain to be added

        // Clear out the data in the existing list
        while (head) {
            // Set the cursor to the current head
            cursor = head;
            // Set the head pointer to the next link
            head = head->next;
            // Deallocate the current link
            delete cursor;
        }
        // Clear the pointers
        cursor = head = NULL;
        // Now copy all the links from input into this object
        cursor = input.head;

        // Set the size of the list
        size = input.size;

        if (cursor) {
            try {
                // Create the head node and set its data
                Node *link = new Node;
                link->data = cursor->data;
                link->next = NULL;
                current = head = link;
                // Go to the next node to copy if any
                cursor = cursor->next;
            } catch (std::bad_alloc) {
                memError();
            }
        }

        // Traverse the rest of the nodes in obj
        while (cursor) {

            try {
                // Create a new link and set its data
                Node *link = new Node;
                link->data = cursor->data;
                // Now link it with the other links in the list
                link->next = NULL;
                // Connect the new link to the existing links
                current->next = link;
                // Now set the new link as the current link
                current = link;
                // Go to the next link in obj list
                cursor = cursor->next;
            } catch (std::bad_alloc) {
                memError();
            }
        }
    }
    // Just return a reference to
    return *this;
}

/* Mutators and Accessors*/

//*********************************************************
// append Function. Adds an input to the end of the list. *
//*********************************************************

void List::append(const int& input) {

    // Test to see if we have added any items to the vector
    if (head) {

        Node *cursor; // For navigating through the list
        cursor = head; // Start at the front of the list

        // Go through the list until the last node, then
        // add the new link there
        while (cursor->next) {
            // Keep going until we get to the end.
            cursor = cursor->next;
        }

        try {
            // Create a new node, set its data element
            // to the input and its pointer to null
            Node *link = new Node;
            link->data = input;
            link->next = NULL;
            // Add the new link to the last link we found
            cursor->next = link;
        } catch (std::bad_alloc) {
            memError();
        }

        // Increase the size by 1
        size++;
    }        // If the vector does not have any items
    else {
        // Create a new node, set its data element
        // to the input and its pointer to null
        Node *link = new Node;
        link->data = input;
        link->next = NULL;

        // Now set the head pointer to this new link
        // in the list/chain
        head = link;
        // Initialize the size to 1
        size = 1;
    }
}

//****************************************************************
// prepend Function. Adds a element at the beginning of the list *
//****************************************************************

void List::prepend(const int& input) {

    // Create a new node for the input and 
    // set its data element.

    Node *link = new Node;
    link->data = input;
    
    // Since it will be at the beginning, it should
    // point to the current first link in the list.    
    link->next = head;

    // Now set the new link to be the first link
    // and increase the list size.
    head = link;
    size++;
}

//************************************************
// first function. Returns the element at the    *
// beginning of the list if the list is not      *
// empty. An error is displayed if the list is   *
// empty.                                        *
//************************************************

int List::first() {
    if (head != NULL && size > 0) {

        Node *cursor;
        cursor = head;

        // Get the element at the front
        int output;
        output = head->data;

        // Deallocate the node and change the head
        // to the next link
        head = head->next;
        delete cursor;
        size--;
        return output;

    } else {
        // If the list does not have anything just return 0 (or null)
        // Only for test purposes. Could throw an exception and exit_failure instead.
        std::cout << "Empty list. Return value 0." << std::endl;
        return 0;
    }


}

//************************************************
// last function. Returns the element at the end *
// of the list if the list is not empty. An      *
// error is displayed if the list is empty       *
//************************************************

int List::last() {

    if (head != NULL && size > 0) {

        Node *cursor; // For navigating through the list
        Node *previous; // For removing link

        //Start at the beginning of the list
        cursor = head;
        previous = cursor;

        // We go through the links until we get to the last one
        while (cursor->next) {
            // Keep going until we get to the end.
            previous = cursor;
            cursor = cursor->next;
        }

        // Decrement the size and return the data in the link
        int output;
        output = cursor->data;
        // Remove the link
        previous->next = NULL;

        delete cursor;
        size--;

        // If it was the last link in the list we can set the head node
        // pointer to 0.
        if (size == 0) {
            head = NULL;
        }

        return output;
    }
    // If the list does not have anything just return 0 (or null)
    // Only for test purposes. Could throw an exception and exit_failure instead.
    std::cout << "Empty vector. Return value 0." << std::endl;
    return 0;
}
//*************************************************
// insertBefore function. Searches the list and   *
// inserts an element before the passed parameter *
// Returns true if successful, false otherwise    *
//*************************************************

bool List::insertBefore(const int & entry, const int& input){
    if(head){
        Node *cursor; // For navigating through the list
        Node *previous; // For removing link

        //Start at the beginning of the list
        cursor = head;
        previous = cursor;

        // We go through the links until we get to the last one
        while (cursor->next && cursor->data!=entry) {
            // Keep going until we get to the end.
            previous = cursor;
            cursor = cursor->next;
        }
        
                
    }
    return false;
    
}

bool List::insertAfter(const int & entry, const int& input){
    
}
void List::clear() {
	
	// Clear out the data in the existing list
	while (head) {
            // Set the cursor to the current head
            Node const *cursor = head;			
            // Set the head pointer to the next link
            head = head->next;
            // Deallocate the current link
            delete cursor;
	}        
	size = 0;
}
/*Utility Functions*/

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

void List::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

void List::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

