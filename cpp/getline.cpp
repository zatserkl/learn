/*
g++ -o getline getline.cpp
./a.out getline.cpp
*/

#include <fstream>
#include <iostream>
#include <cstdarg>

using std::cout;      using std::endl;

main(int argc, char* argv[])
{
  for (int i=0; i<argc; ++i) cout<< i << "\t " << argv[i] <<endl;

  if (argc < 2) {
    cout<< "Usage: " << argv[0] << " ifname" <<endl;
    return 0;
  }

  std::string ifname;
  if (argc > 1) ifname = argv[1];
  
  std::ifstream ifile(ifname.c_str());
  if (!ifile.is_open()) {
    cout<< "file not found: " << ifname <<endl;
    return 0;   // exception
  }

  std::string line;
  while (std::getline(ifile, line))  // NB: global function std::istream& std::getline(istream& is, string& str);
  {
    cout<< line <<endl;
  }
}
