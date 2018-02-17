#include <iostream>
#include <cstdarg>
#include <string>
#include <sstream>

using std::cout;      using std::endl;

int runnum(std::string fname)
{
  // const std::string ifname = "/home/zatserkl/work/time/2009_run/run172.out";
  // const std::string run = "run";
  // unsigned pos = ifname.rfind(run);
  // cout<< "runnum(ifname.substr(pos+run.size())) = " << runnum(ifname.substr(pos+run.size())) <<endl;

  std::stringstream ss(fname);
  int n = 0;
  ss >> n;
  return n;
}

int runnum(std::string fname, unsigned pos)
{
  // const std::string ifname = "/home/zatserkl/work/time/2009_run/run172.out";
  // const std::string run = "run";
  // unsigned pos = ifname.rfind(run);
  // cout<< "runnum(ifname, pos+run.size()) = " << runnum(ifname, pos+run.size()) <<endl;

  std::stringstream ss(fname.substr(pos));
  int n = 0;
  ss >> n;
  return n;
}

main(int argc, char *argv[])
{
  cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

  // if (argc == 1) {
  //   cout<< "Usage: " << argv[0] << " filename" <<endl;
  //   return 0;
  // }

  //                    0123456789 123456789 123456789 123456789 123456789
  std::string ifname = "/home/zatserkl/work/time/2009_run/run172.out";

  const std::string run = "run";
  // const std::string out = ".out";

  // unsigned pos1 = ifname.find_last_of(run);
  // if (pos1 == std::string::npos) {
  //   cout<< "***ERROR: cannot find " << run << " in file name " << ifname <<endl;
  //   return 0;
  // }
  // unsigned pos2 = ifname.find_last_of(out);
  // if (pos2 == std::string::npos) {
  //   cout<< "***ERROR: cannot find " << out << " in file name " << ifname <<endl;
  //   return 0;
  // }

  // int n = pos2 - pos1;
  // cout<< "pos1 = " << pos1 << " pos2 = " << pos2 <<endl;
  // //pos1 += run.size();

  // unsigned pos = ifname.find(run);
  // cout<< "runnum(ifname, pos+run.size()) = " << runnum(ifname, pos+run.size()) <<endl;

  // // std::string substring = ifname.substr(pos1+run.size(), n);
  // // cout<< "substring = " << substring <<endl;

  unsigned pos = ifname.rfind(run);
  cout<< "pos = " << pos <<endl;
  cout<< "runnum(ifname, pos+run.size()) = " << runnum(ifname, pos+run.size()) <<endl;
  cout<< "runnum(ifname.substr(pos+run.size())) = " << runnum(ifname.substr(pos+run.size())) <<endl;
}
