/* 
 * File:   main.cpp
 * Author: super0
 *
 * Created on October 11, 2015, 12:36 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>

//#include "olist.h"
#include "tlist.h"
//#include "sample.hpp"
#include "stack.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
 cout<<"Hello World!!!!!"<<endl;
    string s;
    
    TList<float> myList;
    myList.prepend(.1);        
    myList.prepend(1.5);
    myList.prepend(-.2);
    myList.prepend(6.5);
    myList.prepend(-.2);
    
    TList<float>::iterator itr;
    for(itr = myList.begin();itr!=myList.end();itr++){
        cout<<*itr<<" ";
    }
    cout<<"remove 6.5 sucessful? "<< myList.remove(-.2) << "\n";
    for(itr = myList.begin();itr!=myList.end();itr++){
        cout<<*itr<<" ";
    }
    
    Stack<int> mystack;
    cout<<"\nStack is empty: "<<mystack.isEmpty()<<"\n";
    mystack.push(1);
    mystack.push(3);
    cout<<"\nStack is empty: "<<mystack.isEmpty()<<"\n";
    cout<<"\n Top element: "<<mystack.top()<<"\n";
    int i = mystack.top();
    cout<<"i is: "<<i<<"\n";
    mystack.pop();
    cout<<"Poping the stack: "<<mystack.pop()<<" i is now: "<<i<<"\n";
    //cout<<"List contains: "<<myList.toString()<<endl;
    //myList.remove(2);
    //cout<<"List contains: "<<myList.toString()<<endl;    
    //Sample<int> newList;
    //newList = myList;
    //cout<<"length of newList "<<newList.length()<<endl;;
    //cout<<"At position 2: "<<newList[1]<<endl;
    //cout<<"At position 1: "<<newList[0]<<endl;
    //cout<<"At position 4: "<<newList[3]<<endl;
    //cout<<"List size now: "<<newList.length()<<endl;;
    //cout<<"At position 3: "<<newList[2]<<endl;
    /*
    OListIterator<int> begin = myList.begin();
    OListIterator<int> end = myList.end();
    
    while(begin!=end){
        cout<<"Item: "<<*begin << " ";
        begin++;
    }
    
     */
    //myList.clear();
    //cout<<"List size now: "<<myList.length()<<endl;


    return 0;
}

