
#ifndef OLIST_H
#define	OLIST_H
/*
 * OrderedList.h
 *
 *  Created on: Nov 4, 2015
 *      Author: super0
 */

#include <new>

#include "invalidargument.h"
#include "empty.h"

template<class T>
class OList {
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

    // Sorts the vector in ascending order
    void mergeSort(T *array, T *tempArray, int first, int last);
    void mergeArrays(T *array, T *tempArray, int first, int mid, int last);

    // Returns the position of an entry in the list
    typename OList<T>::iterator position(const T& entry) const;

    /* OList Member variables */
    Node *head; // Reference to first/head node
    Node *tail; // Reference to last/tail node
    int size;

    
public:

    // iterator class for traversing the list
    class iterator {
    public:
        friend class OList;
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
    OList();

    // Main constructor
    OList(const T &entry);

    // Copy constructor
    OList(const OList<T> &obj);

    // Destructor
    ~OList();

    // Overloaded Operators

    // Oveloaded = operator
    OList<T>& operator=(const OList<T> &obj);

    /* Mutators and Accessors */

    void insert(const T& entry);

    // Adds an entry to the front of the list
    void prepend(const T& entry);

    // Adds an entry to the back of the list
    void append(const T& entry);

    // Inserts an element before the passed parameter
    void insertBefore(OList<T>::iterator *position, const T& entry);

    // Inserts an element after the passed parameter
    void insertAfter(OList<T>::iterator *position, const T& entry);

    // Returns the first element in the list
    T& first() throw (Empty);

    // Returns the last element in the list
    T& last() throw (Empty);

    // Returns a pointer to the beginning of the list.
    iterator begin();
    iterator begin() const;

    // Returns a a null iterator to signify the end of the list.
    iterator end();
    iterator end() const;

    // Returns whether the list contains the passed entry.
    bool contains(const T& entry);

    // Sorts the list in ascending order
    void sort();

    // Returns the size of the list

    int length() const {
        return size;
    }

    // Removes all items for the list
    void clear();

};

/*OList Class Constructor and Function Definitions */

// Default constructor

template<class T>
OList<T>::OList() {
    tail = NULL;
    head = NULL;
    size = 0;
}

//****************************************************************
// Main constructor. Adds an entry and increments the size by 1. *
//****************************************************************

template<class T>
OList<T>::OList(const T &entry) {

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
OList<T>::OList(const OList<T> &obj) {
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
OList<T>::~OList() {
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
OList<T>& OList<T>::operator=(const OList<T> &obj) {

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

template<class T>
void OList<T>::insert(const T& entry) {
    Node * link;
    // Allocate memory
    try {
        link = new Node;

    } catch (const std::bad_alloc&) {
        memError();
    }
    // Set its data element.
    link->data = entry; 
    link->next = head;    
    head = link;   
}

//****************************************************************
// prepend Function. Adds a element at the beginning of the list *
//****************************************************************

template<class T>
void OList<T>::prepend(const T& input) {
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
void OList<T>::append(const T& input) {
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
void OList<T>::insertBefore(OList<T>::iterator *location, const T& entry) {

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
void OList<T>::insertAfter(OList<T>::iterator *location, const T& entry) {

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
T& OList<T>::first() throw (Empty) {
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
T& OList<T>::last() throw (Empty) {
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
typename OList<T>::iterator OList<T>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class T>
typename OList<T>::iterator OList<T>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename OList<T>::iterator OList<T>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class T>
typename OList<T>::iterator OList<T>::end() const {
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
bool OList<T>::contains(const T& entry) {
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

// This is an inefficient sort. Better sort would be
// to sort the list elements itself rather than copying
// into an array and sorting. Temporary fix.

//***************************************************
// sort function. Sorts the list in ascending order *
//***************************************************

template<class T>
void OList<T>::sort() {
    // We only need to sort if the list has more than one element
    if (head && size > 1) {
        // For sorting the list
        T *array;
        T *tempArray;
        // Allocate memory for the arrays and sort.
        try {
            array = new T[size];
            // Allocate memory for the temporary array
            tempArray = new T[size];

            // Copy the elements into the array
            int index = 0;
            Node *cursor = head;
            // Go through each node and copy
            // into the array
            while (index < size && cursor) {
                // Copy the data into the array
                array[index] = cursor->data;
                // Go to the next node
                cursor = cursor->next;
                index++;
            }

            // Set the first and last positions
            int first = 0;
            int last = size - 1;
            // Now merge sort the arrays
            mergeSort(array, tempArray, first, last);

            // Reset the counters
            index = 0;
            cursor = head;
            // Now replace the elements in the list
            while (index < size && cursor) {
                cursor->data = array[index];
                index++;
                cursor = cursor->next;
            }
            // Deallocate the arrays
            delete[] array;
            delete[] tempArray;

        } catch (const std::bad_alloc&) {
            memError();
        }

    }
}

//***************************************************************************
// clear function. Deallocates each link in the list and sets the size to 0 *
//***************************************************************************

template<class T>
void OList<T>::clear() {
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
OList<T>::iterator::iterator() {
}

// Main constructor
template<class T>
OList<T>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/
template<class T>
bool OList<T>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}

template<class T>
bool OList<T>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class T>
T& OList<T>::iterator::operator*() {
    return position->data;
}

template<class T>
T* OList<T>::iterator::operator->() {
    return (&*(OList<T>::iterator) * this);
}


// Prefix increments the iterator to the next element
template<class T>
typename OList<T>::iterator& OList<T>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element
template<class T>
typename OList<T>::iterator OList<T>::iterator::operator++(int) {
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
void OList<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template<class T>
void OList<T>::subError() const {
    std::cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//****************************************************
// Returns the position of an entry in the list.     *
// If the entry is not in the list, it returns null. *
//****************************************************
template<class T>
typename OList<T>::iterator OList<T>::position(const T& entry) const {
    iterator cursor(head);
    iterator finish(NULL);
    while (*cursor != entry && cursor != finish) {
        cursor++;
    }
    return cursor;
}

// Uses merge sort to sort the list

template<class T>
void OList<T>::mergeSort(T *array, T *tempArray, int first, int last) {
    // Base case
    if (first < last) {
        int mid = first + (last - first) / 2;
        // Divide and conquer. Split into left and right subarrays
        // recursively
        mergeSort(array, tempArray, first, mid);
        mergeSort(array, tempArray, mid + 1, last);
        // Combine both subarrays back into one array
        mergeArrays(array, tempArray, first, mid, last);
    }
}

//***************************************************************
// mergeArrays function. Merges the sub arrays back into one.	*
//***************************************************************

template<class T>
void OList<T>::mergeArrays(T *array, T *tempArray, int first, int mid,
        int last) {
    // To keep track of which indexes have been merged into the tempArray
    int beginHalf1 = first; // subarray1 starting index
    int beginHalf2 = mid + 1; // subarray2 starting index

    // Need to copy array into tempArray to actually sort it. Important!!
    // Book's algorithm did not work for me.
    for (int i = first; i <= last; i++) {
        tempArray[i] = array[i];
    }
    // To keep track of the current element added to tempArray
    int index = first;
    // Need to keep within range of both sub arrays
    while ((beginHalf1 <= mid) && (beginHalf2 <= last)) {
        // Only copy if 1st half element is less than or equal to element in
        // 2nd half
        if (tempArray[beginHalf1] < tempArray[beginHalf2]) {
            array[index] = tempArray[beginHalf1];
            // go the next element in subarray1 to sort
            beginHalf1++;
        } else {
            array[index] = tempArray[beginHalf2];
            // go the next element in subarray 2 to sort
            beginHalf2++;

        }
        // Go to the next elements in both subarrays to be sorted
        index++;
    }

    // Now we need to copy any of the remaining elements in the first
    // subarray into array[]
    while (beginHalf1 <= mid) {
        array[index] = tempArray[beginHalf1];
        index++;
        beginHalf1++;
    }
}

#endif	/* OLIST_H */


