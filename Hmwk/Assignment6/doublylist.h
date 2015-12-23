
#ifndef DOUBLYLIST_H
#define	DOUBLYLIST_H
/*
 * Author: Marlo Zeroth
 * doublyList.h
 *
 * Implements a template doubly linked list data structure. Allows duplicates, 
 * insertion at front, back, and any point in the list. The list is not ordered.
 * Created on: Nov 4, 2015
 *      
 */

#include <new>
#include <string>
#include <sstream>

#include "invalidargument.h"
#include "empty.h"

template<class T>
class DoublyList {
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
    typename DoublyList<T>::iterator position(const T& entry) const;

    /* OList Member variables */
    Node *head; // Reference to first/head node
    Node *tail; // Reference to last/tail node
    int size;


public:

    // iterator class for traversing the list

    class iterator {
    public:
        friend class DoublyList;
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


    // Default constructor
    DoublyList();

    // Main constructor
    DoublyList(const T &entry);

    // Copy constructor
    DoublyList(const DoublyList<T> &obj);

    // Destructor
    ~DoublyList();

    // Overloaded Operators


    DoublyList<T>& operator=(const DoublyList<T> &obj);
    // Oveloaded = operator

    /* Mutators and Accessors */

    void prepend(const T& entry);
    // Adds an entry to the front of the list

    void append(const T& entry);
    // Adds an entry to the back of the list
   
    void insertBefore(DoublyList<T>::iterator position, const T& entry);
    // Inserts an element before the passed parameter
    
    void insertAfter(DoublyList<T>::iterator position, const T& entry);
    // Inserts an element after the passed parameter

    T& first() throw (Empty);
    // Returns the first element in the list

    T& last() throw (Empty);
    // Returns the last element in the list

    iterator begin();
    // Returns a pointer to the beginning of the list.

    iterator begin() const;
    // Returns a pointer to the beginning of the list.

    iterator end();
    // Returns a a null iterator to signify the end of the list.

    iterator end() const;
    // Returns a a null iterator to signify the end of the list.

    bool contains(const T& entry);
    // Returns whether the list contains the passed entry.
    
        
    bool isEmpty()const {return (head == NULL && tail == NULL);}
    // Returns whether the list is empty
        
    std::string toString();
    // Returns a string with the contents of the list

    int length() const {
        return size;
    }
    // Returns the size of the list

    void remove(const T& entry);
    // Removes the passed entry from the list if it exits. Returns
    // true if successful, false otherwise

    void removeFirst();
    // Removes the first element of the list


    void removeLast();
    // Removes the last element of the list


    void clear();
    // Removes all items for the list

};

/*OList Class Constructor and Function Definitions */

// Default constructor

template<class T>
DoublyList<T>::DoublyList() {
    tail = NULL;
    head = NULL;
    size = 0;
}

//****************************************************************
// Main constructor. Adds an entry and increments the size by 1. *
//****************************************************************

template<class T>
DoublyList<T>::DoublyList(const T &entry) {

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
DoublyList<T>::DoublyList(const DoublyList<T> &obj) {
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
DoublyList<T>::~DoublyList() {
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
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T> &obj) {
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
void DoublyList<T>::prepend(const T& input) {
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
void DoublyList<T>::append(const T& input) {
    std::cout << "Appending\n";
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

//************************************************************************
// insertBefore function. Inserts an element before the passed parameter *
//************************************************************************

template<class T>
void DoublyList<T>::insertBefore(DoublyList<T>::iterator location, const T& entry) {

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

//**********************************************************************
// insertAfter function. Inserts an element after the passed parameter *
//**********************************************************************

template<class T>
void DoublyList<T>::insertAfter(DoublyList<T>::iterator location, const T& entry) {
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
T& DoublyList<T>::first() throw (Empty) {
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
T& DoublyList<T>::last() throw (Empty) {
    if (tail) {
        return tail->data;
    } else {
        throw Empty();
    }
}

// Returns a string with list contents
template<class T>
std::string DoublyList<T>::toString() {
    std::string output;
    std::stringstream s;
    Node *cursor = head;
    // Traverse the list adding each link's data to the 
    // string stream
    while (cursor) {
        s << cursor->data << " ";
        cursor = cursor->next;
    }
    // Create a string and return it.
    output = s.str();
    return output;
}

// Removes all entries from the list the matched the given entry
template<class T>
void DoublyList<T>::remove(const T& entry) {
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
void DoublyList<T>::removeFirst() {
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
void DoublyList<T>::removeLast() {
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
typename DoublyList<T>::iterator DoublyList<T>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename DoublyList<T>::iterator DoublyList<T>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename DoublyList<T>::iterator DoublyList<T>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename DoublyList<T>::iterator DoublyList<T>::end() const {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//****************************************************************
// contains function. Returns true if entry is in the list and   *
// moves the found link to the head/front of the list. Otherwise *
// returns false.                                                *
//****************************************************************

template<class T>
bool DoublyList<T>::contains(const T& entry) {
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
                Node *before = cursor->previous;
                Node *after = cursor->next;
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
void DoublyList<T>::clear() {
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
DoublyList<T>::iterator::iterator() {
}

// Main constructor

template<class T>
DoublyList<T>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/
template<class T>
bool DoublyList<T>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}

template<class T>
bool DoublyList<T>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class T>
T& DoublyList<T>::iterator::operator*() {
    return position->data;
}

template<class T>
T* DoublyList<T>::iterator::operator->() {
    return (&*(DoublyList<T>::iterator) * this);
}


// Prefix increments the iterator to the next element

template<class T>
typename DoublyList<T>::iterator& DoublyList<T>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element

template<class T>
typename DoublyList<T>::iterator DoublyList<T>::iterator::operator++(int) {
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
void DoublyList<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template<class T>
void DoublyList<T>::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//****************************************************
// Returns the position of an entry in the list.     *
// If the entry is not in the list, it returns null. *
//****************************************************

template<class T>
typename DoublyList<T>::iterator DoublyList<T>::position(const T& entry) const {
    iterator cursor(head);
    iterator finish(NULL);
    while (*cursor != entry && cursor != finish) {
        cursor++;
    }
    return cursor;
}

#endif	/* DOUBLYLIST_H */


