// #include <iostream>
// #include <algorithm>
// 
// using std::cout;      using std::endl;
// 
// int main()
// {
//   double v[] = {0, 1, 4, 3};
//   cout<< *std::find(&v[0], &v[3], 4) <<endl;
//   cout<< std::find(&v[0], &v[3], 2) <<endl;
//   return 0;
// }

// find example
#include <iostream>     // std::cout
#include <algorithm>    // std::find
#include <vector>       // std::vector

using std::cout;    using std::endl;

int main () {
  int myints[] = { 10, 20, 30, 40 };
  int * p;

  // pointer to array element:
  p = std::find (myints,myints+4,30);
  ++p;
  std::cout << "The element following 30 is " << *p << '\n';

  std::vector<int> myvector (myints,myints+4);
  std::vector<int>::iterator it;

  // iterator to vector element:
  it = find (myvector.begin(), myvector.end(), 30);
  ++it;
  std::cout << "The element following 30 is " << *it << '\n';

  cout<< "addresses of the array elements:" <<endl;
  for (int i=0; i<4; ++i) {
    cout<< i << "\tmyints[" << i << "] = " << myints[i] << "\taddress = " << &myints[i] <<endl;
  }

  cout<< "last element: std::find(myints,myints+4, 40) = " << std::find(myints,myints+4, 40) <<endl;
  cout<< "next to the last element: std::find(myints,myints+4, 0) = " << std::find(myints,myints+4, 0) <<endl;

  return 0;
}
