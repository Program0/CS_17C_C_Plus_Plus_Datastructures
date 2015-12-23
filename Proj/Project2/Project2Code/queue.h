/*
 * Author: Marlo Zeroth
 * doublyList.h
 *
 * Implements a template doubly linked list data structure. Allows duplicates, 
 * insertion at front, back, and any point in the list. The list is not ordered.
 * Created on: Nov 4, 2015
 *      
 */


#ifndef QUEUE_H
#define	QUEUE_H

#include <new>

#include "empty.h"

template<class T>
class Queue {
private:
    // Internal struct to hold data and point to other nodes

    struct Node {
        // Default constructor

        Node() : next(NULL), previous(NULL) {
        }

        // Main constructor

        Node(const T& input, Node* nextNode, Node* previousNode) :
        data(input), next(nextNode), previous(previousNode) {
        }
        // Node member variables
        T data;
        Node *next;
        Node *previous;
    };

    /*Utility functions*/
    void memError() const;
    // Handles memory allocation errors

    /* queue Member variables */
    Node *head; // Reference to first/head node
    Node *tail; // Reference to last/tail node
    int size;

public:

    Queue();
    // Default constructor

    Queue(const T &entry);
    // Main constructor

    Queue(const Queue<T> &obj);
    // Copy constructor

    ~Queue();
    // Destructor

    // Overloaded Operators

    Queue<T>& operator=(const Queue<T> &obj);
    // Overloaded = operator

    /* Mutators and Accessors */

    void push(const T& entry);
    // Adds an entry to the front of the queue    

    void pop() throw (Empty);
    // Removes and returns the back entry from the queue

    void clear();
    // Removes all items for the queue

    T& back() throw (Empty);
    // Returns the first element in the queue

    T& front() throw (Empty);
    // Returns the last element in the queue

    bool contains(const T& entry);
    // Returns whether the queue contains the passed entry.

    int length() const {
        return size;
    }
    // Returns the size of the queue

    bool isEmpty() const {
        return (head == NULL && tail == NULL);
    }
    // Returns whether the queue is empty
};

/*Constructors and Destructor Definitions */

// Default constructor

template<class T>
Queue<T>::Queue() {
    tail = NULL;
    head = NULL;
    size = 0;
}

//****************************************************************
// Main constructor. Adds an entry and increments the size by 1. *
//****************************************************************

template<class T>
Queue<T>::Queue(const T &entry) {

    // Create new node with entry parameter
    Node *link;
    // Attempt to allocate memory
    try {
        link = new Node(entry, NULL, NULL);

    } catch (const std::bad_alloc&) {
        memError();
    }
    // Now point the head and tail to this new link in the list
    head = tail = link;
    size++;

}

// Copy constructor. This is order O(N).

template<class T>
Queue<T>::Queue(const Queue<T> &obj) {
    // Set the head and tail pointers to null.
    tail = head = NULL;

    // Set the size of the list
    size = 0;

    // Now set the cursor to the object's head and
    // traverse the links in obj if there are any.
    Node *cursor; // For navigating through the obj list
    for (cursor = obj.head; cursor != 0; cursor = cursor->next) {
        push(cursor->data);
    }
}

// Destructor

template<class T>
Queue<T>::~Queue() {
    // Traverse the list deleting each link
    while (head) {
        // Set the cursor to the current head
        Node *cursor = head;
        // Set the head pointer to the next link
        head = head->next;
        // Deallocate the current link
        delete cursor;
    }
    tail = NULL;
}


/*Overloaded operators*/

// Overload = operator declaration

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T> &obj) {
    // Test to make sure the passed object is not the same
    // as calling object e.g. input = input
    if (this != &obj) {
        // Remove the current contents of the queue
        clear();

        // Now set the cursor to the object's head and
        // traverse the links in obj if there are any and copy.
        Node *cursor; // For navigating through the obj list
        for (cursor = obj.head; cursor != 0; cursor = cursor->next) {
            push(cursor->data);
        }
    }
    // Just return a reference
    return *this;
}

/*Mutators and accessors*/

//********************************************************************
// enqueue Function. Adds an element at the back of the of the queue *
//********************************************************************

template<class T>
void Queue<T>::push(const T& input) {
    // Create a new node for the input.
    Node *link;

    // Allocate memory
    try {
        link = new Node(input, NULL, NULL);

    } catch (const std::bad_alloc&) {
        memError();
    }

    // If the queue is empty, add the new link at the front. Otherwise
    // just add it to the back
    if (isEmpty()) {
        // Set the link's next and previous to null as this is the only link        
        // Now point the head and tail to the new link
        head = link;
    } else {
        // Since it will be at the end, the new link's previous pointer should
        // point to the current tail link in the list.
        link->previous = tail;
        // Now set the next pointer in the existing tail link
        // to the new link.
        tail->next = link;
    }
    // Link it to the queue and increment the size
    tail = link;
    size++;
}

//**********************************************************
// pop function. Removes the front element in the queue if *
// the queue is not empty. Throws anEmpty  exception if    * 
// queue is empty.                                         *
//**********************************************************

template<class T>
void Queue<T>::pop() throw (Empty) {
    if (isEmpty()) {
        std::string message = "Queue";
        throw Empty(message);
    } else {
        Node *cursor = head; // To deallocate later
        // Test if this is the only node
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            // Set the front to be the next node.
            head = head->next;
        }
        // Deallocate memory and decrease the size
        delete cursor;
        cursor = NULL;
        --size;
    }
}


//*********************************************************
// back function. Returns the back element in the queue   *
//*********************************************************

template<class T>
T& Queue<T>::back() throw (Empty) {
    if (isEmpty()) {
        std::string message = "Queue";
        throw Empty(message);
    } else {
        return tail->data;
    }

}

//*********************************************************
// front function. Returns the front element in the queue *
//*********************************************************

template<class T>
T& Queue<T>::front() throw (Empty) {
    if (isEmpty()) {
        std::string message ="Queue";
        throw Empty(message);
    } else {
        return head->data;
    }
}

//****************************************************************
// contains function. Returns true if entry is in the list and   *
// moves the found link to the head/front of the list. Otherwise *
// returns false.                                                *
//****************************************************************

template<class T>
bool Queue<T>::contains(const T& entry) {
    Node *cursor = head;
    bool found = false;
    // Go through the list until we reach the end
    // or find the entry
    while (!found && cursor != 0) {
        if (cursor->data == entry) {
            if (cursor->next == NULL && cursor->previous != NULL) {
                // The previous link before the cursor is now 
                // the last link
                cursor->previous = cursor->next;
                // Now we set the entry at the beginning
                cursor->next = head;
                head->previous = cursor;
                head = cursor;
            } else if (cursor->next != NULL && cursor->previous != NULL) {
                // Link the nodes next to cursor together
                Node before = cursor->previous;
                Node after = cursor->next;
                before->next = cursor->next;
                after->previous = cursor->previous;

                // Now set the cursor at the front
                cursor->previous = NULL;
                cursor->next = head;
                head->previous = cursor;
                head = cursor;
            }
            found = true;
        }
        cursor = cursor->next;
    }
    return found;
}

//***************************************************************************
// clear function. Deallocates each link in the list and sets the size to 0 *
//***************************************************************************

template<class T>
void Queue<T>::clear() {
    Node *cursor;
    // Clear out the data in the existing list
    while (head) {
        // Set the cursor to the current head
        cursor = head;
        // Set the head pointer to the next link
        head = head->next;
        // Deallocate the current link
        delete cursor;
    }
    tail = NULL;
    size = 0;
}

/*Utility Functions*/

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template<class T>
void Queue<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

#endif	/* QUEUE_H */

