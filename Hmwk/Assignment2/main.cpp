#include <cstdlib>
#include <iostream>
#include <simplevectorv1.h>
#include <simplevectorv2.h>

void printVector(SimpleVectorV1 <int> myVector, int numberPerLine);
void printVector(SimpleVectorV2 <float> myVector, int numberPerLine);

int main()
{

    using namespace std;

    // Testing SimpleVectov1 class
    // Test with default constructor
    SimpleVectorV1 <int> myVector;
    // Only show this number of elements per line
    int showPerLine = 10;

    cout<<"Testing SimpleVectorv1. Adding one element at a time and increase the size by 1." << endl;
    cout<< "Pushing one element at a time into vector"<< endl;
    for(int i = 0; i<5;i++){
        myVector.push(i);
        cout<<"The size of myVector is now: "<<myVector.size()
           << " Number of elements: "<< myVector.length() << endl;
        // Show the contents of the vector after the push
        cout<<"myVector contains: ";
        printVector(myVector, showPerLine);
        cout<<endl;
    }

    cout<<endl;

    cout<<"Pulling the last element one at a time from myVector: " << endl;
    for(int i = 0; i<5;i++){
        myVector.pull();
        cout<<"The size of myVector is now: "<<myVector.size()
              << " Number of elements: "<< myVector.length() << endl;
        // Show the contents of the vector after the pull
        cout<<"myVector contains: ";
        printVector(myVector,showPerLine);
        cout<<endl;
    }

    // Now test push and pull functions after main object constructor
    SimpleVectorV1 <int> myVector2(10);
    cout<< "Pushing one element at a time into myVector2"<< endl;
    for(int i = 0; i<5;i++){
        myVector2.push(i);
        cout<<"The size of myVector2 is now: "<<myVector2.size()
           << " Number of elements: "<< myVector2.length() << endl;
        // Show the contents of the vector after the push
        cout<<"myVector2 contains: ";
        printVector(myVector2, showPerLine);
        cout<<endl;
    }

    cout<<endl;

    cout<<"Pulling the last element one at a time from myVector2: " << endl;
    for(int i = 0; i<5;i++){
        myVector2.pull();
        cout<<"The size of myVector2 is now: "<<myVector2.size()
              << " Number of elements: "<< myVector2.length() << endl;
        // Show the contents of the vector after the pull
        cout<<"myVector2 contains: ";
        printVector(myVector2,showPerLine);
        cout<<endl;
    }

    cout<<endl;

    // Testing SimpleVectov2 class
    // Test with default constructor
    SimpleVectorV2 <float> myVector3;

    cout<<"Testing SimpleVectorv2 class. Adding one element at a time and increase the size by 1." << endl;
    cout<< "Pushing one element at a time into myVector3"<< endl;
    for(int i = 0; i<5;i++){
        myVector3.push(static_cast<float>(i)+0.5);
        cout<<"The size of myVector3 is now: "<<myVector3.size()
           << " Number of elements: "<< myVector3.length() << endl;
        // Show the contents of the vector after the push
        cout<<"myVector3 contains: ";
        printVector(myVector3, showPerLine);
        cout<<endl;
    }

    cout<<endl;

    cout<<"Pulling the last element one at a time from myVector3: " << endl;
    for(int i = 0; i<5;i++){
        myVector3.pull();
        cout<<"The size of myVector3 is now: "<<myVector3.size()
              << " Number of elements: "<< myVector3.length() << endl;
        // Show the contents of the vector after the pull
        cout<<"myVector3 contains: ";
        printVector(myVector3,showPerLine);
        cout<<endl;
    }

    // Now test push and pull functions after main object constructor
    SimpleVectorV2 <float> myVector4(10);
    cout<< "Pushing one element at a time into myVector4"<< endl;
    for(int i = 0; i<5;i++){
        myVector4.push(static_cast<float>(i)+0.5);
        cout<<"The size of myVector4 is now: "<<myVector4.size()
           << " Number of elements: "<< myVector4.length() << endl;
        // Show the contents of the vector after the push
        cout<<"myVector4 contains: ";
        printVector(myVector4, showPerLine);
        cout<<endl;
    }

    cout<<endl;

    cout<<"Pulling the last element one at a time from myVector4: " << endl;
    for(int i = 0; i<5;i++){
        myVector4.pull();
        cout<<"The size of myVector4 is now: "<<myVector4.size()
              << " Number of elements: "<< myVector4.length() << endl;
        // Show the contents of the vector after the pull
        cout<<"myVector4 contains: ";
        printVector(myVector4,showPerLine);
        cout<<endl;
    }

    cout<<endl;

    return 0;
}

void printVector(SimpleVectorV1 <int> myVector, int numberPerLine){
    // Output the contents
    std::cout<<endl;
    for(int i =0; i<myVector.length();i++){
        std::cout<<myVector[i]<<" ";
        if(i%numberPerLine==(numberPerLine-1)){
            std::cout<<"\n";
        }
    }
    std::cout<<endl;
}

void printVector(SimpleVectorV2 <float> myVector, int numberPerLine){
    // Output the contents
    std::cout<<endl;
    for(int i =0; i<myVector.length();i++){
        std::cout<<myVector[i]<<" ";
        if(i%numberPerLine==(numberPerLine-1)){
            std::cout<<"\n";
        }
    }
    std::cout<<endl;
}
