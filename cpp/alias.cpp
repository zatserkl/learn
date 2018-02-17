#include <iostream>

using std::cout;      using std::endl;

int main()
{
  int v = 5;
  int& alias = v;
  cout<< "single: alias = " << alias <<endl;

  int a[3];
  int& a0 = a[0];
  int& a1 = a[1];
  int& a2 = a[2];

  for (int i=0; i<3; ++i) a[i] = 10 + i;

  cout<< "array: a0 = " << a0 << " a1 = " << a1 << " a2 = " << a2 <<endl;

  return 0;
}
