#include <map>
#include <string>
#include <iostream>

using namespace std;

main()
{
  std::map<std::string, std::string> map;
  
  std::string key;
  std::string value;

  key = "hello";
  value = "world";

  cout<< "Search before inserting" <<endl;
  if (map.find(key) != map.end()) cout<< "found" <<endl;
  else cout<< "not found" <<endl;

  map[key] = value;

  cout<< "Search after inserting" <<endl;
  std::map<std::string, std::string>::const_iterator i_key = map.find(key);
  if (i_key != map.end()) cout<< "found for key " << key << " i_key->second = " << i_key->second <<endl;
  else cout<< "not found" <<endl;
  
  // look at more complecated map
  std::map<std::string, std::map<std::string, std::string> > mapmap;
}
