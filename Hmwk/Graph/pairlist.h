/* 
 * File:   pairlist.h
 * Author: Marlo Zeroth
 * Implements a template singly linked list for key value pair. The data 
 * structure does allow duplicates and is not ordered.
 * Created on November 11, 2015, 10:05 PM
 */

#ifndef PAIRLIST_H
#define	PAIRLIST_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>

#include "empty.h"
#include "KeyValueNode.h"
#include "pairlistiterator.h"

// Forward declare the KeyValueNode
template <class K, class V> class KeyValueNode;

template<class K, class V>
class PairList {
public:   

    // Forward declare PairListIterator
    typedef PairListIterator<K, V> iterator;
    friend class PairListIterator<K, V>;

    PairList() : head(NULL) {
    }
    // Default constructor

    PairList(K& keyEntry, V& valueEntry);
    // Main constructor

    PairList(const PairList& obj);
    // Copy constructor

    ~PairList();
    // Destructor

    PairList<K,V>& operator = (const PairList<K,V>& ojb);

    void insert(const K& key, const V& value);
    // Inserts an entry at the front of the list. O(n). 

    bool remove(const K& key);
    // Removes an entry in the list. Returns true if successful,
    // false otherwise. O(n).

    void clear();
    // Removes all elements from the list. O(n).    

    unsigned int length()const {
        return size;
    }
    // Returns the size of the list. O(1).

    // Returns a string of the list key elements. O(n).
    std::string keyToString();

    // Returns the value associated with the passed key. If not in the list
    // throws an out_of_range exception).
    V& at(const K& key) throw (std::out_of_range);

    bool containsKey(const K& key);
    // Returns whether the list contains the passed key.    

    bool containsValue(const V& value);
    // Returns whether the list contains the passed value.

    bool isEmpty() {
        return head == NULL;
    }
    // Returns whether the list is empty or not

    iterator begin();
    // Returns a pointer to the beginning of the list. O(1).

    iterator begin() const;
    // Returns a pointer to the beginning of the list. O(1).

    iterator end();
    // Returns a null iterator to signify the end of the list. O(1).

    iterator end() const;
    // Returns a null iterator to signify the end of the list. O(1).

private:
    void memError() const;
    // Emits an error message if memory was not allocated for a node

    KeyValueNode<K, V>* positionKey(const K& key);
    // Returns a pointer to the value associated with the passed key
    // Used by contains(const K& key) and at(const K& key) functions

    KeyValueNode<K, V>* positionValue(const V& value);
    // Returns a pointer to the value associated with the passed key
    // Used by contains(const K& key) and at(const K& key) functions

    // PairList Member variables
    KeyValueNode<K, V> *head;
    unsigned int size;
};

// Main constructor

template<class K, class V>
PairList<K, V>::PairList(K& key, V& value) {
    KeyValueNode<K, V> *link = new KeyValueNode<K, V>(key, value, NULL);
    // Set this as the head
    head = link;
}

// Copy constructor - This is O(n) as there are two while loops (really 2n).

template<class K, class V>
PairList<K, V>::PairList(const PairList & obj) {
    KeyValueNode<K, V> *cursor = obj.head;
    // Go through obj link's and copy each data element
    // into new links
    for (cursor; cursor != NULL; cursor = cursor->next) {
        insert(cursor->key, cursor->value);
    }
    // Now we reverse it to ensure it is in the correct order
    KeyValueNode<K, V> *tempFirst = 0;
    cursor = head;
    KeyValueNode<K, V> *tempNext;

    // Note code to reverse nodes found at: http://www.panix.com/~elflord/cpp/list_howto/

    // Iterate through the list/stack and swap nodes
    // to reverse the list/stack
    while (cursor) {
        // Store the address of the next node
        tempNext = cursor->next;

        // Now we swap the order of the nodes
        cursor->next = tempFirst;
        tempFirst = cursor;

        // Advance to the next two nodes to swap
        cursor = tempNext;
    }
}

template<class K, class V>
PairList<K, V>::~PairList() {
    KeyValueNode<K, V> *cursor = head;
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

template<class K, class V>
void PairList<K, V>::insert(const K& key, const V& value) {
    // If the list is empty just put it at the front (can't put it elsewhere).
    if (!head) {
        // Create and allocate memory for the new key value pair
        KeyValueNode<K, V> * link;
        // Allocate memory
        try {
            link = new KeyValueNode<K, V>(key, value, NULL);

        } catch (const std::bad_alloc&) {
            memError();
        }
        // Now point the head and tail to the new link
        head = link;
        size++;

    } else {
        // Test if the key already exists in the list. If it does, just update
        // the value of it, otherwise insert it at the beginning
        KeyValueNode<K, V> *cursor = positionKey(key);
        if (cursor) {
            cursor->value = value;
        } else {
            // Create and allocate memory for the new key value pair
            KeyValueNode<K, V> * link;
            // Allocate memory
            try {
                link = new KeyValueNode<K, V>(key, value, NULL);

            } catch (const std::bad_alloc&) {
                memError();
            }
            link->next = head;
            // Now point the head to the new link
            head = link;
            size++;
        }
    }
}

// Returns the value associated with the give key if it is the list. Throws
// an out_of_range exception if given key is not in the list.

template<class K, class V>
V& PairList<K, V>::at(const K& key) throw (std::out_of_range) {

    // Get the location node of the key
    KeyValueNode<K, V> *cursor = positionKey(key);

    // If we find it return the value associate it with it
    if (cursor) {
        return cursor->value;
    } else {
        throw std::out_of_range("out of range");
    }
}

// Removes an entry from the list. 

template<class K, class V>
bool PairList<K, V>::remove(const K& key) {
    // To return if the entry was found and deleted.
    bool deleted = false;
    if (!isEmpty()) {
        // Cursor node to traverse the list
        KeyValueNode<K, V> *cursor = head;
        KeyValueNode<K, V> *previousNode = NULL;
        // Test the first node to see if the entry is there.
        if (head->key == key) {
            // Set the next node to be the new head/first node
            head = head->next;
            // Delete the node with the entry
            delete cursor;
            cursor = NULL;
            deleted = true;
            --size;
        }// If not then go through the rest of the nodes and delete the node
            // that contains the key if it exists in the list.
        else {
            // Stop when we have we reached the end of the list
            while (!deleted && cursor != NULL) {
                if (cursor->key == key) {
                    // We found it. Now delete it.                    
                    deleted = true;

                    // Delete the node
                    previousNode->next = cursor->next;
                    delete cursor;
                    cursor = NULL;
                    --size;
                } else {
                    previousNode = cursor;
                    cursor = cursor->next; // Go to the next node
                }
            }
        }
    }
    return deleted;
}

// Removes all entries from the list

template<class K, class V>
void PairList<K, V>::clear() {
    KeyValueNode<K, V> *cursor = head;
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

// Returns whether the given key is in the list

template<class K, class V>
bool PairList<K, V>::containsKey(const K& key) {
    KeyValueNode<K, V> *cursor = positionKey(key);
    return cursor != NULL;
}

// Returns whether the given value is in the list

template<class K, class V>
bool PairList<K, V>::containsValue(const V& value) {
    KeyValueNode<K, V> *cursor = positionValue(value);
    return cursor != NULL;
}

// Returns a string with the list's contents

template<class K, class V>
std::string PairList<K, V>::keyToString() {
    std::string output;
    std::stringstream s;
    KeyValueNode<K, V> *cursor = head;
    // Traverse the list adding each link's data to the 
    // string stream
    while (cursor) {
        s << cursor->key << " ";
        cursor = cursor->next;
    }
    // Create a strip and return it.
    output = s.str();
    return output;
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class K, class V>
typename PairList<K, V>::iterator PairList<K, V>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class K, class V>
typename PairList<K, V>::iterator PairList<K, V>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class K, class V>
typename PairList<K, V>::iterator PairList<K, V>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class K, class V>
typename PairList<K, V>::iterator PairList<K, V>::end() const {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

/*Utility Functions*/


//********************************************************
// positionKey function. Returns the position of a given *
// key if it exists in the list. Returns null otherwise. *
//********************************************************

template<class K, class V>
KeyValueNode<K, V>* PairList<K, V>::positionKey(const K& key) {
    KeyValueNode<K, V> *cursor = head;

    while (cursor != NULL) {
        if (key == cursor->key) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return cursor;
}

//**********************************************************
// positionValue function. Returns the position of a value *
// key if it exists in the list. Returns null otherwise.   *
//**********************************************************

template<class K, class V>
KeyValueNode<K, V>* PairList<K, V>::positionValue(const V& value) {
    KeyValueNode<K, V> *cursor = head;

    while (cursor != NULL) {
        if (value == cursor->value) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return cursor;
}


//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template<class K, class V>
void PairList<K, V>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

#endif	/* PAIRLIST_H */

