#ifndef TMATRIX_H
#define TMATRIX_H

class TMatrix {
public:
    /***********Constructors and Destructor***********/
    TMatrix();
    //Default constructor

    ~TMatrix();
    //Destructor

    /***********Accessors***********/
    void print();

private:
    const int COLUMNSIZE = 10;
    // Default size of the rows and columns for the matrix
    int *columns;
    // Dynamic array to hold the number of columns at each row (size of the dynamic array at that element)
    int **rows;
    // 2-D Dymanic array to hold the actual data elements of the matrix.
    // The number of columns for each row is preset by the elements of from *columns dynamic array above
};

#endif // TMATRIX_H

