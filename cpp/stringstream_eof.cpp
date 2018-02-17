#include <iostream>
#include <string>
#include <sstream>

using std::cout;      using std::endl;

main()
{
  std::stringstream ss("this is a string");
  std::string str;
  unsigned nwords = 0;
  while (ss >> str) {
    ++nwords;
    cout<< nwords <<" "<< str <<endl;
  }

  if (ss.eof()) cout<< "the end of stream (EOF) is reached" <<endl;
  else          cout<< "WARNING: i/o problem" <<endl;

  cout<< "\nState of the stringstream ss:" <<endl;
  cout<< "(ss.rdstate() & std::ios_base::eofbit) = " << (ss.rdstate() & std::ios_base::eofbit) <<endl;
  cout<< "(ss.rdstate() & std::ios_base::failbit) = " << (ss.rdstate() & std::ios_base::failbit) <<endl;
  cout<< "(ss.rdstate() & std::ios_base::badbit) = " << (ss.rdstate() & std::ios_base::badbit) <<endl;
  cout<< "(ss.rdstate() & std::ios_base::goodbit) = " << (ss.rdstate() & std::ios_base::goodbit) <<endl;

  cout<< "\nnwords = " << nwords <<endl;
}
