#include <iostream>

using std::cout;      using std::endl;

main()
{
  int a = 0;
  int& r = a;
  r = 5;
  cout<< "a = " << a <<endl;

  // // const reference only can be alias of 2
  // const int& two = 2;
  // cout<< "two = " << two <<endl;

  int array[] = {1, 2, 3};
  int& a0 = array[0];
  int& a1 = array[1];
  int& a2 = array[2];
  cout<< "a0 = " << a0 << " a1 = " << a1 << " a2 = " << a2 <<endl;
}
