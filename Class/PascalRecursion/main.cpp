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
int rcoeff(int,int,int);
int ** rcoeff(int,int);
unsigned int rfib(unsigned int);

//Execution begins here
int main(int argc, char** argv) {
    //Declare variables
    int nRows=20;
    //Loop on rows and columns
    for(int row=1;row<=nRows;row++){
        for(int col=1;col<=row;col++){
            cout<<rcoeff(row,col,nRows)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    //Loop on rows and columns
    int **a=rcoeff(nRows,nRows);
    for(int row=0;row<nRows;row++){
        for(int col=0;col<=row;col++){
            cout<<a[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    //For the fibonacci
    unsigned int nFib=47;
    for(unsigned int i=1;i<=nFib;i++){
        cout<<rfib(i)<<" ";
    }
    cout<<endl;
    //Delete the allocated array
    for(int i=0;i<nRows;i++){
        delete []a[i];
    }
    delete []a;
    //Exit stage right
    return 0;
}

unsigned int rfib(unsigned int n){
    if(n<=2)return 1;
    return rfib(n-1)+rfib(n-2);
}

int rcoeff(int r,int c,int limit){
    static int count;
    count++;
    if(r<1||c<1)return 0;
    if(c==1)return 1;
    if(r==c)return 1;
    if(r==limit&&c==limit-1)cout<<endl<<"r="<<r<<"c="<<c<<"count="<<count<<endl;
    return rcoeff(r-1,c-1,limit)+rcoeff(r-1,c,limit);
}

int ** rcoeff(int r,int c){
    //Allocate an array
    int **array=new int*[r];
    for(int i=0;i<r;i++){
        array[i]=new int[c];
    }
    //Fill up the coefficient matrix
    for(int row=0;row<r;row++){
        for(int col=0;col<=row;col++){
            if(row==col)array[row][col]=1;
            else if(col==0)array[row][col]=1;
            else array[row][col]=array[row-1][col-1]+array[row-1][col];
        }
    }
    return array;
}