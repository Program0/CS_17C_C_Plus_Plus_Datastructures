/* 
 * File:   tlist.h
 * Author: Marlo Zeroth
 * Implements a template singly linked list. The data structure allows
 * duplicates and is not ordered. *
 * Created on November 11, 2015, 10:05 PM
 */

#ifndef TLIST_HPP
#define	TLIST_HPP

#include <cstdlib>
#include <string>
#include <sstream>

#include "empty.h"

template<class T>
class TList {
private:

    // Nested class only accessible to TList and iterator

    class Node {
    public:
        // Friend classes to access privates
        friend class TList;
        friend class iterator;

        // Main constructor

        Node(const T& entry, Node *ptr) : data(entry), next(ptr) {
        };
    private:
        T data;
        Node *next;
    };

    // TList Member variables
    Node *head;
    unsigned int size;

public:

    // Nested iterator class to externally traverse the list

    class iterator {
    public:
        friend class TList;
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

    TList() : head(NULL) {
    };
    // Main constructor
    TList(T& entry);
    // Copy constructor
    TList(const TList& obj);
    // Destructor
    ~TList();

    // Inserts an entry at the front of the list. O(1).
    void prepend(const T& entry);

    // Inserts an entry at the back of the list. O(n).
    void append(const T& entry);

    // Removes an entry in the list. Returns true if successful,
    // false otherwise. O(n).
    bool remove(const T& entry);

    // Removes all instances of entry from the list. O(n).
    bool removeAll(const T& entry);

    // Removes all elements from the list. O(n).
    void clear();

    // Returns the size of the list. O(1).

    unsigned int length()const {
        return size;
    }

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

    // Returns whether the list contains the passed entry. O(n).
    bool contains(const T& entry);

    void memError() const;

    void subError() const;

};

// 

template<class T>
TList<T>::TList(T& entry) {
    Node *link = new Node(entry, NULL);
    // Set this as the head
    head = link;
}

template<class T>
TList<T>::TList(const TList & obj) {
    Node * cursor = obj.head;
    // Go through obj link's and copy each data element
    // into new links
    for (cursor; cursor != NULL; cursor = cursor->next) {
        Node *link = new Node(cursor->data, head);
        // Add to the front/head
        head = link;
        size++;
    }
}

template<class T>
TList<T>::~TList() {
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
void TList<T>::prepend(const T& entry) {
    // Create a new link with head as the next the next pointer
    Node *link = new Node(entry, head);
    // Set the new link to be the new head
    head = link;
    size++;
}

template<class T>
void TList<T>::append(const T& entry) {
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
            Node *link = new Node(entry, NULL);
            // Add the new link to the last link we found
            cursor->next = link;
        } catch (std::bad_alloc) {
            memError();
        }

        // Increase the size by 1
        size++;
    }// If the list is empty
    else {
        // Just it to the front
        prepend(entry);
    }
}

// Returns the first element in the list

template<class T>
T& TList<T>::first() throw (Empty) {
    if (head) {
        return head->data;
    } else {
        throw Empty();
    }

}

// Removes an entry from the list. 

template<class T>
bool TList<T>::remove(const T& entry) {
    // For traversing the list
    Node *cursor = head;
    // For changing the link before the entry to delete
    Node *prevPtr = NULL;
    bool found = false;
    // Traverse the list until we find the node or 
    // we reach the end
    while (cursor->data != entry && cursor != NULL) {
        if (cursor->data == entry)
            found = true;
        // Set the previous link to the current link
        prevPtr = cursor;
        // Go to the next link
        cursor = cursor->next;
    }

    if (cursor == 0)
        found = false;

    // If we found it delete it        
    if (cursor == head) {
        // If it is at the front of the list, there is not previous 
        // link. Just set the head to the next link
        head = cursor->next;
        found = true;
    } else {
        // Link the previous node and the node after the 
        // one to delete
        prevPtr->next = cursor->next;
        found = true;
    }
    // Deallocate it
    delete cursor;
    --size;
    return found;
}

template<class T>
bool TList<T>::removeAll(const T& entry) {
    // For traversing the list
    Node *cursor = head;
    // For changing the link before the entry to delete
    Node *prevPtr = NULL;
    bool found = false;
    // Traverse the list until we find the node or 
    // we reach the end
    while (cursor != NULL) {
        // Set the previous link to the current link
        prevPtr = cursor;
        // Go to the next link
        cursor = cursor->next;
        // If we found it delete it
        if (cursor->data == entry) {
            // Link the previous node and the node after the 
            // one to delete
            prevPtr->next = cursor->next;
            // Deallocate it
            delete cursor;
            --size;
            found = true;
        }
    }
    return found;
}

// Removes all entries from the list

template<class T>
void TList<T>::clear() {
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
std::string TList<T>::toString() {
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
typename TList<T>::iterator TList<T>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename TList<T>::iterator TList<T>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename TList<T>::iterator TList<T>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename TList<T>::iterator TList<T>::end() const {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

// Iterator implementation

// Default constructor

template<class T>
TList<T>::iterator::iterator() {
}

// Main constructor

template<class T>
TList<T>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/
template<class T>
bool TList<T>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}

template<class T>
bool TList<T>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class T>
T& TList<T>::iterator::operator*() {
    return position->data;
}

template<class T>
T* TList<T>::iterator::operator->() {
    return (&*(TList<T>::iterator) * this);
}


// Prefix increments the iterator to the next element

template<class T>
typename TList<T>::iterator& TList<T>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element

template<class T>
typename TList<T>::iterator TList<T>::iterator::operator++(int) {
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
void TList<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template<class T>
void TList<T>::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}



#endif	/* TLIST_HPP */

