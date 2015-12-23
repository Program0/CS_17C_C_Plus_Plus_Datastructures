//***********************************************************
// Revised templated class created by Dr. Lehr. Revised by  *
// Marlo Zeroth as assignment 2 for CSC17C. Modified for    *
// use in assignment 4 to compare with the simplevectorlist *
// class for the functions push, pull, getElementAt, and    *
// the [] operator. Comparison is with total number of      *
// operations.                                              *
//***********************************************************

// SimpleVector class template

#ifndef SIMPLEVECTORV2_H
#define SIMPLEVECTORV2_H
#include <iostream>
#include <new>       // Needed for bad_alloc exception
#include <cstdlib>   // Needed for the exit function
using namespace std;

template <class T>
class SimpleVectorArray
{
private:   
   T *aptr;          // To point to the allocated array
   int arraySize;    // Number of elements in the array
   int last;         // Position of last element in vector
   void memError();  // Handles memory allocation errors
   void subError();  // Handles subscripts out of range

public:
   // Default constructor
   SimpleVectorArray()
      { aptr = 0; arraySize = 0; last = 0;}

   // Constructor declaration
   SimpleVectorArray(int);

   // Copy constructor declaration
   SimpleVectorArray(const SimpleVectorArray &);

   // Destructor declaration
   ~SimpleVectorArray();

   // Accessor to return the array size
   int size() const
      { return arraySize; }

   // Accessor to return a specific element
   T getElementAt(int position);

   // Overloaded [] operator declaration
   T &operator[](const int &);

   // Mutator to add one element to the top of the vector
   void push(const T data);

   // Accesor to return the top value of the array and decrease
   // the size by 1
   T pull();

   //Accesor to return the total elements in the vector
   int length() const
   { return last;}

};

//***********************************************************
// Constructor for SimpleVector class. Sets the size of the *
// array and allocates memory for it.                       *
//***********************************************************

template <class T>
SimpleVectorArray<T>::SimpleVectorArray(int s)
{
   arraySize = s;
   // Allocate memory for the array.
   try
   {
      aptr = new T [s];
   }
   catch (bad_alloc)
   {
      memError();
   }

   // Initialize the array.
   for (int count = 0; count < arraySize; count++)
      *(aptr + count) = 0;

   // The first element is the last element
   last = 0;
}

//*******************************************
// Copy Constructor for SimpleVector class. *
//*******************************************

template <class T>
SimpleVectorArray<T>::SimpleVectorArray(const SimpleVectorArray &obj)
{

   // Copy the array size.
   arraySize = obj.arraySize;

   // Allocate memory for the array.
   aptr = new T [arraySize];
   if (aptr == 0)
      memError();

   // Copy the elements of obj's array.
   for(int count = 0; count < arraySize; count++)
      *(aptr + count) = *(obj.aptr + count);

   // Get location of top/last element
   last = obj.last;

}

//**************************************
// Destructor for SimpleVector class.  *
//**************************************

template <class T>
SimpleVectorArray<T>::~SimpleVectorArray()
{
   if (arraySize > 0)
      delete [] aptr;
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template <class T>
void SimpleVectorArray<T>::memError()
{
   cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template <class T>
void SimpleVectorArray<T>::subError()
{
   cout << "ERROR: Subscript out of range.\n";
   exit(EXIT_FAILURE);
}

//*******************************************************
// getElementAt function. The argument is a subscript.  *
// This function returns the value stored at the sub-   *
// cript in the array.                                  *
//*******************************************************

template <class T>
T SimpleVectorArray<T>::getElementAt(int sub)
{


   if (sub < 0 || sub >= arraySize)
      subError();

   return aptr[sub];
}

//*******************************************************
// Overloaded [] operator. The argument is a subscript. *
// This function returns a reference to the element     *
// in the array indexed by the subscript.               *
//*******************************************************

template <class T>
T &SimpleVectorArray<T>::operator[](const int &sub)
{
   int totalArrayOp = 0; // Reset the count for this function counter.
   if (sub < 0 || sub >= arraySize)
      subError();
   // Have three comparisons in if statement for checking
   // bounds. Still constant time.
   totalArrayOp = 3; // 3 Comparison Operations 1:<, 1: >=, 1: ||

   std::cout<<"Total operations in [] operator: " << totalArrayOp << std::endl;

   return aptr[sub];
}

//*******************************************************
// push function. Mutator to add one element to the top *
// of the vector array and increase the array size by 1 *
// and double the vector size.                          *
//*******************************************************

template <class T>
void SimpleVectorArray<T>::push(const T data){

    // The number of operations will change depending on the size of the
    // existing array. We may have to increase it in size. At worst this is
    // a linear time function and at best it is constant time.


    int totalPush = 0; // Reset the count of operations for this function.

    totalPush++; // One comparison operation <
    if(arraySize>0){
        // Test if there is room in the array to add one more element
        // If there is, just add the new data element.

        totalPush++; // 1 comparison operation <
        totalPush++; // 1 arithmetic operation -
        if(last<arraySize-2){

            totalPush++; // 1 comparison ==

            // Test to make sure we are not pointing at null
            // Note program ends if we are out of bounds
            if(aptr==0){                
                memError();
            }
            // Now add the new element and increment the
            // position of the last element.
            totalPush+=2; // 1 increment ++ and 1 memory access []
            aptr[last++] = data;

        }
        // If there is not, double the array size and copy to a new array
        else{

            totalPush+=2; // 1 arithmetic * and 1 assignment =

            // Increase the array size
            arraySize *= 2;

            totalPush+=2; // 1 assignment = and 1 memory operation new


            //Allocate a new array to copy existing array
            T *tempPtr = new T [arraySize];

            totalPush++; // 1 comparison ==

            // Check to make sure it was allocated properly
            if(tempPtr==0){
                memError();
            }

            totalPush++; // 1 assignment = (in for statement)

            // Copy the existing array elements into the new one
            for(int count =0; count<last;count++){
                // 1 comparison <, 1 increment ++, 1 assignment =,
                // 2 memory access []
                totalPush+=5;
                tempPtr[count]=aptr[count];
            }
            // Now add the new element at the end,
            // and increment the position of the last element.
            tempPtr[last++] = data;

            // 1 assignment, 1 increment, 1 memory access
            totalPush+=3;

            // 1 comparison <
            totalPush++;
            // Deallocate the old array.            
            if (arraySize > 0) {
                delete [] aptr;
                // 1 memory access
                totalPush++;
            }

            // Set pointer to the new array.
            aptr = tempPtr;

            // 1 assignment
            totalPush++;

        }


    }
    else{

        // 1 assingment, 1 memory access
        totalPush+=2;
        // Allocate memory for the array.
        aptr = new T [arraySize+1];

        totalPush++; // 1 comparison ==

        // Test to make sure memory was allocated
        if(aptr==0){
            memError();
        }

        // 1 assignment =, 2 increment ++, 1 memory access []
        totalPush+=3;

        // Now add the new element and increment the
        // position of the last element.
        aptr[last++] = data;

        // Increment the array size by 1
        arraySize++;
    }

    std::cout<<"Total operations in push(): " << totalPush << std::endl;

}

//*******************************************************
// pull function. Accessor to remove and return the top *
// element of the vector. Decreases the array size by 1 *
// and if the last element was removed returns 0 (null) *
//*******************************************************

template <class T>
T SimpleVectorArray<T>::pull()
{

    // Function is constanct time

    int totalPull =0; // Reset the counter
    totalPull++; // 1 comparison <

    if(last>0){

        // 1 decrement --, 1 memory access []
        totalPull+=2;

        // Get the element at the end of the array,
        // decrease the position of the last element by 1.

        std::cout<<"Total operations in pull(): "<<totalPull<<std::endl;

        return aptr[--last];
    }

    // If the last element returned was aptr[0], then
    // there is nothing left in the vector. We just return 0.
    return 0;
}

#endif
