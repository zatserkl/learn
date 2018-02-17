/*
g++ -o grep001 grep001.cpp
./grep001
./grep001 grep001.t
*/

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using std::cout;      using std::endl;

void expand_number(std::string& str, const int ndigits=5)
{
  // change FIRST :23: to :00023: in the line
  // FastFECSupervisor/src/common/FastFECSupervisor.cc:23:   throw (xdaq::exception::Exception)

  std::size_t pos1 = std::string::npos;
  std::size_t pos2 = std::string::npos;
  
  pos1 = str.find_first_of(':', 0);
  if (pos1 != std::string::npos) pos2 = str.find_first_of(':', pos1+1);
  if (pos2 != std::string::npos)
  {
    int ndigits_curr = pos2 - pos1 + 1 - 2;    // n chars w/o head and trailing ':'
    if (ndigits_curr > 0)
    {
      std::string number_str(str.substr(pos1+1,ndigits_curr));
      //cout<< "expand_number: number_str = " << number_str <<endl;

      std::stringstream out;
      out<< std::setfill('0') << std::setw(ndigits) << number_str;
      //cout<< "expand_number: out.str() = " << out.str() <<endl;

      //cout<< "--> " << str <<endl;
      str.replace(pos1+1, ndigits_curr, out.str());
      //cout<< "--> " << str <<endl;
    }
  }
}

main(int argc, char *argv[])
{
  // change :23: to :0023: in the line
  // std::string str = "FastFECSupervisor/src/common/FastFECSupervisor.cc:23:   throw (xdaq::exception::Exception)";

  std::string ifname;
  int ndigits = 5;

  if (argc == 1) {
    cout<< "Usage: " << argv[0] << " fname ndigit=" << ndigits <<endl;
    return 0;
  }

  if (argc > 1) ifname = argv[1];
  if (argc > 2) ndigits = atoi(argv[2]);

  std::ifstream ifile(ifname.c_str());
  if (!ifile) {
    cout<< "Input file not found: " << ifname <<endl;
    return 0;
  }

  std::string line;
  while (std::getline(ifile, line))  // NB: global function std::getline(istream& is, string& str);
  {
    expand_number(line,ndigits);
    cout<< line <<endl;
  }
  ifile.close();
}

// main(int argc, char *argv[])
// {
//   // change :23: to :0023: in the line
//   // std::string str = "FastFECSupervisor/src/common/FastFECSupervisor.cc:23:   throw (xdaq::exception::Exception)";
// 
//   std::string str;
//   int ndigits = 5;
// 
//   if (argc == 1) {
//     cout<< "Usage: " << argv[0] << " grep-n_string ndigit=" << ndigits <<endl;
//     return 0;
//   }
// 
//   if (argc > 1) str = argv[1];
//   if (argc > 2) ndigits = atoi(argv[2]);
// 
//   expand_number(str,ndigits);
// 
//   cout<< str <<endl;
// }
