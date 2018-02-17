/*
This code has been compiled fine with the C compiler:

$ clang -Wall VariableLengthArray.c

The C++ compiler generates errors:

$ clang++ -Wall VariableLengthArray.c
clang: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated
VariableLengthArray.c:81:11: error: no matching function for call to 'sum2d'
    tot = sum2d(nrows,ncols,matrix);
          ^~~~~
VariableLengthArray.c:38:5: note: candidate function not viable: no known conversion from 'int [2][3]' to 'int (*)[*]' for 3rd argument
int sum2d(int, int, int ar[*][*]);                  // ar a VLA, names omitted
    ^
VariableLengthArray.c:39:5: note: candidate function not viable: no known conversion from 'int [2][3]' to 'int (*)[cols]' for 3rd argument
int sum2d(int rows, int cols, int ar[rows][cols]);  // prototype with names
    ^
VariableLengthArray.c:47:5: note: candidate function not viable: no known conversion from 'int [2][3]' to 'int (*)[cols]' for 3rd argument
int sum2d(int rows, int cols, int ar[rows][cols])
    ^
1 error generated.
*/

#include <stdio.h>

// http://www.9wy.net/onlinebook/CPrimerPlus5/ch10lev1sec8.html

///////////////////////////////////////////////////
//
//  Prototype of the function with VLA parameter
//
///////////////////////////////////////////////////

// The C99 standard says you can omit names from the prototype; 
// but in that case, you need to replace the omitted dimensions with asterisks:

int sum2d(int, int, int ar[*][*]);                  // ar a VLA, names omitted
int sum2d(int rows, int cols, int ar[rows][cols]);  // prototype with names

///////////////////////////////////////////////////
//
//  Definition of the function with VLA parameter
//
///////////////////////////////////////////////////

int sum2d(int rows, int cols, int ar[rows][cols])
{
    int r;
    int c;
    int tot = 0;

    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            tot += ar[r][c];

    return tot;
}

#define ROWS 2
#define COLS 3

int main()
{
    int matrix[2][3];

    for (int row=0; row<ROWS; ++row) {
        for (int col=0; col<COLS; ++col) {
            matrix[row][col] = (row+1)*10 + col;
            printf("%d\t",matrix[row][col]);
        }
        printf("\n");
    }

    int tot = 0;

    // tot = sum2d(ROWS,COLS,matrix);   // does not work with clang++ as well

    int nrows = ROWS;
    int ncols = COLS;
    tot = sum2d(nrows,ncols,matrix);

    printf("tot = %d\n", tot);

    return 0;
}
