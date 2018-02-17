#include <iostream>

using std::cout;    using std::endl;

/*
From the book "C in a Nutshell" by Peter Prinz and Tony Crawford.

Matrices

Two-dimensional arrays are also called matrices. Because they are so frequently used, they merit 
a closer look. It is often helpful to think of the elements of a matrix as being arranged in rows 
and columns. Thus the matrix mat in the following definition has three rows and five columns:

     float mat[3][5];

The three elements mat[0], mat[1], and mat[2] are the rows of the matrix mat. Each of these rows 
is an array of five float elements. Thus the matrix contains a total of 3 × 5 = 15 float elements, 
as the following diagram illustrates:

        0       1       2       3       4
mat[0]  0.0     0.1     0.2     0.3     0.4
mat[1]  1.0     1.1     1.2     1.3     1.4
mat[2]  2.0     2.1     2.2     2.3     2.4

The values specified in the diagram can be assigned to the individual elements by a nested loop 
statement. The first index specifies a row, and the second index addresses a column in the row:

     for ( int row = 0;  row < 3;  ++row )
       for ( int col = 0;  col < 5;  ++col )
         mat[row][col] = row + (float)col/10;

In memory, the three rows are stored consecutively, since they are the elements of the array mat. 
As a result, the float values in this matrix are all arranged consecutively in memory in ascending 
order.

The output of this programs is:

0
0.1
0.2
0.3
0.4
1
1.1
1.2
1.3
1.4
2
2.1
2.2
2.3
2.4
*/

int main()
{
    double matrix[3][5];

    for (int row=0; row<3; ++row) {
        for (int col=0; col<5; ++col) {
            matrix[row][col] = row + (double)col/10;
        }
    }

    // one-dimensional array that starts at the first element of two-dimensional array matrix
    double* first = &matrix[0][0];

    // print consecutive elements
    for (int i=0; i<3*5; ++i) {
        cout<< first[i] <<endl;
    }

    return 0;
}
