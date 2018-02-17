#include <map>
#include <string>
#include <iostream>

using namespace std;

main()
{
  std::map<std::string, double> map;
  
  std::string key = "key";
  double value = 1.;

  cout<< "Search before inserting" <<endl;
  if (map.find(key) != map.end()) cout<< "found" <<endl;
  else cout<< "not found" <<endl;

  map[key] = value;

  cout<< "Search after inserting" <<endl;
  std::map<std::string, double>::const_iterator i_key = map.find(key);
  if (i_key != map.end()) cout<< "found" <<endl;
  else cout<< "not found" <<endl;
}
