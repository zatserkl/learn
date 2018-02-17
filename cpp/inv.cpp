#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <cstdio>

using std::cout;      using std::endl;

int main(int argc, char *argv[])
{
  cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

  if (argc == 1) {
    cout<< "Usage:\n" << argv[0] << " file" <<endl;
    return 0;
  }

  const char* ifname = argv[1];

  std::ifstream ifile(ifname, std::ifstream::binary);
  if (!ifile) {
    cout<< "Could not open file " << ifname <<endl;
    return 0;
  }

  // NB: ofname(ifname) will set stream pointer in the position 0 and 
  // next ofname << ".inv" will overwrite the beginning of the filename

  // std::stringstream ofname;
  // ofname << ifname << ".inv";
  // std::ofstream ofile(ofname.str().c_str(), std::ofstream::out|std::ofstream::binary);
  // if (!ofile) {
  //   cout<< "Could not open new file " << ofname.str().c_str() <<endl;
  //   return 0;
  // }

  std::string ofname(ifname);

  const std::string inv(".inv");
  unsigned pos_suffix = ofname.rfind(inv);

  // cout<< "ofname.length() = " << ofname.length() << " pos_suffix = " << pos_suffix << " ofname.length() - inv.length() = " << ofname.length() - inv.length() <<endl;

  if (pos_suffix == ofname.length() - inv.length()) {
    // cout<< "erase the .inv" <<endl;
    ofname.erase(pos_suffix);
  }
  else ofname += inv;

  std::ofstream ofile(ofname.c_str(), std::ofstream::out|std::ofstream::binary);
  if (!ofile) {
    cout<< "Could not open output file " << ofname.c_str() <<endl;
    return 0;
  }

  cout<< "Write output file " << ofname <<endl;

  while (ifile.good()) {
    char ichar = ifile.get();
    if (ifile.good()) {
      // cout<< ichar;
      ofile.put(-ichar);
    }
  }

  return 0;
}
