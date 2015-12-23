
#ifndef LIST_H
#define	LIST_H
/*
 * Author: Marlo Zeroth
 * List.h
 *
 * Implements a template doubly linked list data structure. Allows duplicates,
 * insertion at front, back, and any point in the list. The list is not ordered.
 * Created on: Nov 4, 2015
 *
 */

#include <new>

#include "invalidargument.h"
#include "empty.h"

template<class T>
class List {
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
    typename List<T>::iterator position(const T& entry) const;

    /* DoublyList Member variables */
    Node *head; // Reference to first/head node
    Node *tail; // Reference to last/tail node
    int size;


public:

    // iterator class for traversing the list
    class iterator {
    public:
        friend class List;
        // Default constructor. Allows .
        iterator();

        // Copy constructor
        //OListiterator(const iterator & obj);

        // Destructor
        //~OListiterator();

        /*Overloaded operators*/

        // Assignment operator
        //iterator& operator = (const OListiterator& obj);

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

    //Constructors and Destructor

    List();
    // Default constructor

    List(const T &entry);
    // Main constructor

    List(const List<T> &obj);
    // Copy constructor

    ~List();
    // Destructor

    // Overloaded Operators

    List<T>& operator=(const List<T> &obj);
    // Oveloaded = operator

    /* Mutators and Accessors */

    void prepend(const T& entry);
    // Adds an entry to the front of the list

    void append(const T& entry);
    // Adds an entry to the back of the list

    void insertBefore(List<T>::iterator *position, const T& entry);
    // Inserts an element before the passed parameter

    void insertAfter(List<T>::iterator *position, const T& entry);
    // Inserts an element after the passed parameter

    T& first() throw (Empty);
    // Returns the first element in the list

    T& last() throw (Empty);
    // Returns the last element in the list

    iterator begin();
    // Returns a pointer to the beginning of the list.

    iterator begin() const;
    // Returns a const iterator to the beginning of the list.

    iterator end();
    // Returns a null iterator to signify the end of the list.

    iterator end() const;
    // Returns a const null iterator to signify the end of the list.

    bool contains(const T& entry);
    // Returns whether the list contains the passed entry.

    int length() const { return size;}
    // Returns the size of the list

    void remove(const T& entry);
    // Removes the passed entry from the list if it exits. Throws
    // an invalid argument if it does not exist.

    void clear();
    // Removes all items for the list
};

/*DoublyList Constructor, Destructor, and Function Definitions */

// Default constructor

template<class T>
List<T>::List() {
    tail = NULL;
    head = NULL;
    size = 0;
}

//****************************************************************
// Main constructor. Adds an entry and increments the size by 1. *
//****************************************************************

template<class T>
List<T>::List(const T &entry) {

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
List<T>::List(const List<T> &obj) {
    std::cout << "copy constructor" << std::endl;

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
List<T>::~List() {
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
List<T>& List<T>::operator=(const List<T> &obj) {

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

//****************************************************************
// prepend Function. Adds a element at the beginning of the list *
//****************************************************************

template<class T>
void List<T>::prepend(const T& input) {
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
void List<T>::append(const T& input) {
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
void List<T>::insertBefore(List<T>::iterator *location, const T& entry) {

    Node *cursor = const_cast<Node*> (location->position);
    // Check to be sure this is a valid position
    if (cursor == 0) {
        throw InvalidArgument("invalid position");
    }
    Node * const link;
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    link->data = entry;
    // If the position is at the tail, change the tail
    if (cursor == head) {
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
    } else {
        Node *prevPtr = head;
        while (prevPtr != 0 && prevPtr->next != cursor) {
            prevPtr = prevPtr->next;
        }
        if (prevPtr == 0) {
            throw InvalidArgument("invalid position");
        }
        prevPtr->next = link;
    }
}

// Inserts an element after the passed parameter

template<class T>
void List<T>::insertAfter(List<T>::iterator *location, const T& entry) {

    // Check to be sure this is a valid position
    if (location == 0) {
        throw InvalidArgument("invalid position");
    }
    Node *link;
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    link->data = entry;
    location->position->next = link;
    link->previous = location.position;
    // If the position is at the tail, change the tail
    if (location->position == tail)
        tail = link;

}

// Returns the first element in the list

template<class T>
T& List<T>::first() throw (Empty) {
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
T& List<T>::last() throw (Empty) {
    if (tail) {
        return tail->data;
    } else {
        throw Empty();
    }
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename List<T>::iterator List<T>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename List<T>::iterator List<T>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename List<T>::iterator List<T>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename List<T>::iterator List<T>::end() const {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//*****************************************************************
// contains function. Returns true if entry is in the list, false *
// otherwise                                                      *
//*****************************************************************

template<class T>
bool List<T>::contains(const T& entry) {
    Node *cursor = head;
    bool found = false;
    // Go through the list until we reach the end
    // or find the entry
    while (!found && cursor != 0) {
        if (cursor->data == entry)
            found = true;        
        cursor = cursor->next;
    }
    return found;
}

template<class T>
void List<T>::remove(const T& entry){

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

    // If it is not in the list throw an exception
    if (cursor == 0)
        throw InvalidArgument("Entry not in the list");

    // If we found it delete it
    if (cursor == head) {
        // If it is at the front of the list, there is no previous
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
}


//***************************************************************************
// clear function. Deallocates each link in the list and sets the size to 0 *
//***************************************************************************

template<class T>
void List<T>::clear() {
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

/*iterator definitions*/

// Default constructor

template<class T>
List<T>::iterator::iterator() {
}

// Main constructor
template<class T>
List<T>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/

// != operator
template<class T>
bool List<T>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}

// == operator
template<class T>
bool List<T>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position
template<class T>
T& List<T>::iterator::operator*() {
    return position->data;
}

template<class T>
T* List<T>::iterator::operator->() {
    return (&*(List<T>::iterator) * this);
}


// Prefix increments the iterator to the next element
template<class T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element
template<class T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
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
void List<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template<class T>
void List<T>::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//****************************************************
// Returns the position of an entry in the list.     *
// If the entry is not in the list, it returns null. *
//****************************************************
template<class T>
typename List<T>::iterator List<T>::position(const T& entry) const {
    iterator cursor(head);
    iterator finish(NULL);
    while (*cursor != entry && cursor != finish) {
        cursor++;
    }
    return cursor;
}

#endif	/* LIST_H */


