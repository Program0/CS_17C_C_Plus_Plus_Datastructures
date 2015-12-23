/*
* Course: CSC17C 48942
* Assignment: 1
* Purpose: This is the implementation for the header file tmatrix.h
* Author: Marlo Zeroth
* Date: 09/07/15*
*/

#include <tmatrix.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

/*********** Constructors and Destrutor ***********/

//Main constructor
 TMatrix::TMatrix(){
     //Allocate memory for columns
     columns = new int[COLUMNSIZE];
     //Fill the dynamic array with random column sizes from 1 to COLUMNSIZE
     for(int i = 0; i<COLUMNSIZE; i++){
         columns[i]=rand()%COLUMNSIZE+1;
     }

     //Allocate memory for columns for each row
     rows = new int*[COLUMNSIZE];
     for(int i = 0; i<COLUMNSIZE;i++){
         rows[i]= new int[columns[i]];
     }

     //Now we fill the allocated memory with random numbers
     for(int row = 0; row < COLUMNSIZE;row++){
         for(int column = 0; column < columns[row]; column++){
             rows[row][column]=rand()%90+10;
         }
     }
 }

 //Destructor
 TMatrix::~TMatrix(){
     //Deallocate the dynamic array holding the number of columns in per row
     delete []columns;
     //Deallocate the dynamic array held at each row (children first)
     for(int i =0; i < COLUMNSIZE; i++){
         delete []rows[i];
     }
     //Deallocate the 2-D dynamic array of arrays (parents last)
     delete []rows;
 }

 /***********Accessor Functions***********/
 void TMatrix::print(){
     //Pad one line before
     cout<<endl;
     // Now print the array one row at a time
     for(int row =0; row < COLUMNSIZE ; row++){
         // We need to print according to the actual number of columns allocated in that row
         for(int column = 0; column < columns[row];column++){
             cout<< rows[row][column]<< " ";
         }
         // Go to the next row and pad with a new line
         cout<<endl;
     }
     //Pad at the end of the function call with a new line
     cout<<endl;
 }


