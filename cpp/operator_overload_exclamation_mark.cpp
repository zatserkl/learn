#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;      using std::endl;

class OpenFile {
  bool status;
public:
  OpenFile(const char* fname): status(false) {
    std::ifstream file(fname);
    if (!file) cout<< "File not found: " << fname <<endl;
    else {
      status = true;
      cout<< "File exists: " << fname <<endl;
    }
  }
  bool operator !() const {return !status;}
};

int main()
{
  OpenFile openfile("operator_overload_exclamation_mark.cpp");
  cout<< "!openfile = " << std::boolalpha << !openfile <<endl;
  // the same: use 'not' instead of '!'
  cout<< "not openfile = " << std::boolalpha << not openfile <<endl;

  OpenFile openfile_xxx("operator_overload_exclamation_mark.cpp-xxx");
  cout<< "!openfile_xxx = " << std::boolalpha << !openfile_xxx <<endl;
  // the same: use 'not' instead of '!'
  cout<< "not openfile_xxx = " << std::boolalpha << not openfile_xxx <<endl;

  return 0;
}
