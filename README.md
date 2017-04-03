simple_matrix
===================

This is a simple library for matrix calculations aiming for ease to set up and use. It is contained in a single file that has no dependencies except for one C++ header that can be easily pasted any project and included as header.

----------
Purpose
--
Nobody should be motivated to deal with all the weirdness of MatLab only because it does a few basic matrix operations. This easy library implements in C++ a matrix object that supports functions like addition, subtraction, multiplication (by vector, scalar or matrix), transposition, power or determinant, all of which can be used in the source code as naturally as in MatLab.

----------
Features
--
- Support for matrix addition, subtraction, multiplication, transposition, power, determinant, comparison and printing, all doable through operators if possible
- Compile time checking of matrix dimensions via templates
- Boundary checks when accessing elements in debug mode (prints warnings)
- Internally identical to a 2D array

----------
Example
--
```
#include "simple_matrix.h"
matrix<2, 2> A = {{2, 3}, {3, 1}; // declare+init 2x2 matrix
matrix<3, 2> B = {{2, 3}, {0, 1}, {3, 1}}; // a 3x2 matrix
matrix<3, 2> C = B * A + B; // arithmetic
C[1][2] = 3; // set a value like in an array
A = (A ^ 2) * 2; // caution, the power sign has low priority
lineVector<2> a = {1, 7}; // same as a 1x2 matrix
lineVector<2> b = a * transpose(A);
double c = determinant(A);
```
> **Notes**:
>- first index is line row, second is column
>- the numeric type is double by default, but other types can be set as a third template argument (p.e. `matrix<3, 3, float>` or `lineVector<2, int>`)
>- requires C++11 to compile
>- only the simple_matrix.h file is required, tests.cpp is only to check if the functions do what they are meant to do

----------
Limitations
--
- No algorithm for matrix inversion or computation of eigenvalues or eigenvectors
- No optimised algorithm for matrix multiplication
- Quite slow in debug mode
