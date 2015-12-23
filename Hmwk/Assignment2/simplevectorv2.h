//***********************************************************
// Revised templated class created by Dr. Lehr. Revised by  *
// Marlo Zeroth as assignment 2 for CSC17C.                 *
//***********************************************************

// SimpleVector class template

#ifndef SIMPLEVECTORV2_H
#define SIMPLEVECTORV2_H
#include <iostream>
#include <new>       // Needed for bad_alloc exception
#include <cstdlib>   // Needed for the exit function
using namespace std;

template <class T>
class SimpleVectorV2
{
private:
   T *aptr;          // To point to the allocated array
   int arraySize;    // Number of elements in the array
   int last;         // Position of last element in vector
   void memError();  // Handles memory allocation errors
   void subError();  // Handles subscripts out of range

public:
   // Default constructor
   SimpleVectorV2()
      { aptr = 0; arraySize = 0; last = 0;}

   // Constructor declaration
   SimpleVectorV2(int);

   // Copy constructor declaration
   SimpleVectorV2(const SimpleVectorV2 &);

   // Destructor declaration
   ~SimpleVectorV2();

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
SimpleVectorV2<T>::SimpleVectorV2(int s)
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
SimpleVectorV2<T>::SimpleVectorV2(const SimpleVectorV2 &obj)
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
SimpleVectorV2<T>::~SimpleVectorV2()
{
   if (arraySize > 0)
      delete [] aptr;
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template <class T>
void SimpleVectorV2<T>::memError()
{
   cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template <class T>
void SimpleVectorV2<T>::subError()
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
T SimpleVectorV2<T>::getElementAt(int sub)
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
T &SimpleVectorV2<T>::operator[](const int &sub)
{
   if (sub < 0 || sub >= arraySize)
      subError();
   return aptr[sub];
}

//*******************************************************
// push function. Mutator to add one element to the top *
// of the vector array and increase the array size by 1 *
// and double the vector size.                          *
//*******************************************************

template <class T>
void SimpleVectorV2<T>::push(const T data){

    if(arraySize>0){
        // Test if there is room in the array to add one more element
        // If there is, just add the new data element.
        if(last<arraySize-2){

            // Test to make sure we are not pointing at null
            if(aptr==0){
                memError();
            }
            // Now add the new element and increment the
            // position of the last element.
            aptr[last++] = data;

        }
        // If there is not, double the array size and copy to a new array
        else{

            arraySize *= 2;

            //Allocate a new array to copy existing array
            T *tempPtr = new T [arraySize];
            if(tempPtr==0){
                memError();
            }

            // Copy the existing array elements into the new one
            for(int count =0; count<last;count++){
                tempPtr[count]=aptr[count];
            }
            // Now add the new element at the end,
            // and increment the position of the last element.
            tempPtr[last++] = data;

            // Deallocate the old array.
            if (arraySize > 0) delete [] aptr;

            // Set pointer to the new array.
            aptr = tempPtr;

        }


    }
    else{
        // Allocate memory for the array.
        aptr = new T [arraySize+1];

        // Test to make sure memory was allocated
        if(aptr==0){
            memError();
        }
        // Now add the new element and increment the
        // position of the last element.
        aptr[last++] = data;

        // Increment the array size by 1
        arraySize++;
    }
}

//*******************************************************
// pull function. Accessor to remove and return the top *
// element of the vector. Decreases the array size by 1 *
// and if the last element was removed returns 0 (null) *
//*******************************************************

template <class T>
T SimpleVectorV2<T>::pull()
{
    if(last>0){
        // Get the element at the end of the array,
        // decrease the position of the last element by 1.
        return aptr[--last];
    }

    // If the last element returned was aptr[0], then
    // there is nothing left in the vector. We just return 0.
    return 0;
}

#endif
