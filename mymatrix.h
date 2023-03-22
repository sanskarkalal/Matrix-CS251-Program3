/*mymatrix.h*/

// 
// TODO
//
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023


//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>

class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    NumRows = R;
    // create R rows
    Rows = new ROW[R];

    for (int r = 0; r < NumRows; ++r)
    {
        //create C cols
      Rows[r].Cols = new T[C];
      Rows[r].NumCols = C;

      // set all elements to the default value
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
          Rows[r].Cols[c] = T{};
      }
    }

  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a
  // copy of an existing matrix.  Example: this occurs when passing
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
      //copy the number of rows
      NumRows = other.NumRows;
      //create the array of the same size
      Rows = new ROW[other.NumRows];

      //looping through the rows
      for (int r = 0; r < NumRows; ++r)
      {
          //add the same number of columns
          Rows[r].Cols = new T[other.numcols(r)];
          Rows[r].NumCols = other.numcols(r);

          //copy the elements
          for (int c = 0; c < Rows[r].NumCols; ++c)
          {
              Rows[r].Cols[c] = other.Rows[r].Cols[c];
          }
      }

  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }


  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    //check if the columns need to be grown or retained
    if(C> numcols(r)){
        //create a new longer array
        T *newCols = new T[C];

        for(int i=0;i< C;i++){
            if(i<Rows[r].NumCols){
                // copy existing content
                newCols[i] = this->Rows[r].Cols[i];

            }else{
                // set the new cols to default value
                newCols[i]= T{};
            }
        }
        Rows[r].Cols = newCols;
        Rows[r].NumCols = C;
    }
  }


//helper function
  void growColumns(int &r,int &C,ROW* &newRows){
      // check if columns need to be grown
      if(C<Rows[r].NumCols){
          newRows[r].Cols = new T[numcols(r)];

          for(int c=0;c< numcols(r);c++){
              newRows[r].Cols[c] = Rows[r].Cols[c];
          }
          newRows[r].NumCols = Rows[r].NumCols;

      }else{
          newRows[r].Cols = new T[C];
          for(int c=0;c< C;c++){
              if(c< numcols(r)){
                  //copy the contents
                  newRows[r].Cols[c] = Rows[r].Cols[c];

              }else{
                  //set the new columns to default
                  newRows[r].Cols[c] = T{};
              }
          }
          newRows[r].NumCols = C;
      }
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  //
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  //
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");
    //check if the rows need to be increased
    if(NumRows<R){
        ROW* newRows = new ROW[R];
        // looping and dynamically increasing the size
        for(int r=0;r<R;r++){
            // grow cols for existing rows
           if(r<NumRows){
               growColumns(r, C, newRows);
           }else{
               // make new rows and set it to default
               newRows[r].Cols = new T[C];
               for(int c=0;c<C;c++){
                   newRows[r].Cols[c] = T{};
                   newRows[r].NumCols = C;
               }
           }
        }
        NumRows = R;
        Rows = newRows;
    }else{
        // grow existing cols retaining the rows
        for(int r=0;r<NumRows;r++){
            if(C>Rows[r].NumCols){
                growcols(r,C);
            }
        }
    }

  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
      int size =0;
      for(int i=0;i<NumRows;i++){
        size+= Rows[i].NumCols;
      }

      return size;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");


    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");


    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {

    mymatrix<T> result(numrows(),1);
    for(int i=0;i<numrows();i++){
        result.growcols(i, numcols(i));
    }
    //looping through each element and multiply it by the number;
    for(int r=0;r<NumRows;r++){
        for(int c=0;c<Rows[r].NumCols;c++){
            result.Rows[r].Cols[c] = Rows[r].Cols[c] * scalar;
        }
    }


    return result;
  }

  //helper function to check if a matrix is jagged
  bool checkJagged(mymatrix<T> matrix){
      int num = matrix.numcols(0);
    for(int i=1;i<matrix.NumRows;i++){
        if(num != matrix.numcols(i)){
            return false;
        }
    }
      return true;

  }

  // helper function to check if the matrices are compatible
bool checkRectangle(const mymatrix<T>matrix){
      if(this->numcols(0) == matrix.numrows()){
          return true;
      }
      return false;
  }
  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //


  void crossMultiply(int i,const mymatrix<T> &result,const mymatrix<T> &other){
      int val =0;
      //looping through the columns of the other matrix
      for(int j=0;j<other.numcols(0);j++) {
          for (int k = 0; k < other.NumRows; k++) {
              val += Rows[i].Cols[k] * other.Rows[k].Cols[j];
          }
          result(i, j) = val;
          val = 0;
      }
  }



  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    if(!checkJagged(*this)){
        throw invalid_argument("mymatrix is not rectangular");
    }
    if(!checkJagged(other)){
        throw invalid_argument("mymatrix is not rectangular ");
    }
    if(!checkRectangle(other)){
        throw invalid_argument("matrices are not compatible");
    }
    mymatrix<T> result(this->NumRows,other.numcols(0));

    //looping through the rows and multiplying with the other column
    for(int i=0;i<NumRows;i++){
        crossMultiply(i,result,other);
    }


    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
