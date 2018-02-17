#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  std::map<std::string, int> map;

  map["Jan"] = 1;
  map["Feb"] = 2;
  map["Mar"] = 3;

  for (std::map<std::string, int>::const_iterator it=map.begin(); it!=map.end(); ++it)
  {
    // does not work: cout<< std::distance(map.begin(), it) << " " << it->first << " " << it->second <<endl;
    // to make it work add explicit type conversion:
    cout<< std::distance<std::map<std::string, int>::const_iterator>(map.begin(), it) << " " << it->first << " " << it->second <<endl;
  }
}
