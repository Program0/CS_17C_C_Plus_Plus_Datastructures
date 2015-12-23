//***********************************************************
// List mimicking a priority queue. The contains function   *
// moves the passed entry to the front of the list if it    *
// exists in the list.                                      *
//***********************************************************


#ifndef ORDEREDLIST_H
#define	ORDEREDLIST_H
/*
 * OrderedList.h
 *
 *  Created on: Nov 4, 2015
 *      Author: super0
 */

#include <new>
#include <string>
#include <sstream>

#include "invalidargument.h"
#include "empty.h"

template<class T>
class OrderedList {
private:
    // Internal struct class to hold data and point to other nodes

    struct Node {
        T data;
        Node *next;
        Node *previous;
    };

    /*Utility functions*/
    void memError() const; // Handles memory allocation errors
    void subError() const; // Handles subscripts out of range

    // Returns the position of an entry in the list
    typename OrderedList<T>::iterator position(const T& entry) const;

    /* Ordered List Member variables */
    Node *head; // Reference to first/head node
    Node *tail; // Reference to last/tail node
    unsigned int size;

public:

    // iterator class for traversing the list

    class iterator {
    public:
        friend class OrderedList;
        // Default constructor. Allows .
        iterator();

        // Copy constructor
        //OrderedListIterator(const iterator & obj);

        // Destructor
        //~OrderedListIterator();

        /*Overloaded operators*/

        // Assignment operator
        iterator& operator=(const iterator& obj);

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
        iterator(Node *pter);
        Node *position;
    };

    // Default constructor
    OrderedList();

    // Main constructor
    OrderedList(const T &entry);

    // Copy constructor
    OrderedList(const OrderedList<T> &obj);

    // Destructor
    ~OrderedList();

    // Overloaded Operators

    // Oveloaded = operator
    OrderedList<T>& operator=(const OrderedList<T> &obj);

    /* Mutators and Accessors */

    void insert(const T& entry);

    // Returns whether the list contains the passed entry.
    bool contains(const T& entry);

    // Sorts the list in ascending order
    void sort();

    // Returns the size of the list

    unsigned int length() const {
        return size;
    }

    // Removes all items for the list
    void clear();

    // Returns whether the list is empty
    bool isEmpty()const {return (head == NULL && tail == NULL);}

    // Returns a string with the contents of the list
    std::string toString();

    // Removes all instances of entry from the list
    void extract(const T& entry);

    // Returns the first element in the list
    T& first() const throw (Empty);

    // Returns the last element in the list
    T& last() const throw (Empty);

    // Removes the first element of the list
    void removeFirst();

    // Removes the last element of the list
    void removeLast();

    // Returns a pointer to the beginning of the list.
    iterator begin();
    iterator begin() const;

    // Returns a a null iterator to signify the end of the list.
    iterator end();
    iterator end() const;

private:
    // Adds an entry to the front of the list
    void prepend(const T& entry);

    // Adds an entry to the back of the list
    void append(const T& entry);

    // Inserts an element before the passed parameter
    void insertBefore(OrderedList<T>::iterator position, const T& entry);

    // Inserts an element after the passed parameter
    void insertAfter(OrderedList<T>::iterator position, const T& entry);


};

/*OrderedList Class Constructor and Function Definitions */

// Default constructor

template<class T>
OrderedList<T>::OrderedList() {
    tail = NULL;
    head = NULL;
    size = 0;
}

//****************************************************************
// Main constructor. Adds an entry and increments the size by 1. *
//****************************************************************

template<class T>
OrderedList<T>::OrderedList(const T &entry) {

    // Create new node with entry parameter
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
    link->previous = NULL;

    // Now point the head and tail to this new link in the list
    head = tail = link;
    size++;

}

// Copy constructor. This is order O(N).

template<class T>
OrderedList<T>::OrderedList(const OrderedList<T> &obj) {

    // Set the head and tail pointers to null.
    tail = head = NULL;

    // Set the size of the list
    size = 0;

    // Now set the cursor to the object's head and
    // traverse the links in obj if there are any.
    Node *cursor; // For navigating through the obj list
    for (cursor = obj.head; cursor != 0; cursor = cursor->next) {
        append(cursor->data);
    }
}

// Destructor

template<class T>
OrderedList<T>::~OrderedList() {
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


// Overloaded operators

// Overload = operator declaration

template<class T>
OrderedList<T>& OrderedList<T>::operator=(const OrderedList<T> &obj) {

    std::cout << "= operator " << std::endl;
    // Test to make sure the passed object is not the same
    // as calling object e.g. input = input
    if (this != &obj) {
        clear();
        // Set the size of the list
        size = 0;

        // Now set the cursor to the object's head and
        // traverse the links in obj if there are any.
        Node *cursor; // For navigating through the obj list
        for (cursor = obj.head; cursor != 0; cursor = cursor->next) {
            append(cursor->data);
        }
    }
    // Just return a reference
    return *this;
}

/*Mutators and accessors*/

// Inserts an entry in ascending order.

template<class T>
void OrderedList<T>::insert(const T& entry) {

    // If the list is empty just put it at the front (can't put it elsewhere).
    if (!head) {
        Node * link;
        // Allocate memory
        try {
            link = new Node;

        } catch (const std::bad_alloc&) {
            memError();
        }
        // Set its data element.
        link->data = entry;
        // Set the link's next and previous to null as this is the only link
        link->next = NULL;
        link->previous = NULL;
        // Now point the head and tail to the new link
        tail = head = link;
        size++;

    } else {
        iterator itr = begin();
        iterator finish = end();
        bool found = false;
        // Iterate through the list until we find where the entry should go
        while (!found && itr != finish) {
            // If we find it keep set found to true and keep current itr
            // otherwise go to the next link.            
            if (entry<*itr)
                found = true;
            else
                ++itr;

        }

        // If we managed to reach the end of the list, just append the entry.
        if (itr == finish)
            append(entry);
            // Otherwise just insert it before the current iterator position
        else
            insertBefore(itr, entry);
    }
}

//****************************************************************
// prepend Function. Adds a element at the beginning of the list *
//****************************************************************

template<class T>
void OrderedList<T>::prepend(const T& input) {
    // Create a new node for the input.
    Node *link;

    // Allocate memory
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }

    // Set its data element.
    link->data = input;

    // If the list is empty, add the new link and point head and tail to it
    if (!head) {
        // Set the link's next and previous to null as this is the only link
        link->next = NULL;
        link->previous = NULL;
        // Now point the head and tail to the new link
        tail = head = link;
        size++;

    } else {
        // Since it will be at the beginning, it should
        // point to the current first link in the list.
        link->next = head;
        link->previous = NULL;
        // Now set the previous pointer in the existing first link
        // to the new link.
        head->previous = link;
        // Set the new head.
        head = link;
        size++;
    }
}

//**********************************************************
// append Function. Adds a element at the end of the list. *
//**********************************************************

template<class T>
void OrderedList<T>::append(const T& input) {
    // Create a new node for the input.
    Node *link;

    // Allocate memory
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }

    // Set its data element.
    link->data = input;

    // If the list is empty, add the new link and point head and tail to it
    if (!tail) {
        // Set the link's next and previous to null as this is the only link
        link->next = NULL;
        link->previous = NULL;
        // Now point the head and tail to the new link
        tail = head = link;
        size++;

    } else {
        // Since it will be at the end, it should
        // point to the current last link in the list.
        link->previous = tail;
        link->next = NULL;
        // Now set the next pointer in the existing last link
        // to the new link.
        tail->next = link;
        // Set the new tail.
        tail = link;
        size++;
    }
}

// Inserts an element before the passed parameter

template<class T>
void OrderedList<T>::insertBefore(OrderedList<T>::iterator location, const T& entry) {

    // Check to be sure this is a valid position
    if (location.position == 0) {
        throw InvalidArgument();
    }
    Node * link;
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    link->data = entry;
    // If the position is at the head, change the head
    if (location == begin()) {
        // Since it will be at the beginning, it should
        // point to the current first link in the list.
        link->next = location.position;
        link->previous = NULL;
        // Now set the previous pointer in the existing first link
        // to the new link.
        location.position->previous = link;
        // Set the new head.
        head = link;
        size++;
    } else {
        // Set the new link's previous pointer to point to the 
        // link before location
        link->previous = location.position->previous;

        // The link's next pointer should point to the current location
        link->next = location.position;

        // Change the previous link's next pointer to point
        // to the new link
        location.position->previous->next = link;
        location.position->previous = link;
        size++;
    }
}

// Inserts an element after the passed parameter

template<class T>
void OrderedList<T>::insertAfter(OrderedList<T>::iterator location, const T& entry) {

    // Check to be sure this is a valid position
    if (location.position == 0) {
        throw InvalidArgument();
    }
    Node *link;
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    // Set the data
    link->data = entry;
    // If the position is at the tail, change the tail
    if (location.position == tail) {
        link->previous = location.position;
        link->next = NULL;

        location.position->next = link;
        tail = link;
        size++;
    } else {
        // The link's next pointer should point to what the current location
        // next pointer was pointing to
        link->next = location.position->next;
        // The new link's previous pointer should point to the current location
        link->previous = location.position;
        // Change the next link's previous pointer to point
        // to the new link
        location.position->next->previous = link;
        // Set the current location next pointer to the new link
        location.position->next = link;

        size++;
    }
}

// Returns the first element in the list

template<class T>
T& OrderedList<T>::first() const throw (Empty) {
    if (head) {
        return head->data;
    } else {
        throw Empty();
    }

}

//******************************************************
// last function. Returns the last element in the list *
//******************************************************

template<class T>
T& OrderedList<T>::last() const throw (Empty) {
    if (tail) {
        return tail->data;
    } else {
        throw Empty();
    }
}

// Removes an entry from the list.

template<class T>
void OrderedList<T>::extract(const T& entry) {
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
                if (cursor == tail) {
                    tail = tail->previous;
                }
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

//***************************************************************
// removeFirst function. Returns the first element of the list. *
// Throws an empty exception if the list is empty.              *
//***************************************************************

template<class T>
void OrderedList<T>::removeFirst() {
    if (head) {
        Node *cursor = head;
        // If the list has only one element
        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->next;
            head->previous = NULL;
        }
        --size;
        delete cursor;

    }
}

//**************************************************************
// removeLast function. Returns the last element of the list.  *
// Throws an empty exception if the list is empty.             *
//**************************************************************

template<class T>
void OrderedList<T>::removeLast() {
    if (tail) {
        Node *cursor = tail;
        // If the list has only one element
        if (head == tail) {
            head = tail = NULL;
        } else {
            tail = tail->previous;
            tail->next = NULL;
        }
        --size;
        delete cursor;
    }
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename OrderedList<T>::iterator OrderedList<T>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename OrderedList<T>::iterator OrderedList<T>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename OrderedList<T>::iterator OrderedList<T>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename OrderedList<T>::iterator OrderedList<T>::end() const {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// contains function. Returns true if entry is in the list. *
// Otherwise returns false.                                 *
//***********************************************************

template<class T>
bool OrderedList<T>::contains(const T& entry) {
    Node *cursor = head;
    bool found = false;
    // Go through the list until we reach the end
    // or find the entry
    while (!found && cursor != NULL) {
        if (cursor->data == entry) {
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
void OrderedList<T>::clear() {
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

// Returns a string of the list contents
template<class T>
std::string OrderedList<T>::toString() {
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

/*iterator definitions*/

// Default constructor

template<class T>
OrderedList<T>::iterator::iterator() {
}

// Main constructor

template<class T>
OrderedList<T>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/

// Assignment operator

template<class T>
typename OrderedList<T>::iterator& OrderedList<T>::iterator::operator=(const iterator &obj) {
    position = obj.position;
    return *this;
}


// Overloaded != operator. Checks for inequality between passed obj iterator
// and this object iterator

template<class T>
bool OrderedList<T>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}
// Overloaded == operator. Checks for equality between passed obj iterator
// and this object iterator

template<class T>
bool OrderedList<T>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class T>
T& OrderedList<T>::iterator::operator*() {
    return position->data;
}

template<class T>
T* OrderedList<T>::iterator::operator->() {
    return (&*(OrderedList<T>::iterator) * this);
}


// Prefix increments the iterator to the next element

template<class T>
typename OrderedList<T>::iterator& OrderedList<T>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element

template<class T>
typename OrderedList<T>::iterator OrderedList<T>::iterator::operator++(int) {
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
void OrderedList<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template<class T>
void OrderedList<T>::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//****************************************************
// Returns the position of an entry in the list.     *
// If the entry is not in the list, it returns null. *
//****************************************************

template<class T>
typename OrderedList<T>::iterator OrderedList<T>::position(const T& entry) const {
    iterator cursor(head);
    iterator finish(NULL);
    while (*cursor != entry && cursor != finish) {
        cursor++;
    }
    return cursor;
}

#endif	/* ORDEREDLIST_H */


