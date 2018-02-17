#include <stdio.h>
#include <stdlib.h>

int factorial(int X) {
  if (X == 0) return 1;
  return X*factorial(X-1);
}

int main(int argc, char **argv) {
  for (int i=0; i<argc; ++i) printf("%d\t %s\n", i, argv[i]);
  if (argc != 2) return 0;
  printf("%d\n", factorial(atoi(argv[1])));
}
