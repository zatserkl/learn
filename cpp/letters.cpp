#include <iostream>
#include <fstream>
#include <map>
#include <cctype>

using std::cout;      using std::endl;

int main()
{
  // std::ifstream ifile(__FILE__);
  const char ifname[] = "OHenry.txt";

  std::ifstream ifile(ifname);
  if (!ifile) {
    cout<< "Could not open file " << ifname <<endl;
    return 0;
  }

  std::map<char, int> map;

  char ch;
  while (ifile >> ch) {
    ++map[std::toupper(ch)];
  }

  for (std::map<char,int>::const_iterator
      i_map=map.begin(); i_map!=map.end(); ++i_map)
  {
    // cout<< i_map->first <<"\t "<< i_map->second <<endl;
    if (std::isalpha(i_map->first)) cout<< i_map->first <<"\t "<< i_map->second <<endl;
  }

  return 0;
}
