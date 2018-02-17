#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;      using std::endl;

bool fexists(const char* ifname) {
  bool fexists = false;
  std::ifstream ifile(ifname, std::ifstream::in|std::ifstream::binary);
  if (ifile.is_open()) {
     ifile.close();
     fexists = true;
  }
  return fexists;
}

int main()
{
  cout<< "fexists(\"fexists.cpp\") = " << std::boolalpha << fexists("fexists.cpp") <<endl;
  return 0;
}
