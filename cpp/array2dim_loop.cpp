// http://terpconnect.umd.edu/~colvin/recitation_examples/081008_basic2D.c

#include <stdio.h>

#define ROWS 5
#define COLS 6

int main() 
{
  int matrix[ROWS][COLS];
  int i, j, k;

  for (i = 0, k = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++, k++) {
      matrix[i][j] = k;
    }
  }

  for (i = 0, k = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++, k++) {
      printf("%d\t", matrix[i][j]);
    }

    printf("\n");
  }

  return 0;
}
