// toupper example (C++)
#include <iostream>
#include <string>
//-- seems you do not have to include header locale to compile this program
// #include <locale>
using namespace std;

int main ()
{
  locale loc;
  string str="Test String.\n";
  for (size_t i=0; i<str.length(); ++i)
    cout << toupper(str[i],loc);
  return 0;
}
