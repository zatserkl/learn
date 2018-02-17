#include <iostream>

using std::cout;      using std::endl;

int main()
{
  int ix[] = {1, 2, 3, 4, 5, 6, 7};
  cout<< "sizeof(ix)/sizeof(int) = " << sizeof(ix)/sizeof(int) <<endl;

  double x[] = {10.5, 8.5, 6.5, 4.5, 3.125, 1.8, 0.0};
  cout<< "sizeof(x)/sizeof(double) = " << sizeof(x)/sizeof(double) <<endl;

  return 0;
}
