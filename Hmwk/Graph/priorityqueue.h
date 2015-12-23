/* 
 * File:   priorityqueue.h
 * Author: super0
 * Class implementing a priority queue
 */


#ifndef PRIORITYQUEUE_H
#define	PRIORITYQUEUE_H

#include "orderedlist.h"
#include "empty.h"

template<class T>
class PriorityQueue {
public:

    // Default constructor
    PriorityQueue();

    // Copy constructor
    PriorityQueue(const PriorityQueue<T>& obj);

    // Overloaded = operator
    PriorityQueue<T>& operator=(const PriorityQueue<T> &obj);

    // Enqueues an entry into the queue
    void enqueue(const T& entry);

    // Removes the entry at the back of the queue
    void pop_back();
    
    // Removes the entry at the front of the queue
    void pop_front();

    // Returns a reference to the back
    T& front() throw (Empty);

    // Returns a reference to the back
    T& back() throw (Empty);
    
    // Returns the number of stored items in the queue
    unsigned int length() const;
    
    // Returns whether the queue is empty
    bool isEmpty() const {return contents.isEmpty();}
    
    // Clears the contents of the queue
    void clear(){contents.clear();}
    
    private:
        OrderedList<T> contents;
};

template<class T>
PriorityQueue<T>::PriorityQueue(){
    
}

template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& obj){
    contents = obj.contents;
}

template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator =(const PriorityQueue<T>& obj){
    contents.clear();
    contents = obj.contents;
}

template<class T>
void PriorityQueue<T>::enqueue(const T& entry){
    contents.insert(entry);
}

template<class T>
void PriorityQueue<T>::pop_back(){
    contents.removeLast();
}

template<class T>
void PriorityQueue<T>::pop_front(){
    contents.removeFirst();
}

template<class T>
T& PriorityQueue<T>::front() throw (Empty){
    if(!contents.isEmpty()){
        return contents.first();
    }
    else{
        throw Empty();
    }    
}

template<class T>
T& PriorityQueue<T>::back() throw (Empty){
    if(!contents.isEmpty()){
        return contents.last();
    }
    else{
        throw Empty();
    }    
}

template<class T>
unsigned int PriorityQueue<T>::length() const {
    unsigned int size;
    size = contents.length();
    return size;
}

#endif	/* PRIORITYQUEUE_H */

