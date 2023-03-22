#include <iostream>
#include "iomanip"
using namespace std;

#include "mymatrix.h"



bool numrows_test1(){
    mymatrix<int> M;
    if(M.numrows() == 4){
        return true;
    }else{
        return false;
    }
}

bool numrows_test2(){
    mymatrix<int>M(10,10);
    if(M.numrows()==10){
        return true;
    }else{
        return false;
    }
}

bool numcols_test(){
    mymatrix<int> M(2,5);

    if(M.numcols(0)== 5){
        return true;
    }else{
        return false;
    }
}

bool numcols_exception_test(){
    try{
        mymatrix<int> M(5,3);

        cout<< M.numcols(10);
        // should throw an exception


        cout << "numcols exception test failed: "
             << "out of bounds row number did not throw exception"
             << endl;
        return false;
    }
    catch(...){
        return true;
    }
}

bool growcols_test1(){
    mymatrix<int> M;
    M.growcols(1,5);
    //increases the number of columns on the second row to 5
    if(M.numcols(1) == 5){
        return true;
    }else{
        return false;
    }
}

bool growcols_col_exception(){
    try {
        mymatrix<int> M;
        M.growcols(1, 0);
        //should throw an exception
        cout << "growcols column exception test failed: "
             << "desired columns less than one did not throw exception"
             << endl;

    }catch(...){
        return true;
    }
    return false;
}

bool growcols_row_exception_test(){
    try{
        mymatrix<int> M;
        M.growcols(5,2);
        //should throw an exception as row number is not valid
        cout << "growcols row exception test failed: "
             << "desired row being invalid did not throw exception"
             << endl;
    }catch(...){
        return true;
    }
    return false;
}

bool growcols_retain_test(){
    mymatrix<int> M;
    M.growcols(1,2);
    // number of columns are not reduces
    if(M.numcols(1) == 4){
        return true;

    }
    return false;
}

bool grow_test1(){
    mymatrix<int> M;
    M.grow(5,5);
    int count=0;
    //grows the matrix to make it 5x5;
    for(int i=0;i<M.numrows();i++){
        if(M.numcols(i) == 5){
            count ++;
        }
    }
    if(M.numrows() == 5 && count == 5){
        return true;
    }
    return false;

}

bool grow_retain_test(){
    mymatrix<int> M(7,7);
    M.grow(5,5);
    int count=0;
    //retains the original size not reducing it;
    for(int i=0;i<M.numrows();i++){
        if(M.numcols(i) == 7){
            count ++;
        }
    }
    if(M.numrows() == 7 && count == 7){
        return true;
    }
    return false;
}

bool grow_exception_test(){
    try{
        mymatrix<int> M;
        M.grow(0,1);
        //should throw an exception

    }catch(...){
        return true;
    }
    return false;

}

bool size_test(){
  mymatrix<int> M(3,10);
  if(M.size() ==30){
      return true;
  }
  return false;
}

bool at_test1(){
    mymatrix<int>M;
    M.at(2,3) = 3;
    if(M.at(2,3) == 3){
        return true;
    }
    return false;
}

bool at_exception_test(){
    try {
        mymatrix<int> M;
        M.at(2, 4);
        //should give an exception

        cout << "at() invalid exception test failed: "
             << "desired row and column being invalid did not throw exception"
             << endl;
    }catch(...){
        return true;
    }
    return false;
}

bool op_test(){
    mymatrix<int>M;
    M(2,3) = 3;
    if(M(2,3) == 3){
        return true;
    }
    return false;
}

bool op_exception_test(){
    try {
        mymatrix<int> M;
        M.at(2, 4);
        //should give an exception

        cout << "() invalid exception test failed: "
             << "desired row and column being invalid did not throw exception"
             << endl;
    }catch(...){
        return true;
    }
    return false;
}

bool scalar_test_int(){
    int count =0;
    mymatrix <int> P;
    mymatrix <int> M(2,2);
    M(0,0) = 1;
    M(0,1) = 3;
    M(1,1) = 4;
    M(1,0) = 2;

    P=M*3;
    if((P(0,0) == 3)&&(P(0,1) == 9)&& (P(1,1) == 12)&& (P(1,0) == 6) ){
        count++;
    }
    P=M*5;
    if((P(0,0) == 5)&&(P(0,1) == 15)&& (P(1,1) == 20)&& (P(1,0) == 10) ){
        count++;
    }
    if(count ==2){
        return true;
    }
    return false;
}


bool scalar_test_float(){
    int count =0;
    mymatrix <float> P;
    mymatrix <float> M(2,2);
    M(0,0) = 1.5;
    M(0,1) = 3.2;
    M(1,1) = 4.3;
    M(1,0) = 2.2;

    P=M*3;
    if((P(0,0)-4.5 < 0.001)&& (P(0,1) - 9.6<0.001) && (P(1,1) - 12.9<0.001)&& (P(1,0)- 6.6<0.001) ){
        count++;
    }
    P=M*5;
    if((P(0,0) - 7.5 < 0.001)&&(P(0,1) - 16<0.001)&& (P(1,1) - 21.5<0.001)&& (P(1,0) - 11<0.001) ){
        count++;
    }
    if(count ==2){
        return true;
    }
    return false;
}

bool matrix_multiplication_int_test(){

    mymatrix<int> M(2,3);
    M(0,0) = 2;
    M(0,1) = 4;
    M(0,2) = 6;
    M(1,0) = 9;
    M(1,1) = 6;
    M(1,2) = 2;

    mymatrix<int> P(3,2);
    P(0,0) = 2;
    P(0,1 ) =5;
    P(1,0) = 5;
    P(1,1) = 1;
    P(2,0) = 0;
    P(2,1) = 3;

    mymatrix<int> result;
    result = M*P;
    if((result(0,0) == 24)&&(result(0,1) == 32)&&(result(1,0) == 48)&&(result(1,1) == 57)){
        return true;
    }
    return false;

}

bool matrix_multiplication_float_test(){

    mymatrix<float> M(2,3);
    M(0,0) = 2.6;
    M(0,1) = 4.7;
    M(0,2) = 6.1;
    M(1,0) = 9.2;
    M(1,1) = 6.1;
    M(1,2) = 2.2;

    mymatrix<float> P(3,2);
    P(0,0) = 2.2;
    P(0,1 ) =5.1;
    P(1,0) = 5.7;
    P(1,1) = 1.8;
    P(2,0) = 0.2;
    P(2,1) = 3.9;

    mymatrix<float> result;
    result = M*P;
    if((result(0,0) - 33.73<0.0001)&&(result(0,1) - 44.51<0.0001)&&(result(1,0) - 55.45<0.0001)&&(result(1,1) - 66.48<0.0001)){
        return true;
    }
    return false;

}

bool matrix_multiplication_rectangular_exception_test(){
    try {
        mymatrix<int> M;
        mymatrix<int> P;

        M.growcols(2, 7);

        P * M;
        //should throw an exception as matrix M is jagged

        cout << "jagged invalid exception test failed: "
             << "matrix M being jagged did not throw exception"
             << endl;


    }catch(...){
        return true;
    }
    return false;

}

bool matrix_multiplication_compatible_test(){
    try {
        mymatrix<int> M(2, 2);
        mymatrix<int> P(3, 3);
        P*M;
        //should throw an exception as the two cannot be multiplied

        cout << "compatible exception test failed: "
             << "matrices being incompatible did not throw exception"
             << endl;
    }catch(...){
        return true;
    }
    return false;
}




int main(){
    int passed = 0;
    int failed = 0;

    numrows_test1() ? passed++:failed++;
    numrows_test2() ? passed++:failed++;
    numcols_test() ? passed++:failed++;
    numcols_exception_test() ? passed++:failed++;
    growcols_test1() ? passed++:failed++;
    growcols_col_exception() ? passed++:failed++;
    growcols_row_exception_test() ? passed++:failed++;
    growcols_retain_test() ? passed++:failed++;
    grow_test1() ? passed++:failed++;
    grow_retain_test() ? passed:failed++;
    grow_exception_test() ? passed++:failed++;
    size_test() ? passed++: failed++;
    at_test1() ? passed++: failed++;
    at_exception_test() ? passed++:failed++;
    op_test() ? passed++:failed++;
    op_exception_test() ? passed++:failed++;
    scalar_test_int() ? passed++:failed++;
    scalar_test_float() ? passed++:failed++;
    matrix_multiplication_int_test()?passed++:failed++;
    matrix_multiplication_float_test() ? passed++:failed++;
    matrix_multiplication_rectangular_exception_test() ?passed++:failed++;
    matrix_multiplication_compatible_test() ? passed++:failed++;


    cout<< "Passed Tests: "<<passed<<endl;
    cout<<"Failed Tests: "<<failed<<endl;
}