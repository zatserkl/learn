#include <iostream>
#include <sstream>
#include <string>

using std::cout;      using std::endl;

template <char delimiter>
class my_char_trais: public std::char_traits<char>
{
  bool isdel(char c) {
    return eq(c, delimiter);
    //return c == delimiter;
  }
};

main()
{
  std::string date = "16:56:47";
  std::basic_istringstream<char, my_char_trais<':'> > ss(date);
  
}
/*
learn> g++ basic_istringstream.cpp
basic_istringstream.cpp: In function ‘int main()’:
basic_istringstream.cpp:19: error: no matching function for call to ‘std::basic_istringstream<char, my_char_trais<':'>, std::allocator<char> >::basic_istringstream(std::string&)’
/usr/include/c++/4.2/sstream:320: note: candidates are: std::basic_istringstream<_CharT, _Traits, _Alloc>::basic_istringstream(const std::basic_string<_CharT, _Traits, _Alloc>&, std::_Ios_Openmode) [with _CharT = char, _Traits = my_char_trais<':'>, _Alloc = std::allocator<char>]
/usr/include/c++/4.2/sstream:299: note:                 std::basic_istringstream<_CharT, _Traits, _Alloc>::basic_istringstream(std::_Ios_Openmode) [with _CharT = char, _Traits = my_char_trais<':'>, _Alloc = std::allocator<char>]
/usr/include/c++/4.2/sstream:262: note:                 std::basic_istringstream<char, my_char_trais<':'>, std::allocator<char> >::basic_istringstream(const std::basic_istringstream<char, my_char_trais<':'>, std::allocator<char> >&)
*/
