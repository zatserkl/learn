#include <iostream>

using namespace std;

struct Char {
  // static const char const_char[]="const"; // doesn't work
  const char* const const_char;
  Char(): const_char("const_char") {}
};

int main() {
  Char c;
  cout<< c.const_char <<endl;
}
