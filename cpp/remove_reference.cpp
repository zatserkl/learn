// http://en.cppreference.com/w/cpp/types/remove_reference

/*
std::remove_reference

Defined in header <type_traits>

template< class T >
struct remove_reference;

(since C++11)

If the type T is a reference type, provides the member typedef type 
which is the type referred to by T. Otherwise type is T.
*/

/*
clang++ -Wall -std=c++14 remove_reference.cpp
*/

#include <iostream> // std::cout
#include <type_traits> // std::is_same
 
template<class T1, class T2>
void print_is_same() {
  std::cout << std::is_same<T1, T2>() << '\n';
}
 
int main() {
  std::cout << std::boolalpha;
 
  print_is_same<int, int>();    // true
  print_is_same<int, int &>();  // false
  print_is_same<int, int &&>(); // false
 
  print_is_same<int, std::remove_reference<int>::type>();    // true
  print_is_same<int, std::remove_reference<int &>::type>();  // true
  print_is_same<int, std::remove_reference<int &&>::type>(); // true
}
