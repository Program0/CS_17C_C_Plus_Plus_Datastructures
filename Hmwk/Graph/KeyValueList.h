/* 
 * File:   KeyValueList.h
 * Author: super0
 *
 * Created on December 21, 2015, 1:33 AM
 */

#ifndef KEYVALUELIST_H
#define	KEYVALUELIST_H

#include <cstdlib>
#include <string>
#include <sstream>

#include "empty.h"
#include "invalidargument.h"

template<class K, class V>
class KeyValueList {
private:

    // Nested struct for key value pairs

    struct Node {
        K key;
        V value;
        Node * next;
    };

    void memError() const;
    // Emits an error message if memory was not allocated for a node

    Node* positionKey(const K& key) const;
    // Returns a pointer to the value associated with the passed key
    // Used by contains(const K& key) and at(const K& key) functions

    Node* positionValue(const V& value) const;
    // Returns a pointer to the value associated with the passed key
    // Used by contains(const K& key) and at(const K& key) functions

    // PairList Member variables
    Node *head;
    unsigned int size;

public:

    class iterator {
    public:
        friend class KeyValueList;
        // Default constructor
        iterator();

        // Prefix increment operator
        iterator& operator++();

        // Postfix increment operator
        iterator operator++(int);

        // Dereference operator- returns reference to value member variable
        std::pair<const K, V&> operator*();

        // Returns the address of the value referred to
        V* operator->();

        // Comparison operator
        bool operator==(const iterator &obj) const;

        // Comparison operator
        bool operator!=(const iterator &obj) const;

    private:
        // Main constructor
        iterator(Node *ptr);
        Node *position;
    };

    KeyValueList();
    // Default constructor

    KeyValueList(K& keyEntry, V& valueEntry);
    // Main constructor

    KeyValueList(const KeyValueList<K, V>& obj);
    // Copy constructor

    ~KeyValueList();
    // Destructor

    KeyValueList<K,V>& operator=(const KeyValueList<K,V>& ojb);
    // Assignment operator

    void insert(const K& key, const V& value);
    // Inserts an entry at the front of the list. O(n). 

    bool remove(const K& key);
    // Removes an key entry and its value from the list. Returns true if successful,
    // false otherwise. O(n).

    void clear();
    // Removes all elements from the list. O(n).    

    unsigned int length()const {
        return size;
    }
    // Returns the size of the list. O(1).

    // Returns a string of the list key elements. O(n).
    std::string keyToString() const;
    
    // Returns a string of the list value elements.
    std::string valueToString() const;
    
    // Returns a string with the key value pairs in the list
    std::string keyValueToString() const;

    // Returns the value associated with the passed key. If not in the list
    // throws an out_of_range exception).
    V& at(const K& key) throw (InvalidArgument);

    bool containsKey(const K& key) const;
    // Returns whether the list contains the passed key.    

    bool containsValue(const V& value) const;
    // Returns whether the list contains the passed value.

    bool isEmpty()const {
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

};

// Default constructor

template<class K, class V>
KeyValueList<K,V>::KeyValueList(){
    size = 0;
    head = NULL;
}


// Main constructor
template<class K, class V>
KeyValueList<K,V>::KeyValueList(K& keyEntry, V& valueEntry){
       Node *link;
    try {
        link = new Node;
        link->key = keyEntry;
        link->value = valueEntry;
        link->next = NULL;

    } catch (const std::bad_alloc&) {
        memError();
    }
    // Set this as the head
    head = link;
}

// Copy constructor - This is O(n) as there are two while loops (really 2n).

template<class K, class V>
KeyValueList<K, V>::KeyValueList(const KeyValueList<K, V>& obj) {
    if (!obj.isEmpty()) {
        size = 0;
        head = NULL;
        // Copy the contents of obj. Note these will be in reverse order
        for (Node *cursor = obj.head; cursor != NULL; cursor = cursor->next) {
            insert(cursor->key, cursor->value);
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

// Destructor

template<class K, class V>
KeyValueList<K, V>::~KeyValueList() {
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

// Overloaded = operator

template<class K, class V>
KeyValueList<K,V>& KeyValueList<K, V>::operator=(const KeyValueList<K,V>& rightHand) {
    if (!rightHand.isEmpty()) {
        // Empty the current list  
        clear();
        // Initialize the member variables
        size = 0;
        head = NULL;

        // Iterate through obj's nodes and create a list
        Node *cursor;
        for (cursor = rightHand.head; cursor != NULL; cursor = cursor->next) {
            insert(cursor->key, cursor->value);
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

// Inserts a key value pair into the list. If the key is already in the list
// this updates the value.
template<class K, class V>
void KeyValueList<K, V>::insert(const K& key, const V& value) {
    // If the list is empty just put it at the front (can't put it elsewhere).
    if (!head) {
        // Create and allocate memory for the new key value pair
        Node *link;
        // Allocate memory
        try {
            link = new Node;
            link->key = key;
            link->value = value;
            link->next = NULL;

        } catch (const std::bad_alloc&) {
            memError();
        }
        // Now point the head and tail to the new link
        head = link;
        size++;

    } else {
        // Test if the key already exists in the list. If it does, just update
        // the value of it, otherwise insert it at the beginning
        Node *cursor = positionKey(key);
        if (cursor) {
            cursor->value = value;
        } else {
            // Create and allocate memory for the new key value pair
            Node * link;
            // Allocate memory
            try {
                link = new Node;
                link->key = key;
                link->value = value;
                link->next = NULL;

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
V& KeyValueList<K, V>::at(const K& key) throw (InvalidArgument) {

    // Get the location node of the key
    Node*cursor = positionKey(key);

    // If we find it return the value associate it with it
    if (cursor) {
        return cursor->value;
    } else {
        throw InvalidArgument();
    }
}

// Removes an entry from the list. 

template<class K, class V>
bool KeyValueList<K, V>::remove(const K& key) {
    // To return if the entry was found and deleted.
    bool deleted = false;
    if (!isEmpty()) {
        // Cursor node to traverse the list
        Node *cursor = head;
        Node *previousNode = NULL;
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
void KeyValueList<K, V>::clear() {
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

// Returns whether the given key is in the list

template<class K, class V>
bool KeyValueList<K, V>::containsKey(const K& key)const {
    Node *cursor = positionKey(key);
    return cursor != NULL;
}

// Returns whether the given value is in the list

template<class K, class V>
bool KeyValueList<K, V>::containsValue(const V& value)const {
    Node *cursor = positionValue(value);
    return cursor != NULL;
}

// Returns a string with the list's key contents

template<class K, class V>
std::string KeyValueList<K, V>::keyToString() const {
    std::string output;
    std::stringstream s;
    Node *cursor = head;
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

// Returns a string with the list's value contents

template<class K, class V>
std::string KeyValueList<K, V>::valueToString() const {
    std::string output;
    std::stringstream s;
    Node *cursor = head;
    // Traverse the list adding each link's data to the 
    // string stream
    while (cursor) {
        s << cursor->value << " ";
        cursor = cursor->next;
    }
    // Create a strip and return it.
    output = s.str();
    return output;
}

// Returns a string with the list's key value pair contents

template<class K, class V>
std::string KeyValueList<K, V>::keyValueToString() const {
    std::string output;
    std::stringstream s;
    Node *cursor = head;
    // Traverse the list adding each link's data to the 
    // string stream
    while (cursor) {
        s << "|" << cursor->key << " " << cursor->value<< " | ";
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
typename KeyValueList<K, V>::iterator KeyValueList<K, V>::begin() {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//*******************************************************************
// begin function. Returns an iterator to the beginning of the list *
//*******************************************************************

template<class K, class V>
typename KeyValueList<K, V>::iterator KeyValueList<K, V>::begin() const {
    // Create an iterator and set its
    // position to the head.
    return iterator(head);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class K, class V>
typename KeyValueList<K, V>::iterator KeyValueList<K, V>::end() {
    // Create an iterator and set its position to the
    // tail.
    return iterator(NULL);
}

//***********************************************************
// end function. Returns an iterator to the end of the list *
//***********************************************************

template<class K, class V>
typename KeyValueList<K, V>::iterator KeyValueList<K, V>::end() const {
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
typename KeyValueList<K, V>::Node* KeyValueList<K, V>::positionKey(const K& key)const {
    Node *cursor = head;

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
typename KeyValueList<K, V>::Node* KeyValueList<K, V>::positionValue(const V& value) const {
    Node *cursor = head;

    while (cursor != NULL) {
        if (value == cursor->value) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return cursor;
}

// Iterator implementation


// Default constructor

template<class K, class V>
KeyValueList<K, V>::iterator::iterator() : position(NULL) {
}

// Main constructor

template<class K, class V>
KeyValueList<K, V>::iterator::iterator(Node *ptr) {
    position = ptr;
}

/*Overloaded operators*/
template<class K, class V>
bool KeyValueList<K, V>::iterator::operator!=(const iterator &obj) const {
    return position != obj.position;
}

template<class K, class V>
bool KeyValueList<K, V>::iterator::operator==(const iterator &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class K, class V>
std::pair<const K, V&> KeyValueList<K, V>::iterator::operator*() {
    std::pair<const K, V&> pair(position->key, position->value);
    return pair;
}

template<class K, class V>
V* KeyValueList<K, V>::iterator::operator->() {
    return &position->value;
}


// Prefix increments the iterator to the next element

template<class K, class V>
typename KeyValueList<K, V>::iterator& KeyValueList<K, V>::iterator::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element

template<class K, class V>
typename KeyValueList<K, V>::iterator KeyValueList<K, V>::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template<class K, class V>
void KeyValueList<K, V>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

#endif	/* KEYVALUELIST_H */

