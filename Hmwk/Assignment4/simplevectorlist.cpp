/*
 * Author: Marlo Zeroth
 * Assignment 4
 * September 26, 2015
 * Implements the SimpleVector class using a linked list
 * This is the implementation file simplevectorllist.cpp for
 * the class interface simplevectorllist.h
 */

#include <cstdlib>
#include <simplevectorlist.h>
#include <new>                  // Needed for bad allocation
#include <cstdlib>              // Needed for the exit function
#include <iostream>             // Needed for basic I/O
#include <emptyvector.h>        // For throwing an exception when the vector is empty

/******* Constructors and Destructor *******/

// Main constructor
LinkedList::LinkedList(const int &input){

    try{
        // Initialize the size to 1
        vectorSize = 1;
        // Create a new node, set its data element
        // to the input and its pointer to null
        Node *link = new Node;
        link->data = input;
        link->next = NULL;

        // Now set the head pointer to this new link
        // in the list/chain
        head = link;
    }
    catch(std::bad_alloc){
        memError();
    }
}

// Copy constructor
LinkedList::LinkedList(const LinkedList &obj){

    Node *cursor; // For navigating through the obj list
    Node *current; // Current link in the chain to be added

     // Clear the pointers
    cursor = head = NULL;
    // Now copy all the links from input into this object
    cursor = obj.head;

    // Set the size of the list
    vectorSize = obj.vectorSize;

    if(cursor){
        try{
            // Create the head node and set its data
            Node *link = new Node;
            link->data=cursor->data;
            link->next = NULL;
            current = head = link;
            // Go to the next node to copy if any
            cursor=cursor->next;
        }
        catch(std::bad_alloc){
            memError();
        }
    }

    // Traverse the rest of the nodes in obj
    while(cursor){

        try{
            // Create a new link and set its data
            Node *link = new Node;
            link->data=cursor->data;
            // Now link it with the other links in the list
            link->next = NULL;
            // Connect the new link to the existing links
            current->next = link;
            // Now set the new link as the current link
            current=link;
            // Go to the next link in obj list
            cursor = cursor->next;
        }
        catch(std::bad_alloc){
            memError();
        }
    }
}

// Destructor
LinkedList::~LinkedList(){

    Node *cursor; // For navigating through the list

    while(head && vectorSize > 0){

        // Set the cursor to the current head
        cursor = head;
        // Set the head pointer to the next link
        head=head->next;
        // Dealloate the current link
        delete cursor;
    }
}

/* Overloaded Operators */

// Overload [] operator declaration. The returned object can be
// modified. Throws an EmptyVector exception if the vector is empty.
int & LinkedList::operator [](const int & sub) throw (EmptyVector){

    int totalArrayOp=0; // Reset the count

    // 2 comparison < >= 1 boolean ||
    totalArrayOp+=3;

    // If the subscript is out of range give message
    // and exit
    if (sub < 0 || sub >= vectorSize)
          subError();

    // 2 comparison == 1 boolean ||
    totalArrayOp+=3;

    // If the vector is empty give a message and throw and exception
    if(vectorSize==0 || head == NULL){
        std::cout<<"Vector is empty"<<std::endl;
        throw EmptyVector();
    }

    // 2 assignment =
    totalArrayOp+=2;

    // Otherwise we traverse the list until we find the
    // desired position.
    int count = 0;
    Node *cursor = head;
    // Keep going until we reach the desired subscript
    while(cursor && count < sub){

        // 2 comparison < 1 boolean &&
        totalArrayOp+=3;

        // Go to the next one
        cursor = cursor->next;
        count++;

        // 1 assignment, 1 increment
        totalArrayOp+=2;
    }

    // 1 return
    totalArrayOp++;

    std::cout<<"Total operations in [] operator: "<< totalArrayOp << std::endl;

    // We found it!
    return cursor->data;
}

// Overload [] const operator declaration. Guarantees that
// the returned object will not be modified.
// Throws an EmptyVector exception if the vector is empty
const int& LinkedList::operator [](const int & sub) const throw (EmptyVector){

    // If the subscript is out of range give message
    // and exit
    if (sub < 0 || sub >= vectorSize)
          subError();

    // If the vector is empty give a message and throw and exception
    if(vectorSize==0 || head == NULL){
        std::cout<<"Vector is empty"<<std::endl;
        throw EmptyVector();
    }

    // Otherwise we traverse the list until we find the
    // desired position.
    int count = 0;
    Node *cursor = head;

    // Keep going until we reach the desired subscript
    while(cursor && count < sub){
        // Go to the next one
        cursor = cursor->next;
        count++;
    }

    // We found it!
    return cursor->data;
}

// Overload = operator declaration
LinkedList& LinkedList::operator =(const LinkedList &input){

    // Test to make sure the passed object is not the same
    // as calling object e.g. input = input
    if(this!=&input){
        Node *cursor; // For navigating through the obj list
        Node *current; // Current link in the chain to be added

        // Clear out the data in the existing list
        while(head){
            // Set the cursor to the current head
            cursor = head;
            // Set the head pointer to the next link
            head=head->next;
            // Dealloate the current link
            delete cursor;
        }
        // Clear the pointers
        cursor = head = NULL;
        // Now copy all the links from input into this object
        cursor = input.head;

        // Set the size of the list
        vectorSize = input.vectorSize;

        if(cursor){
            try{
                // Create the head node and set its data
                Node *link = new Node;
                link->data=cursor->data;
                link->next = NULL;
                current = head = link;
                // Go to the next node to copy if any
                cursor=cursor->next;
            }
            catch(std::bad_alloc){
                memError();
            }
        }

        // Traverse the rest of the nodes in obj
        while(cursor){

            try{
                // Create a new link and set its data
                Node *link = new Node;
                link->data=cursor->data;
                // Now link it with the other links in the list
                link->next = NULL;
                // Connect the new link to the existing links
                current->next = link;
                // Now set the new link as the current link
                current=link;
                // Go to the next link in obj list
                cursor = cursor->next;
            }
            catch(std::bad_alloc){
                memError();
            }
        }        
    }
    // Just return a reference to
    return *this;
}

/* Mutators and Accessors*/

//********************************************************
// push Function. Adds an input to the end of the vector *
//********************************************************

void LinkedList::push(const int& input){

    int totalPush=0;// Reset the count

    // 1 boolean
    totalPush++;

    // Test to see if we have added any items to the vector
    if(head){

        // 1 assignment
        totalPush++;

        Node *cursor; // For navigating through the list
        // Go through the list until the last node, then
        // add the new link there
        cursor = head;

        while(cursor->next){
            // 1 assignment and 1 boolean
            totalPush+=2;

            // Keep going until we get to the end.
            cursor = cursor->next;
        }

        try{
            // Create a new node, set its data element
            // to the input and its pointer to null
            Node *link = new Node;
            link->data = input;
            link->next = NULL;
            // Add the new link to the last link we found
            cursor->next = link;

            // 4 assignment
            totalPush+=4;

        }
        catch(std::bad_alloc){
            memError();
        }

        // 1 increment
        totalPush++;

        // Increase the size by 1
        vectorSize++;
    }

    // If the vector does not have any items
    else{
        // Create a new node, set its data element
        // to the input and its pointer to null
        Node *link = new Node;
        link->data = input;
        link->next = NULL;

        // Now set the head pointer to this new link
        // in the list/chain
        head = link;
        // Initialize the size to 1
        vectorSize = 1;

        // 5 assignment =, 1 memory access new
        totalPush+=5;
    }

    std::cout<<"Total operations in push: "<< totalPush << std::endl;

}

//************************************************
// pull function. Returns the element at the end *
// of the vector if the vector is not empty.     *
// An error is displayed if the list is empty    *
//************************************************

int LinkedList::pull(){

    int totalPull=0; // Reset the counter

    // 2 comparison != > and 1 boolean &&
    totalPull+=3;

    if(head!=NULL && vectorSize>0){

        Node *cursor; // For navigating through the list
        Node *previous; // For removing link
        // We go through the links until we get to the last one
        cursor = head;
        previous = cursor;

        // 2 assignment
        totalPull+=2;

        while(cursor->next){
            // Keep going until we get to the end.
            previous = cursor;
            cursor = cursor->next;

            // 2 assignment = and 1 boolean
            totalPull+=3;
        }
        // Decrement the size and return the data in the link
        int output;
        output = cursor->data;
        // Remove the link
        previous->next=NULL;

        // 2 assignment
        totalPull+=2;

        // 1 Memory access and 1 decrement
        totalPull+=2;

        delete cursor;
        vectorSize--;

        // 1 comparison ==
        totalPull++;

        // If it was the last link in the list we can set the head node
        // pointer to 0.
        if(vectorSize==0){
            head=NULL;
            // 1 assignment
            totalPull++;
        }

        std::cout<<"Total operations in pull: "<<totalPull<<std::endl;

        return output;
    }
    // If the list does not have anything just return 0 (or null)
    // Only for test purposes. Could throw an exception and exit_failure instead.
    std::cout<<"Empty vector. Return value 0." <<std::endl;
    return 0;
}

/*Utility Functions*/

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

void LinkedList::memError() const
{
   std::cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

void LinkedList::subError() const
{
   std::cout << "ERROR: Subscript out of range.\n";
   exit(EXIT_FAILURE);
}
