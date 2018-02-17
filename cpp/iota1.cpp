/*
C++11 extension for the range-based for loop:

for (int& i:numbers) ...

clang++ -std=c++14 -Wall iota1.cpp
*/

// iota example
#include <iostream>     // std::cout
#include <numeric>      // std::iota

int main () {
  int numbers[10];

  // NB: for some vector v:
  //
  // std::vector<int> v(10)
  // or
  // std::vector<int> v;
  // v.resize(10);	//--NB: not v.reserve(10): reserve doesn't change size
  //
  // std::iota(v.begin(), v.end(), 100);

  std::iota (numbers,numbers+10,100);

  std::cout << "numbers:";
  for (auto i:numbers) std::cout << ' ' << i;
  std::cout << '\n';

  return 0;
}
