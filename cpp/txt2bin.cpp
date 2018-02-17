#include <iostream>
#include <fstream>
#include <cstdarg>
#include <string>

using std::cout;    using std::endl;

int main(int argc, char *argv[])
{
  if (argc == 1) {
    cout<< "Usage:\n" << argv[0] << " filename" <<endl;
    return 0;
  }

  std::string ifname = argv[1];
  std::string ofname = ifname + ".bin";
  cout<< "converting " << ifname << " to " << ofname <<endl;

  std::ifstream ifile(ifname.c_str());
  if (!ifile) {
    cout<< "Could not open file " << ifname <<endl;
    return 0;
  }

  std::ofstream ofile(ofname.c_str(), std::ios::binary);

  // skip 4 lines
  std::string line;
  for (int i=0; i<4; ++i) std::getline(ifile, line);

  // convert next 100 lines to bin
  for (int iline=0; iline<100; ++iline) {
    int idata;
    // skip line number
    ifile >> idata;
    for (int inumber=0; inumber<512; ++inumber) {
      ifile >> idata;
      char cdata = idata;
      ofile << cdata;
    }
  }
  ifile.close();
  ofile.close();

  return 0;
}
