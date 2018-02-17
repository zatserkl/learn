#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using std::cout;      using std::endl;

int main()
{
  const char* ifname[4] = {"ifile1.dat", "ifile2.dat", "ifile3.dat", "ifile4.dat"};
  
  std::fstream ifile[4];
  for (int ilayer=0; ilayer<4; ++ilayer) {
    // create file by open it in out mode and close it
    ifile[ilayer].open(ifname[ilayer], std::ios::binary | std::ios::out);
    ifile[ilayer].close();
    // open file for in/out
    ifile[ilayer].open(ifname[ilayer], std::ios::binary | std::ios::in | std::ios::out);
  }

  for (int ilayer=0; ilayer<4; ++ilayer) {
    for (int ievent=0; ievent<5; ++ievent) {
      float val = ilayer+1;
      ifile[ilayer].write((const char*) &val, sizeof(float));
    }
  }

  for (int ilayer=0; ilayer<4; ++ilayer) {
    ifile[ilayer].seekg(0, ifile[ilayer].beg);
    cout<< "ifile[" << ilayer << "].tellg() = " << ifile[ilayer].tellg() <<endl;
  }

  // for (int ilayer=0; ilayer<4; ++ilayer) {
  //   float val = 0;
  //   while (ifile[ilayer].read((char*) &val, sizeof(float))) {
  //     cout<< "ilayer = " << ilayer << " val = " << val <<endl;
  //   }
  // }

  // std::ofstream ofile("ofile.dat", std::ios::binary);
  // for (int ilayer=0; ilayer<4; ++ilayer) {
  //   std::copy(std::istreambuf_iterator<char>(ifile[0]),
  //             std::istreambuf_iterator<char>(),
  //             std::ostreambuf_iterator<char>(ofile));
  // }

  // open file for output, close it and open again for in/out
  std::fstream ofile("ofile.dat", std::ios::binary | std::ios::out);
  ofile.close();
  ofile.open("ofile.dat", std::ios::binary | std::ios::in | std::ios::out);

  for (int ilayer=0; ilayer<4; ++ilayer) {
    std::istreambuf_iterator<char> begin_source(ifile[ilayer]);
    std::istreambuf_iterator<char> end_source;
    std::ostreambuf_iterator<char> begin_dest(ofile);

    std::copy(begin_source, end_source, begin_dest);
  }

  ofile.seekg(0, ofile.beg);

  float val;
  while (ofile.read((char*) &val, sizeof(float))) {
    cout<< val <<endl;
  }

  return 0;
}
