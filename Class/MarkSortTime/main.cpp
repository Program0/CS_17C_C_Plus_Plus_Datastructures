/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 16, 2015, 9:01 AM
 * Purpose:  Example Linear Search/Mark Sort
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void filAray(int [],int);
void prntAry(int [],int,int);
int linSrch(int[],int,int);
void markSrt(int [],int);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare variables
    const int SIZE=200000;
    int array[SIZE];
    //Fill the array
    filAray(array,SIZE);
    //Print the array
    //prntAry(array,SIZE,10);
    //Sort the Array
    int beg=time(0);
    markSrt(array,SIZE);
    int end=time(0);
    cout<<"The array of size "<<SIZE<<" took "<<end-beg<<"(secs)"<<endl;
    //Print again
    //prntAry(array,SIZE,10);
    //Exit Stage Right!
    return 0;
}

int linSrch(int a[],int n,int val){
    for(int i=0;i<n;i++){
        if(a[i]==val)return i;
    }
    return -1;
}

void markSrt(int a[],int n){
    for(int pos=0;pos<n-1;pos++){
        for(int lst=pos+1;lst<n;lst++){
            if(a[pos]>a[lst]){
                int temp=a[pos];
                a[pos]=a[lst];
                a[lst]=temp;
            }
        }
    }
}

void prntAry(int a[],int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        if(i%perLine==perLine-1)cout<<endl;
    }
    cout<<endl;
}

void filAray(int a[],int n){
    for(int i=0;i<n;i++){
        a[i]=rand();
    }
}