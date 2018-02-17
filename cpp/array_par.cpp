#include <iostream>

/*
learn$ g++ array_par.cpp
array_par.cpp: In function ‘int main()’:
array_par.cpp:13: warning: extended initializer lists only available with -std=c++0x or -std=gnu++0x
array_par.cpp:13: error: cannot convert ‘<brace-enclosed initializer list>’ to ‘int*’ for argument ‘2’ to ‘int sum(int, int*)’
learn$ g++ array_par.cpp -std=gnu++0x
array_par.cpp: In function ‘int main()’:
array_par.cpp:13: error: cannot convert ‘<brace-enclosed initializer list>’ to ‘int*’ for argument ‘2’ to ‘int sum(int, int*)’
*/

using std::cout;      using std::endl;

int sum(int n, int a[]) {
  int sum = 0;
  for (int i=0; i<n; ++i) sum += a[i];
  return sum;
}

int main()
{
  int res = sum(3, {1,2,3});
  return 0;
}
