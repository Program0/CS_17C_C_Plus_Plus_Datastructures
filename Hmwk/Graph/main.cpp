/* 
 * File:   main.cpp
 * Author: super0
 *
 * Created on December 19, 2015, 9:16 AM
 */

#include <cstdlib>
//#include "pairlist.h"
//#include "graph.h"
#include "vertex.h"
#include "KeyValueList.h"
#include "map.h"

using namespace std;

// Test keyValueList
void testKeyValueList();
void testMap();

int main(int argc, char** argv) {

    //testKeyValueList();
    //testMap();

    Vertex<std::string> vertex;
    vertex.setLabel("new york");
    Vertex<std::string> vertex2("albany");
    vertex.connect(vertex2,15);
    
    return 0;
}

void testMap(){
    // Testing default constructor    
    Map<int,string> map;
    
    cout<<"map is empty? "<<map.isEmpty()?" true\n":"false\n";
    // Testing main constructor
    Map<int,string> map2(15);
    
    cout<<"map2 created with main constructor. Is map2 empty?"<<map2.isEmpty()?" true\n":"false\n";
    cout<<"inserting 12 entries into map\n";
    // Testing the insert function
    for(int i =0;i<12;i++){
        map.insert(i,"number");
    }
    cout<<"map contains "<< map.toString();
    cout<<"map had " << map.totalCollisions() << " collisions\n";
    // Test copy constructor
    Map<int,string> map3(map);
    
    cout<<"map3 constains "<< map3.toString()<<"\n";
    // Test assignment operator
    map2=map3;
    // Testing remove function
    map.remove(0);
    cout<<"\n\ncurrent map size is: "<<map.length()<<"\n";
    map.clear();
}

void testKeyValueList() {

  KeyValueList<int, std::string> mycontainer;

    cout << "\n\n Begin test function for the List<T> class\n";

    // Testing the insert, insert, isEmpty, length, toString functions
    cout << "Testing size of new empty container: " << mycontainer.length() << endl;
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";

    cout << "Testing insert(1), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(1,"banana");
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(2,"apple");
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(4), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(4,"apple");
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(2), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(2,"pear");
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(3), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(3,"peach");
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";
    cout << "Size is " << mycontainer.length() << endl;

    cout << "Testing insert(7), length(), and isEmpty() functions. mycontainer is empty? "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    mycontainer.insert(7,"fig");
    cout << "List contains: " << mycontainer.keyValueToString() << "\n";
    cout << "Size is " << mycontainer.length() << endl << endl;


    int size = mycontainer.length();

    cout << "Testing remove(int), length() and isEmpty() functions \n"
            << "in a for loop with iterations greater than container size.";

    for (int i = 0; i < size + 1; i++) {
        cout << "\nIteration: " << i + 1 << "\n";
        if (!mycontainer.isEmpty()) {
            cout << "\tmycontainer is empty? " << (mycontainer.isEmpty() ? " true\n" : "false\n");
            cout << "\tList size before remove is " << mycontainer.length() << endl;
            cout << "\tRemoving key: " << i + 1 << endl << endl;
            mycontainer.remove(i + 1);
            cout << "\tmycontainer has: " << mycontainer.keyValueToString() << "\n";
        } else {
            cout << "\tmycontainer is empty.\n";
        }

        cout << "\tList size is now: " << mycontainer.length() << endl;
    }
    cout << "\nFinished for loop\n";


    cout << "\nTesting the at reference function for key value pairs.\n";
    cout << "Start with int test = 7. mycontainer.insert(test)\n";
    int test = 7;
    mycontainer.insert(test,"rest");
    cout << "Testing with test = 7. test=mycontainer.at(7). \n";    
    std::string s = mycontainer.at(test);
    cout<< "mycontainter.at(7) is "<<s <<"\n";
    cout<<"Modifying the reference:\n ";
    s= "behest";
    mycontainer.at(test)=s;
    cout<<"value of mycontainer.at(7) is "<<mycontainer.at(test)<<"\n";
    cout<<"mycontainer now has: "<<mycontainer.keyValueToString()<<"\n";
    
    cout << "mycontainer size is " << mycontainer.length() << endl;

    cout << "\nTesting the clear() function: \n";
    mycontainer.clear();
    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");



    cout << "\n\nTesting containsKey(400): " << (mycontainer.containsKey(400) ? " true\n" : "false\n");
    cout << "\n\nTesting containsValue(711): " << (mycontainer.containsValue("fig") ? " true\n" : "false\n");

    cout << "\nTesting assignment operator: container2 = mycontainer\n";
    cout << "Filling mycontainer with ints starting at 42\n";
    size = 5;
    // Fill mycontainer with ints to test copy constructor
    for (int i = 0; i < size; i++) {
        mycontainer.insert(i + 42,"one");
    }


    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");
    cout << "mycontainer has: " << mycontainer.keyValueToString() << "\n";

    KeyValueList<int, std::string> container2;
    container2 = mycontainer;
    cout << "mycontainer size is: " << mycontainer.length() << endl;
    cout << "container2 size is: " << container2.length() << endl;
    cout << "Testing the contents of container2 and mycontainer:\n";
    cout << "mycontainer has: " << mycontainer.keyValueToString() << "\n";
    cout << "container2 has: " << container2.keyValueToString() << "\n";

    cout << "\nTesting the copy constructor.\n";

    cout << "mycontainer size now is " << mycontainer.length()
            << " mycontainer is empty: "
            << (mycontainer.isEmpty() ? " true\n" : "false\n");

    KeyValueList<int, std::string> container3(mycontainer);

    cout << "container3 size is: " << container3.length();
    cout << "\nTesting the contents of mycontainer and container3:\n";
    cout << "mycontainer has: " << mycontainer.keyValueToString() << "\n";
    cout << "container3 has: " << container2.keyValueToString() << "\n";

    cout << "\nEnd of test function for the OrderedList<T> class\n\n";
}