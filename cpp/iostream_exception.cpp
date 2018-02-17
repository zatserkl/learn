//http://www.artima.com/cppsource/streamstrings3.html

#include <sstream>
#include <string>
#include <cassert>
#include <iostream>

int main()
{
  std::istringstream sstream;
  sstream >> std::noskipws;		// Don't skip whitespace	
  sstream.str(" 1.23");			// will cause exception because of leading space while set std::noskipws
  // sstream.str("1.23"); 		// will not cause exception
  double d;
  try
  {
    // Turn on exceptions
    sstream.exceptions(std::ios::badbit | std::ios::failbit);
    sstream >> d;
  }
  catch(std::ios_base::failure e)
  {
    std::cout << e.what() << '\n';
    // Manually fix it...assuming we know what went wrong!
    sstream.clear(std::ios::goodbit);
    // Ignore whitespace!
    sstream >> std::skipws;
    sstream >> d;
  }

  assert(d==1.23);
}
