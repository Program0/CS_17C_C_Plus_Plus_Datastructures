//System Libraries
#include <iostream>
#include <cstdlib>
#include <tmatrix.h>
#include <tmatrixtemplate.h>

using namespace std;

//Execution Begins Here
int main(){

    //Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

    //Set the precision for cout so that float show only two decimal places.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout<<"Testing tmatrix class. It uses int type for the array member variable." << endl;
    TMatrix mymatrix;
    mymatrix.print();

    cout<<"Testing the template with ints: "<<endl;

    TMatrixTempl<int> myMatrixTemp;
    myMatrixTemp.print();

    cout<<"Testing the template with floats: "<<endl;

    TMatrixTempl<float>myFloatMatrix;
    myFloatMatrix.print();

    return 0;
}

