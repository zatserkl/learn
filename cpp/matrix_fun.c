/*
Compile this code with C compiler that suppors C99 standard for Variable Length Arrray, e.g.

clang -Wall matrix_fun.c
*/

//
//  This program cannot be compiled in C++ because the Variable Length Array is a C C99 feature
//
/*
clang++ -Wall matrix_fun.c
clang: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated
matrix_fun.c:90:18: error: no matching function for call to 'maximum'
    double max = maximum(nrows,ncols,matrix);
                 ^~~~~~~
matrix_fun.c:52:8: note: candidate function not viable: no known conversion from 'double [3][5]' to 'double (*)[ncols]' for 3rd argument
double maximum(int nrows, int ncols, double matrix[nrows][ncols]);  // OK, with parameter names
       ^
matrix_fun.c:53:8: note: candidate function not viable: no known conversion from 'double [3][5]' to 'double (*)[*]' for 3rd argument
double maximum(int, int, double matrix[*][*]);                      // OK, but NB astericks
       ^
matrix_fun.c:61:8: note: candidate function not viable: no known conversion from 'double [3][5]' to 'double (*)[ncols]' for 3rd argument
double maximum(int nrows, int ncols, double matrix[nrows][ncols])
       ^
1 error generated.*/

#include <stdio.h>

/*
From the book "C in a Nutshell" by Peter Prinz and Tony Crawford.

C99 also lets you declare array parameters as variable-length arrays (see Chapter 8). To do so, 
place a nonconstant integer expression with a positive value between the square brackets. In this 
case, the array parameter is still a pointer to the first array element. The difference is that 
the array elements themselves can also have a variable length. In Example 7-5, the maximum( ) 
function’s third para- meter is a two-dimensional array of variable dimensions.
*/

// The function maximum() obtains the greatest value in a
// two-dimensional matrix of double values.
// Arguments: The number of rows, the number of columns, and the matrix.
// Return value: The value of the greatest element.

///////////////////////////////////////////////////////////////////
//
//  Prototype
//
//  NB: Prototype needs asterisks if you omit the parameter names
//
///////////////////////////////////////////////////////////////////

double maximum(int nrows, int ncols, double matrix[nrows][ncols]);  // OK, with parameter names
double maximum(int, int, double matrix[*][*]);                      // OK, but NB astericks

////////////////////////////////////////////////////////
//
//  Function definition
//
////////////////////////////////////////////////////////

double maximum(int nrows, int ncols, double matrix[nrows][ncols])
{
  double max = matrix[0][0];
  for ( int r = 0; r < nrows; ++r )
    for ( int c = 0; c < ncols; ++c )
      if ( max < matrix[r][c] )
        max = matrix[r][c];
  return max;
}

#define ROWS 3
#define COLS 5

int main()
{
    int nrows = ROWS;
    int ncols = COLS;

    double matrix[nrows][ncols];

    for (int row=0; row<nrows; ++row) {
        for (int col=0; col<ncols; ++col) {
            matrix[row][col] = row + (double)col/10;
            printf("%0.1f\t", matrix[row][col]);
        }
        printf("\n");
    }

    // call the function to find the maximum
    double max = maximum(nrows,ncols,matrix);

    printf("max = %0.1f\n",max);

    return 0;
}
