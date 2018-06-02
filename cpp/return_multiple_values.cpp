// modified example from the book: C++17 Quick Syntax Reference.pdf

/*
clang++ -Wall -std=c++17 return_multiple_values.cpp
*/

// Returning multiple values

#include <tuple>
#include <iostream>

using std::cout;    using std::endl;

/**
  * Two possibilities:
  *
  * 1) declare function return value as auto
  *    AND use function std::make_tuple(5, 1.2, 'b')
  *
  * 2) declare function return value as std::tuple<int, double, char>
  *    AND return values as a list enclosed in curly brackets
  */

auto getTuple() 
{
  return std::make_tuple(5, 1.2, 'b');
}

// std::tuple<int, double, char> getTuple() 
// {
//   return {5, 1.2, 'b'};
// }

int main()
{
  auto mytuple = getTuple();

  cout << std::get<0>(mytuple) << endl; // "5"
  cout << std::get<1>(mytuple) << endl; // "1.2"
  cout << std::get<2>(mytuple) << endl; // "b"

  int i;
  double d;

  // Unpack tuple into variables
  tie(i, d, std::ignore) = getTuple();  // NB: ignore the third element 'b'

  cout << "i: " << i << " d: " << d << endl; // "5 1.2"
}
