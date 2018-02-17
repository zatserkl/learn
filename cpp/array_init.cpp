#include <iostream>

using std::cout;      using std::endl;

main()
{
  int a[] = {1, 2, 3};

  for (int i=0; i<3; ++i) {
    cout<< "a[" << i << "] = " << a[i] <<endl;
  }
}
