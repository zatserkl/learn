// http://cplusplus.com/reference/clibrary/cstdio/printf.html
#include <cstdio>

int main()
{
  printf ("Characters: %c %c \n", 'a', 65);
  printf ("Decimals: %d %ld\n", 1977, 650000L);
  printf ("Preceding with blanks: %10d \n", 1977);
  printf ("Preceding with zeros: %010d \n", 1977);
  printf ("Preceding with zeros: %.10d \n", 1977);
  printf ("Some different radixes: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
  printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
  printf ("Width trick: %*d \n", 5, 10);
  printf ("%s \n", "A string");

  // print number in width=2, preced 0 if it's 1-digit number
  int number = 9;
  printf("1-digit number preceded by 0:  %02d \n", number);

  return 0;
}

/*
learn> g++ printf.cpp
learn> ./a.out
Characters: a A 
Decimals: 1977 650000
Preceding with blanks:       1977 
Preceding with zeros: 0000001977 
Preceding with zeros: 0000001977 
Some different radixes: 100 64 144 0x64 0144 
floats: 3.14 +3e+00 3.141600E+00 
Width trick:    10 
A string 
learn>
*/
