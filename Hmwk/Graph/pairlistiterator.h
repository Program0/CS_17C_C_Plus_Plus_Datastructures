/* 
 * File:   singlylistiterator.h
 * Author: super0
 *
 * Created on December 19, 2015, 8:41 AM
 */

#ifndef PAIRLISTITERATOR_H
#define	PAIRLISTITERATOR_H

#include "pairlist.h"
#include "KeyValueNode.h"

template <typename K, typename V> class PairList;

template<class K, class V>
class PairListIterator {
public:
    friend class PairList<K, V>;
    // Default constructor
    PairListIterator();

    // Prefix increment operator
    PairListIterator<K, V>& operator++();

    // Postfix increment operator
    PairListIterator<K, V> operator++(int);

    // Dereference operator- returns reference to value member variable
    std::pair<const K, V&> operator*();

    // Returns the address of the value referred to
    V* operator->();

    // Comparison operator
    bool operator==(const PairListIterator &obj) const;

    // Comparison operator
    bool operator!=(const PairListIterator &obj) const;

private:
    // Main constructor
    PairListIterator(KeyValueNode<K, V> *ptr);
    KeyValueNode<K, V> *position;
};

// Iterator implementation

// Default constructor

template<class K, class V>
PairListIterator<K, V>::PairListIterator() : position(NULL) {
}

// Main constructor

template<class K, class V>
PairListIterator<K, V>::PairListIterator(KeyValueNode<K, V> *ptr) {
    position = ptr;
}

/*Overloaded operators*/
template<class K, class V>
bool PairListIterator<K, V>::operator!=(const PairListIterator<K, V> &obj) const {
    return position != obj.position;
}

template<class K, class V>
bool PairListIterator<K, V>::operator==(const PairListIterator<K, V> &obj) const {
    return position == obj.position;
}

// Dereferences the pointer and returns value pointed by position

template<class K, class V>
std::pair<const K, V&> PairListIterator<K, V>::operator*() {
    std::pair<const K, V&> pair(position->key, position->value);
    return pair;
}

template<class K, class V>
V* PairListIterator<K, V>::operator->() {
    return &position->value;
}


// Prefix increments the iterator to the next element

template<class K, class V>
PairListIterator<K, V>& PairListIterator<K, V>::operator++() {
    position = position->next;
    return *this;
}


// Postfix increments the iterator to the next  element

template<class K, class V>
PairListIterator<K, V> PairListIterator<K, V>::operator++(int) {
    PairListIterator temp = *this;
    ++(*this);
    return temp;
}

#endif	/* PAIRLISTITERATOR_H */

