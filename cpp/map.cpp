#include <iostream>
#include <map>
#include <string>

using std::cout;      using std::endl;

const std::string astr[6] = {
  "abc",
  "abcd",
  "abc",
  "def",
  "abc",
  "def",
};

main()
{
  std::map<std::string, int> map;
  for (int i=0; i<6; ++i) {
    ++map[astr[i]];
  }

  for (std::map<std::string,int>::const_iterator
      i_map=map.begin(); i_map!=map.end(); ++i_map)
  {
    cout<< i_map->first <<"\t "<< i_map->second <<endl;
  }
}
