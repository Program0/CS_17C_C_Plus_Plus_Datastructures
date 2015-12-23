/*
 * Author: Marlo Zeroth
 * Assignment 4
 * September 26, 2015
 * This is the main program file to test the simpleVectorArray
 * and the SimpleVectorList classes. It compares them by the total
 * number of operations for the functions Push and Pull and the
 * overloaded [] operator.
 */




#include <iostream>
#include <simplevectorlist.h>
#include <simplevectorarray.h>

using namespace std;

// Prints out to the console the passed vector
void printVector(const LinkedList &anyVector);

int main()
{
    int vectorSize = 10;
    cout << "All vectors created will have " << vectorSize
         << " elements." << endl;

    cout<<"Test default constructor: myVector"<<endl;
    LinkedList myVector;
    cout<<"myVector is size: "<<myVector.size()<<endl;

    cout<< "Testing push function"<<endl;
    for(int i = 0; i<vectorSize;i++){
        myVector.push(i+5);
        cout<<"myVector is now size: " << myVector.size()<<endl;
    }

    cout<<"\nTesting [] operator. myVector contains:"<<endl;
    for(int i = 0; i<myVector.size();i++){
        cout<< " myVector["<<i<<"]:" <<myVector[i]<<endl;
    }

    // These calls will terminate the program. Uncomment to observe.
    //cout<<"Testing subscript out of range: i = 11" <<endl;
    //cout<<myVector[11]<<endl;
    //cout<<"Testing subscript out of range: i = -1" <<endl;
    //cout<<myVector[-1]<<endl;

    cout<<"Testing pull function."<<endl;
    for(int i = 0; i<vectorSize;i++){
        cout<<"Pulling: "<<myVector.pull()<<endl;
        cout<<"myVector size is: "<< myVector.size()<<endl;
        cout<<"myVector now contains:"<<endl;
        printVector(myVector);
    }

    cout<<"Testing pull from an empty vector." <<endl;
    cout<< "Return value is: " << myVector.pull()<<endl;

    cout<<"Test main constructor: myVector2(1)"<<endl;
    LinkedList myVector2(1);
    myVector2.push(13);
    myVector2.push(17);
    myVector2.push(11);
    cout<<"Adding 13, 17, 11 "<<endl;
    cout<<"\nTesting [] operator. myVector2 contains:"<<endl;
    for(int i = 0; i<myVector2.size();i++){
        cout<<"myVector["<<i<<"]: "<<myVector2[i]<<endl;
    }
    cout<<"\nmyVector2 is size: "<<myVector2.size()<< " and contains" <<endl;
    printVector(myVector2);

    cout<<"Test main and copy constructor: myVector3(myVector2):"<<endl;
    LinkedList myVector3(myVector2);
    cout<<"myVector3 is size: " << myVector3.size() << " and contains:" << endl;
    printVector(myVector3);
    cout<<"Test assignment operator: myVector4 = myVector2"<<endl;
    LinkedList myVector4;
    myVector4 = myVector2;
    cout<<"myVector4 is size: " << myVector4.size() << " and contains:" << endl;
    printVector(myVector4);

    cout<<"Comparing simplevectorlist to simplevectorarray classes:"<<endl;

    LinkedList testVector1;
    SimpleVectorArray <int> testVector2;

    cout<<"Testing the number of operations in the push() functions: "<< endl;

    for(int i = 0 ; i<vectorSize;i++){
        cout<<"The vector push with linked list test: "<<endl;
        testVector1.push(i);
        cout<<endl;

        cout<<"The vector push with array test: "<< endl;
        testVector2.push(i);
        cout<<endl;

    }
    cout<<"Testing the number of operations in the [] operator: "<< endl;
    for(int i = 0 ; i<vectorSize;i++){
        cout<<"The vector [] operator with linked list test: "<<endl;
        testVector1[i];
        cout<<endl;

        cout<<"The vector push ]] operator with array test: "<< endl;
        //testVector2[i];
        cout<<endl;

    }

    cout<<"Testing the number of operations in the pull() functions: "<< endl;
    for(int i = 0 ; i<vectorSize;i++){
        cout<<"The vector pull with linked list test: "<<endl;
        testVector1.pull();
        cout<<endl;

        cout<<"The vector pull with array test: "<< endl;
        testVector2.pull();
        cout<<endl;

    }

    return 0;
}

void printVector(const LinkedList &anyVector){
    for(int i = 0; i<anyVector.size();i++){
        cout<<anyVector[i]<<" ";
    }
    cout<<endl;
}

