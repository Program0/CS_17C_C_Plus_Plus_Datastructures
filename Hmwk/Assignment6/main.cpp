/* 
 * File:   main.cpp
 * Author: super0
 *
 * Created on November 11, 2015, 8:54 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "doublylist.h"
#include "queue.h"
#include "singlylist.h"
#include "stack.h"
#include "empty.h"
#include "orderedlist.h"
#include "priorityqueue.h"

using namespace std;

void testSinglyList();
void testDoublyList();
void testOrderedList();
void testCircularlyList();
void testStack();
void testQueue();
void testPriorityQueue();

/*
 * 
 */
int main(int argc, char** argv) {


    //testQueue();
    //testStack();
    //testSinglyList();
    //testOrderedList();
    //testPriorityQueue();
    testDoublyList();

    return 0;
}

void testDoublyList(){
        DoublyList<int> mycontainer;

    cout << "\n\n Begin test function for the List<T> class\n";

    // Testing the insert, isEmpty, length, toString functions
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;
    cout << "List contains: " << mycontainer.toString() << "\n";

    cout << "Testing insert(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.append(1);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(2);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(4), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(4);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.append(2);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(3), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(3);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(7), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(7);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl << endl;


    int size = mycontainer.length();

    cout << "Testing extract(int), first(), last(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";

    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << "\tmycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "\tList size before remove is " << mycontainer.length() << endl;
            cout << "\tFirst of container is " << mycontainer.first() << endl;
            cout << "\tLast of container is " << mycontainer.last() << endl;
            cout << "\tExtracting: " << i + 1 << endl << endl;
            mycontainer.remove(i + 1);
            cout << "\tmycontiner has: " << mycontainer.toString() << "\n";
        } else {
            cout << "\tmycontainer is empty.\n";
        }

        cout << "\tList size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout<<"\nClearing container and filling it with int starting with 5 up to 10\n";
    mycontainer.clear();
    for (int i = 1; i < 7; i++)
        mycontainer.append(i + 4);
    cout<<"mycontainer has: "<<mycontainer.toString()<<"\n";

    cout << "\nTesting removeFirst(),removeLast(), first(), last(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";

    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << "\tmycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "\tList size before remove is " << mycontainer.length() << endl;
            cout << "\tFirst of container is " << mycontainer.first() << endl;
            cout << "\tLast of container is " << mycontainer.last() << endl;
            cout << "\tRemoving First: \n";
            mycontainer.removeFirst();
            cout << "\tmycontainer has: " << mycontainer.toString() << "\n";
            cout << "\tRemoving Last: \n";
            mycontainer.removeLast();
            cout << "\tmycontainer has: " << mycontainer.toString() << "\n";
        } else {
            cout << "\tmycontainer is empty.\n";
        }

        cout << "\tList size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout << "\nTesting the reference for first() and last() functions.\n";
    cout << "Start with int test = 7. mycontainer.insert(test)\n";
    int test = 7;
    mycontainer.append(test);
    cout << "Testing with test = 8. test=mycontainer.front(). mycontainer.front() = 13 \n";
    test = 8;
    test = mycontainer.first();
    mycontainer.first() = 13;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;
    test = 11;
    mycontainer.prepend(test);
    cout << "Back of container is: " << mycontainer.last() << endl;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;
    mycontainer.last() = test;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;

    cout << "mycontainer size is " << mycontainer.length() << endl;

    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");


    cout << "\n\nTesting insertBefore and insertAfter fucntions.\n";
    cout << "\nBegin by inserting ints starting at 13\n";
    for (int i = 0; i < 5; i++) {
        mycontainer.prepend(i + 13);
    }

    cout << "\n\nTesting contains(400): " << (mycontainer.contains(400) ? " true\n" : "false\n");
    cout << "\n\nTesting contains(711): " << (mycontainer.contains(711) ? " true\n" : "false\n");

    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.prepend(i + 42);
    }


    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "mycontainer has: " << mycontainer.toString() << "\n";

    DoublyList<int> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size is: " << container2.length() << endl;
    cout << "Testing the contents of container2 and mycontainer:\n";
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "container2 has: " << container2.toString() << "\n";

    cout << "\nTesting the copy constructor.\n";

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    DoublyList<int> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of mycontainer and container3:\n";
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "container3 has: " << container2.toString() << "\n";

    cout << "\nEnd of test function for the List<T> class\n\n";
}

void testPriorityQueue(){
    PriorityQueue<int> mycontainer;

    cout << "\n\n Begin test function for the PriorityQueue<T> class\n";

    // Testing the enqueue function
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;
    cout << "Testing enqueue(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.enqueue(1);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing enqueue(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.enqueue(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing enqueue(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.enqueue(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing enqueue(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.enqueue(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing enqueue(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.enqueue(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing enqueue(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl << endl;

    int size = mycontainer.length();
    cout << "Testing pop_back(), front(), back(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";
    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << " mycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "PriorityQueue size before pop is " << mycontainer.length() << endl;
            //cout<<"Front of container is " << mycontainer.front()<<endl;
            //cout<<"Back of container is " << mycontainer.back()<<endl;
            //cout << "Popping: " << mycontainer.front() << endl << endl;
            mycontainer.pop_back();
        } else {
            cout << "The PriorityQueue is empty.\n";
        }

        cout << "PriorityQueue size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout << "\nTesting the reference for front() and back() functions.\n";
    cout << "Start with int test = 7. mycontainer.enqueue(test)\n";
    int test = 7;
    mycontainer.enqueue(test);
    cout << "Testing with test = 8. test=mycontainer.front(). mycontainer.front() = 13 \n";
    test = 8;
    test = mycontainer.front();
    mycontainer.front() = 13;
    cout << "Test is now " << test << " front of container is " << mycontainer.front()
            << " back of container is " << mycontainer.back() << endl;
    test = 11;
    mycontainer.enqueue(test);
    cout << "Back of container is: " << mycontainer.back() << endl;
    cout << "Test is now " << test << " front of container is " << mycontainer.front()
            << " back of container is " << mycontainer.back() << endl;
    mycontainer.back() = test;
    cout << "Test is now " << test << " front of container is " << mycontainer.front()
            << " back of container is " << mycontainer.back() << endl;

    cout << "mycontainer size is " << mycontainer.length() << endl;

    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");


    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.enqueue(i + 41);
    }

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    PriorityQueue<int> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size is: " << container2.length() << endl;
    cout << "Testing the contents of container2 and mycontainer using back() and pop_back() functions:\n";
    size = container2.length();
    for (int i = 0; i < size; i++) {
        cout << "Attempting front and pop functions. Iteration: " << i + 1 << "\n";

        // Don't perform the operation if either container is empty. 
        // Output should be the same for both containers
        if (!container2.isEmpty() || !mycontainer.isEmpty()) {
            cout << "\tcontainer2 - front(): " << container2.front()
                    << " back(): " << container2.back() << endl;
            container2.pop_back();
            cout << "\tmycontainer - front(): " << mycontainer.front()
                    << " back(): " << mycontainer.back() << endl;
            mycontainer.pop_back();
        } else {
            cout << "Containers are empty.\n";
        }
    }

    cout << "\nTesting the copy constructor. Filling mycontainer ints\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.enqueue(i + 41);
    }

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    PriorityQueue<int> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of container3 and mycontainer using back() and pop_back() functions:\n";
    size = container3.length();
    for (int i = 0; i < size; i++) {
        cout << "Attempting front and pop functions. Iteration: " << i + 1 << "\n";

        // Don't perform the operation if either container is empty. 
        // Output should be the same for both containers
        if (!container3.isEmpty() || !mycontainer.isEmpty()) {
            cout << "\tcontainer3 - front(): " << container3.front()
                    << " back(): " << container3.back() << endl;
            container3.pop_back();
            cout << "\tmycontainer - front(): " << mycontainer.front()
                    << " back(): " << mycontainer.back() << endl;
            mycontainer.pop_back();
        } else {
            cout << "Containers are empty.\n";
        }
    }
    cout << "\nEnd of test function for the PriorityQueue<T> class\n\n";
}

void testOrderedList() {
    OrderedList<int> mycontainer;

    cout << "\n\n Begin test function for the List<T> class\n";

    // Testing the insert, isEmpty, length, toString functions
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;
    cout << "List contains: " << mycontainer.toString() << "\n";

    cout << "Testing insert(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(1);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(2);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(4), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(4);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(2);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(3), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(3);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(7), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(7);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl << endl;


    int size = mycontainer.length();

    cout << "Testing extract(int), first(), last(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";

    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << "\tmycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "\tList size before remove is " << mycontainer.length() << endl;
            cout << "\tFirst of container is " << mycontainer.first() << endl;
            cout << "\tLast of container is " << mycontainer.last() << endl;
            cout << "\tExtracting: " << i + 1 << endl << endl;
            mycontainer.extract(i + 1);
            cout << "\tmycontiner has: " << mycontainer.toString() << "\n";
        } else {
            cout << "\tmycontainer is empty.\n";
        }

        cout << "\tList size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout<<"\nClearing container and filling it with int starting with 5 up to 10\n";
    mycontainer.clear();
    for (int i = 1; i < 7; i++)
        mycontainer.insert(i + 4);
    cout<<"mycontainer has: "<<mycontainer.toString()<<"\n";

    cout << "\nTesting removeFirst(),removeLast(), first(), last(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";

    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << "\tmycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "\tList size before remove is " << mycontainer.length() << endl;
            cout << "\tFirst of container is " << mycontainer.first() << endl;
            cout << "\tLast of container is " << mycontainer.last() << endl;
            cout << "\tRemoving First: \n";
            mycontainer.removeFirst();
            cout << "\tmycontainer has: " << mycontainer.toString() << "\n";
            cout << "\tRemoving Last: \n";
            mycontainer.removeLast();
            cout << "\tmycontainer has: " << mycontainer.toString() << "\n";
        } else {
            cout << "\tmycontainer is empty.\n";
        }

        cout << "\tList size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout << "\nTesting the reference for first() and last() functions.\n";
    cout << "Start with int test = 7. mycontainer.insert(test)\n";
    int test = 7;
    mycontainer.insert(test);
    cout << "Testing with test = 8. test=mycontainer.front(). mycontainer.front() = 13 \n";
    test = 8;
    test = mycontainer.first();
    mycontainer.first() = 13;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;
    test = 11;
    mycontainer.insert(test);
    cout << "Back of container is: " << mycontainer.last() << endl;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;
    mycontainer.last() = test;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;

    cout << "mycontainer size is " << mycontainer.length() << endl;

    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");


    cout << "\n\nTesting insertBefore and insertAfter fucntions.\n";
    cout << "\nBegin by inserting ints starting at 13\n";
    for (int i = 0; i < 5; i++) {
        mycontainer.insert(i + 13);
    }

    cout << "\n\nTesting contains(400): " << (mycontainer.contains(400) ? " true\n" : "false\n");
    cout << "\n\nTesting contains(711): " << (mycontainer.contains(711) ? " true\n" : "false\n");

    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.insert(i + 42);
    }


    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "mycontainer has: " << mycontainer.toString() << "\n";

    OrderedList<int> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size is: " << container2.length() << endl;
    cout << "Testing the contents of container2 and mycontainer:\n";
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "container2 has: " << container2.toString() << "\n";

    cout << "\nTesting the copy constructor.\n";

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    OrderedList<int> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of mycontainer and container3:\n";
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "container3 has: " << container2.toString() << "\n";

    cout << "\nEnd of test function for the List<T> class\n\n";
}

void testSinglyList() {
    SinglyList<int> mycontainer;

    cout << "\n\n Begin test function for the List<T> class\n";

    // Testing the prepend, append, isEmpty, length, toString functions
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;
    cout << "List contains: " << mycontainer.toString() << "\n";

    cout << "Testing prepend(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(1);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing prepend(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(2);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing prepend(4), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.prepend(4);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing append(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.append(2);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing append(3), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.append(3);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing append(7), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.append(7);
    cout << "List contains: " << mycontainer.toString() << "\n";
    cout << "Size is " << mycontainer.length() << endl << endl;


    int size = mycontainer.length();

    cout << "Testing extract(int), first(), last(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";

    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << "\tmycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "\tList size before remove is " << mycontainer.length() << endl;
            cout << "\tFirst of container is " << mycontainer.first() << endl;
            cout << "\tLast of container is " << mycontainer.last() << endl;
            cout << "\tExtracting: " << i + 1 << endl << endl;
            mycontainer.extract(i + 1);
            cout << "\tmycontiner has: " << mycontainer.toString() << "\n";
        } else {
            cout << "\tmycontainer is empty.\n";
        }

        cout << "\tList size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";


    cout << "\nTesting the reference for first() and last() functions.\n";
    cout << "Start with int test = 7. mycontainer.prepend(test)\n";
    int test = 7;
    mycontainer.prepend(test);
    cout << "Testing with test = 8. test=mycontainer.front(). mycontainer.front() = 13 \n";
    test = 8;
    test = mycontainer.first();
    mycontainer.first() = 13;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;
    test = 11;
    mycontainer.append(test);
    cout << "Back of container is: " << mycontainer.last() << endl;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;
    mycontainer.last() = test;
    cout << "Test is now " << test << " front of container is " << mycontainer.first()
            << " back of container is " << mycontainer.last() << endl;

    cout << "mycontainer size is " << mycontainer.length() << endl;

    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");


    cout << "\n\nTesting insertBefore and insertAfter fucntions.\n";
    cout << "\nBegin by inserting ints starting at 13\n";
    for (int i = 0; i < 5; i++) {
        mycontainer.prepend(i + 13);
    }
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertBefore(13,7)\n";
    mycontainer.insertBefore(13, 7);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertBefore(17,1)\n";
    mycontainer.insertBefore(17, 1);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertBefore(170,21)\n";
    mycontainer.insertBefore(170, 21);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertBefore(15,23)\n";
    mycontainer.insertBefore(15, 23);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";


    cout << "\n\ninsertAfter(2,200)\n";
    mycontainer.insertAfter(2, 200);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertAfter(17,300)\n";
    mycontainer.insertAfter(17, 300);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertAfter(17,300)\n";
    mycontainer.insertAfter(1, 700);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertAfter(17,300)\n";
    mycontainer.insertAfter(21, 710);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "\ninsertAfter(17,300)\n";
    mycontainer.insertAfter(200, 711);
    cout << "mycontainer has: " << mycontainer.toString() << "\n";

    cout << "\n\nTesting contains(400): " << (mycontainer.contains(400) ? " true\n" : "false\n");
    cout << "\n\nTesting contains(711): " << (mycontainer.contains(711) ? " true\n" : "false\n");

    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.prepend(i + 42);
    }


    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "mycontainer has: " << mycontainer.toString() << "\n";

    SinglyList<int> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size is: " << container2.length() << endl;
    cout << "Testing the contents of container2 and mycontainer:\n";
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "container2 has: " << container2.toString() << "\n";

    cout << "\nTesting the copy constructor.\n";

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    SinglyList<int> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of mycontainer and container3:\n";
    cout << "mycontainer has: " << mycontainer.toString() << "\n";
    cout << "container3 has: " << container2.toString() << "\n";

    cout << "\nEnd of test function for the OrderedList<T> class\n\n";
}

void testStack() {
    Stack<int> mycontainer;

    cout << "\n\n Begin test function for the Stack<T> class\n";

    // Testing the push function
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;

    mycontainer.push(1);
    cout << "Testing push(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl;

    mycontainer.push(2);
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl;

    mycontainer.push(2);
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl;

    mycontainer.push(2);
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl;

    mycontainer.push(2);
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl;

    mycontainer.push(2);
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl << endl;

    int size = mycontainer.length();
    cout << "Testing pop(), top(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";
    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << " mycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "Stack size before pop is " << mycontainer.length() << endl;
            cout << "Top of container is " << mycontainer.top() << endl;
            mycontainer.pop();
        } else {
            cout << "The Stack is empty.\n";
        }

        cout << "Stack size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout << "\nTesting the reference for top() function.\n";
    cout << "Start with int test = 7. mycontainer.push(test)\n";
    int test = 7;
    mycontainer.push(test);
    cout << "Testing with test = 8. test=mycontainer.top(). mycontainer.top() = 13 \n";
    test = 8;
    test = mycontainer.top();
    mycontainer.top() = 13;
    cout << "Test is now " << test << " front of container is " << mycontainer.top() << "\n";
    test = 11;
    mycontainer.push(test);
    cout << "Test is now " << test << " top of container is " << mycontainer.top() << "\n";

    mycontainer.top() = test;
    cout << "Test is now " << test << " top of container is " << mycontainer.top() << "\n";


    cout << "\nmycontainer size is " << mycontainer.length() << endl;
    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.push(i + 41);
    }

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    Stack<int> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size now is " << container2.length()
            << " container is empty: "
            << (container2.isEmpty() ? " true\n" : "false\n");

    cout << "Testing the contents of container2 and mycontainer using pop() functions:\n";
    size = container2.length();
    for (int i = 0; i < size; i++) {
        cout << "Attempting front and pop functions. Iteration: " << i + 1 << "\n";

        // Don't perform the operation if either container is empty. 
        // Output should be the same for both containers
        if (!container2.isEmpty() || !mycontainer.isEmpty()) {
            cout << "\tcontainer2 - top(): " << container2.top() << endl;
            container2.pop();
            cout << "\tmycontainer - top(): " << mycontainer.top() << endl;
            mycontainer.pop();
        } else {
            cout << "Containers are empty.\n";
        }
    }

    cout << "\nTesting the copy constructor. Filling mycontainer ints\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.push(i + 41);
    }

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    Stack<int> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of container3 and mycontainer using back() and pop() functions:\n";
    size = container3.length();
    for (int i = 0; i < size; i++) {
        cout << "Attempting front and pop functions. Iteration: " << i + 1 << "\n";

        // Don't perform the operation if either container is empty. 
        // Output should be the same for both containers
        if (!container3.isEmpty() || !mycontainer.isEmpty()) {
            cout << "\tcontainer3 - top(): " << container3.top() << "\n";
            container3.pop();
            cout << "\tmycontainer - front(): " << mycontainer.top() << "\n";
            mycontainer.pop();
        } else {
            cout << "Containers are empty.\n";
        }
    }
    cout << "\nEnd of test function for the Stack<T> class\n\n";
}

void testQueue() {
    Queue<int> mycontainer;

    cout << "\n\n Begin test function for the Queue<T> class\n";

    // Testing the push function
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;
    cout << "Testing push(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.push(1);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.push(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.push(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.push(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.push(2);
    cout << "Size is " << mycontainer.length() << endl;
    cout << "Testing push(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "Size is " << mycontainer.length() << endl << endl;

    int size = mycontainer.length();
    cout << "Testing pop(), front(), back(), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";
    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << " mycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "Queue size before pop is " << mycontainer.length() << endl;
            //cout<<"Front of container is " << mycontainer.front()<<endl;
            //cout<<"Back of container is " << mycontainer.back()<<endl;
            //cout << "Popping: " << mycontainer.front() << endl << endl;
            mycontainer.pop();
        } else {
            cout << "The Queue is empty.\n";
        }

        cout << "Queue size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";

    cout << "\nTesting the reference for front() and back() functions.\n";
    cout << "Start with int test = 7. mycontainer.push(test)\n";
    int test = 7;
    mycontainer.push(test);
    cout << "Testing with test = 8. test=mycontainer.front(). mycontainer.front() = 13 \n";
    test = 8;
    test = mycontainer.front();
    mycontainer.front() = 13;
    cout << "Test is now " << test << " front of container is " << mycontainer.front()
            << " back of container is " << mycontainer.back() << endl;
    test = 11;
    mycontainer.push(test);
    cout << "Back of container is: " << mycontainer.back() << endl;
    cout << "Test is now " << test << " front of container is " << mycontainer.front()
            << " back of container is " << mycontainer.back() << endl;
    mycontainer.back() = test;
    cout << "Test is now " << test << " front of container is " << mycontainer.front()
            << " back of container is " << mycontainer.back() << endl;

    cout << "mycontainer size is " << mycontainer.length() << endl;

    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");


    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.push(i + 41);
    }

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    Queue<int> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size is: " << container2.length() << endl;
    cout << "Testing the contents of container2 and mycontainer using back() and pop() functions:\n";
    size = container2.length();
    for (int i = 0; i < size; i++) {
        cout << "Attempting front and pop functions. Iteration: " << i + 1 << "\n";

        // Don't perform the operation if either container is empty. 
        // Output should be the same for both containers
        if (!container2.isEmpty() || !mycontainer.isEmpty()) {
            cout << "\tcontainer2 - front(): " << container2.front()
                    << " back(): " << container2.back() << endl;
            container2.pop();
            cout << "\tmycontainer - front(): " << mycontainer.front()
                    << " back(): " << mycontainer.back() << endl;
            mycontainer.pop();
        } else {
            cout << "Containers are empty.\n";
        }
    }

    cout << "\nTesting the copy constructor. Filling mycontainer ints\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.push(i + 41);
    }

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    Queue<int> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of container3 and mycontainer using back() and pop() functions:\n";
    size = container3.length();
    for (int i = 0; i < size; i++) {
        cout << "Attempting front and pop functions. Iteration: " << i + 1 << "\n";

        // Don't perform the operation if either container is empty. 
        // Output should be the same for both containers
        if (!container3.isEmpty() || !mycontainer.isEmpty()) {
            cout << "\tcontainer3 - front(): " << container3.front()
                    << " back(): " << container3.back() << endl;
            container3.pop();
            cout << "\tmycontainer - front(): " << mycontainer.front()
                    << " back(): " << mycontainer.back() << endl;
            mycontainer.pop();
        } else {
            cout << "Containers are empty.\n";
        }
    }
    cout << "\nEnd of test function for the Queue<T> class\n\n";
}