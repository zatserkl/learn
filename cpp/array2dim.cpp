// to see warnings compile with option -Wall

// original was http://terpconnect.umd.edu/~colvin/recitation_examples/081008_2DcurlyAssign.c

#include <cstdio>
#include <iostream>

using std::cout;    using std::endl;

#define ROWS 3
#define COLS 4

int main() 
{
  int i, j;

  // int matrix[ROWS][COLS] = {
  // float matrix[ROWS][COLS] = {      // works for float too -- not standard?
  //   { 1, 2, 3, 4 },
  //   { 5, 6, 7, 8 },
  //   { 9, 10, 11, 12 }
  // };

  // the same result will be with
  // int matrix[ROWS][COLS] = {
  //   1, 2, 3, 4,
  //   5, 6, 7, 8,
  //   9, 10, 11, 12
  // };

  // ---------------------------------------------
  // you don't have to specify the first dimension:
  // ---------------------------------------------

  // result will be also the same with
  int matrix[][COLS] = {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 }
  };

  // -- result will be the same as well. NB: comp. warning "missing braces around initializer"
  // int matrix[][COLS] = {
  //   1, 2, 3, 4,
  //   5, 6, 7, 8,
  //   9, 10, 11, 12
  // };

  //-- the same result will be with this assignement
  // int number = 0;
  // for (int i=0; i<ROWS; ++i)
  //   for (int j=0; j<COLS; ++j)
  //     matrix[i][j] = ++number;

  // for (i = 0; i < ROWS; i++) {
  //   for (j = 0; j < COLS; j++) {
  //     printf("%d\t", matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  for (int irow = 0; irow < ROWS; irow++) {
    for (int icol = 0; icol < COLS; icol++) {
      cout<< matrix[irow][icol] << "\t";
    }
    cout<<endl;
  }
  /*
  1       2       3       4
  5       6       7       8
  9       10      11      12
  */

  int somerow = 0;
  cout<< "print the 0th row (somerow = " << somerow << ")" <<endl;
  for (int icol=0; icol<COLS; ++icol) {
    cout<< matrix[somerow][icol] << "\t";
  }
  cout<<endl;

  int somecol = 2;
  cout<< "print the third column (somecol = " << somecol << ")" <<endl;
  for (int irow=0; irow<ROWS; ++irow) {
    cout<< matrix[irow][somecol] <<endl;
  }

  return 0;
}
