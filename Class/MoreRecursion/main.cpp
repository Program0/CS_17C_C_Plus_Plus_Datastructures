/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 23, 2015, 8:27 PM
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
int gcd(int,int);
void hanoi(int,char,char,char);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Test out the greatest common denominator
    int num=78;
    int den=210;
    int gcdnum=gcd(num,den);
    cout<<num<<"/"<<den<<"="<<num/gcdnum<<"/"<<den/gcdnum<<endl;
    //Testing the tower of hanoi
    hanoi(3,'A','B','C');
    //Exit stage right
    return 0;
}

int gcd(int m,int n){
    if(m==0)return n;
    if(m>=n)return gcd(m%n,n);
    return gcd(n%m,m);
}

void hanoi(int nDisk,char src,char spare,char dest){
    if(nDisk>1)hanoi(nDisk-1,src,dest,spare);
    cout<<"Move -> "<<src<<" to "<<dest<<endl;
    if(nDisk>1)hanoi(nDisk-1,spare,src,dest);
}