/* 
 * File:   singlylist.h
 * Author: Marlo Zeroth
 * Implements a template singly linked list. The data structure allows
 * duplicates and is not ordered. *
 * Created on November 11, 2015, 10:05 PM
 */

#ifndef SINGLYLIST_H
#define	SINGLYLIST_H

#include <cstdlib>
#include <string>
#include <sstream>

#include "empty.h"

template<class T>
class SinglyList {
private:
    // Nested class only accessible to SinglyList and iterator

    struct Node {
        T data;
        Node *next;
    };

    // Utility functions

    // Functions provided by Dr. Lehr for dealing with memory errors and 
    // indexes out of bounds
    void memError() const;
    void subError() const;

    // SinglyList Member variables
    Node *head;
    unsigned int size;

public:
    // Nested iterator class to externally traverse the list

    class iterator {
    public:
        friend class SinglyList;
        // Default constructor
        iterator();

        // Prefix increment operator
        iterator& operator++();

        // Postfix increment operator
        iterator operator++(int);

        // Dereference operator
        T& operator*();

        // Returns the addres of the value referred to
        T* operator->();

        // Comparison operator
        bool operator==(const iterator &obj) const;

        // Comparison operator
        bool operator!=(const iterator &obj) const;

    private:
        // Main constructor
        iterator(Node *ptr);
        Node *position;
    };

    // Default constructor

    SinglyList() : head(NULL), size(0) {
    };

    // Main constructor
    SinglyList(T& entry);

    // Copy constructor    
    SinglyList(const SinglyList& obj);

    // Destructor
    ~SinglyList();

    // Overloaded assignment operator
    SinglyList<T>& operator=(const SinglyList<T> &obj);

    // Inserts an entry at the front of the list. O(1).
    void prepend(const T& entry);

    // Inserts an entry at the back of the list. O(n).
    void append(const T& entry);

    // Inserts an entry before the given position
    void insertBefore(const T& position, const T&entry);

    // Inserts and entry after the given position
    void insertAfter(const T& position, const T&entry);

    // Removes an entry in the list. Returns true if successful,
    // false otherwise. O(n).
    void extract(const T& entry);

    // Removes all elements from the list. O(n).
    void clear();

    // Returns the size of the list. O(1).

    unsigned int length()const {
        return size;
    }

    // Returns whether the list is empty

    bool isEmpty() const {
        return head == NULL;
    }
    
    // Returns whether the passed entry is in the list
    bool contains(const T& entry);

    // Returns a string of the list elements. O(n).
    std::string toString();

    // Returns the first element in the list. O(1).
    T& first() throw (Empty);

    // Returns the last element in the list. O(n).
    T& last() throw (Empty);

    // Returns a pointer to the beginning of the list. O(1).
    iterator begin();
    iterator begin() const;

    // Returns a null iterator to signify the end of the list. O(1).
    iterator end();
    iterator end() const;    
};

// Main constructor

template<class T>
SinglyList<T>::SinglyList(T& entry) {
    Node *link = new Node;
    link->data = entry;
    link->next = NULL;
    // Set this as the head
    head = link;
    size = 0;
}

// Copy constructor

template<class T>
SinglyList<T>::SinglyList(const SinglyList<T>& obj) {
    if (!obj.isEmpty()) {
        size = 0;
        head = NULL;
        // Copy the contents of obj. Note these will be in reverse order
        for (Node *cursor = obj.head; cursor != NULL; cursor = cursor->next) {
            prepend(cursor->data);
        }

        // Node following code to reverse contents was found at:
        // http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
        Node *result = NULL;
        Node *current = head;
        Node *next;

        while (current != NULL) {
            next = current->next; // Store the address of the next node

            current->next = result; // Swap the addresses of the current and next node
            result = current;

            current = next; // Advance to the next node
        }

        head = result;

    } else {
        size = 0;
        head = NULL;
    }
}

template<class T>
SinglyList<T>::~SinglyList() {
    Node *cursor = head;
    // Traverse the list delete each link
    while (head) {
        // Get the current link
        cursor = head;
        // Go to the next link
        head = head->next;
        // Deallocate the current link
        delete cursor;
    }
}

template<class T>
SinglyList<T>& SinglyList<T>::operator=(const SinglyList<T> &obj) {
    if (!obj.isEmpty()) {
        // Empty the current list  
        clear();
        // Initialize the member variables
        size = 0;
        head = NULL;

        // Iterate through obj's nodes and create a list
        Node *cursor;
        for (cursor = obj.head; cursor != NULL; cursor = cursor->next) {
            prepend(cursor->data);
        }
        // Node following code to reverse contents was found at:
        // http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
        Node *result = NULL;
        Node *current = head;
        Node *next;

        while (current != NULL) {
            next = current->next; // Store the address of the next node

            current->next = result; // Swap the addresses of the current and next node
            result = current;

            current = next; // Advance to the next node
        }
        // Now set the first node address
        head = result;
    }
    return *this;
}

template<class T>
void SinglyList<T>::prepend(const T& entry) {
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
    link->next = head;
    head = link;
    size++;
}

template<class T>
void SinglyList<T>::append(const T& entry) {
    // Test if the list is empty
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
            link->data = entry;
            link->next = NULL;
            // Add the new link to the last link we found
            cursor->next = link;
        } catch (std::bad_alloc) {
            memError();
        }

        // Increase the size by 1
        size++;
    }// If the list is empty
    else {
        // Just add it to the front
        prepend(entry);
    }
}

// Inserts an entry before the given position if position is found in the list.
// If it is not in the list it inserts at the end or if the list is empty it 
// prepends the entry

template<class T>
void SinglyList<T>::insertBefore(const T& position, const T& entry) {
    if (head) {
        Node *cursor; // For navigating through the list
        Node *previous; // For removing link

        //Start at the beginning of the list
        cursor = head;
        previous = cursor;

        // We go through the links until we find the position or reach the last one
        while (cursor != NULL && cursor->data != position) {
            // Keep going until we get to the end.
            previous = cursor;
            cursor = cursor->next;
        }

        Node *link;
        // Attempt to allocate memory
        try {
            link = new Node;
            // Set its data member and pointers
            link->data = entry;
            link->next = NULL;

        } catch (const std::bad_alloc&) {
            memError();
        }

        if (cursor == head) {
            link->next = head;
            head = link;

        } else {
            // Add it between previous and cursor
            link->data = entry;
            link->next = cursor;
            previous->next = link;
        }
        ++size;
    } else {
        prepend(entry);
    }
}

// Inserts an entry after the given position if position is found in the list.
// If it is not in the list it inserts at the end or if the list is empty it 
// prepends the entry

template<class T>
void SinglyList<T>::insertAfter(const T& position, const T& entry) {

    if (head) {
        Node *cursor; // For navigating through the list
        //Start at the beginning of the list
        cursor = head;

        // We go through the links until we find the position or reach the last one
        while (cursor->next != NULL && cursor->data != position) {
            // Keep going until we get to the end.            
            cursor = cursor->next;
        }

        // Add it right after cursor
        Node *link = new Node;
        link->data = entry;
        link->next = cursor->next;
        cursor->next = link;
        ++size;

    } else {
        prepend(entry);
    }
}

// Returns the first element in the list

template<class T>
T& SinglyList<T>::first() throw (Empty) {
    if (head) {
        return head->data;
    } else {
        throw Empty();
    }

}

// Returns the last element in the list. Time O(n))

template<class T>
T& SinglyList<T>::last() throw (Empty) {
    Node *cursor = head;

    // If the list is empty throw an exception
    if (cursor == NULL)
        throw Empty();

    // Traverse the list until the end
    while (cursor->next != NULL) {
        cursor = cursor->next;
    }
    // Return the last entry
    return cursor->data;
}

// Returns whether a given entry is in the list
template<class T>
bool SinglyList<T>::contains(const T& entry){
    bool found = false;
    Node *cursor = head;
    while(cursor!=NULL && !found){
        if(cursor->data==entry)
            found = true;
        cursor = cursor->next;
    }
    return found;
}

// Removes an entry from the list.
template<class T>
void SinglyList<T>::extract(const T& entry) {
    // For traversing the list
    Node *cursor = head;
    // For changing the link before the entry to delete
    Node *prevPtr = NULL;

    // Traverse the list removing nodes where the entry is found until we 
    // we reach the end.
    while (cursor != NULL) {
        if (cursor->data == entry) {

            // If we found it delete it        
            if (cursor == head) {
                // If it is at the front of the list, there is not previous 
                // link. Just set the head to the next link
                head = head->next;
                delete cursor;
                --size;
                // Go to the next one
                cursor = head;
            } else {
                // Link the previous node and the node after the 
                // one to delete
                prevPtr->next = cursor->next;
                // Deallocate it
                delete cursor;
                --size;
                cursor = prevPtr->next;
            }

        } else {
            // Set the previous link to the current link
            prevPtr = cursor;
            // Go to the next link
            cursor = cursor->next;
        }
    }
}

// Clears the list of all entries

template<class T>
void SinglyList<T>::clear() {
    Node *cursor = head;
    // Traverse the list delete each link
    while (head) {
        // Get the current link
        cursor = head;
        // Go to the next link
        head = head->next;
        // Deallocate the current link
        delete cursor;
    }
    // Reset the size
    size = 0;
}

// Returns a string with the list's contents

template<class T>
std::string SinglyList<T>::toString() {
    std::string output;
    std::stringstream s;
    Node *cursor = head;
    // Traverse the list adding each link's data to the 
    // string stream
    while (cursor) {
        s << cursor->data << " ";
        cursor = cursor->next;
    }
    // Create a strip and return it.
    output = s.str();
    return output;
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename SinglyList<T>::iterator SinglyList<T>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename SinglyList<T>::iterator SinglyList<T>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename SinglyList<T>::iterator SinglyList<T>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename SinglyList<T>::iterator SinglyList<T>::end() const {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

// Iterator implementation

// Default constructor

template<class T>
SinglyList<T>::iterator::iterator() {
}

// Main constructor

template<class T>
SinglyList<T>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/
template<class T>
bool SinglyList<T>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}

template<class T>
bool SinglyList<T>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class T>
T& SinglyList<T>::iterator::operator*() {
    return position->data;
}

template<class T>
T* SinglyList<T>::iterator::operator->() {
    return (&*(SinglyList<T>::iterator) * this);
}


// Prefix increments the iterator to the next element

template<class T>
typename SinglyList<T>::iterator& SinglyList<T>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element

template<class T>
typename SinglyList<T>::iterator SinglyList<T>::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}


/*Utility Functions*/

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template<class T>
void SinglyList<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template<class T>
void SinglyList<T>::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}



#endif	/* SINGLYLIST_H */

