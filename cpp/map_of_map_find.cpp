#include <iostream>
#include <map>
#include <string>

using std::cout;      using std::endl;

std::map<std::string, std::map<std::string, double> > map;

main()
{
  std::string key1 = "key1";
  std::string key2 = "key2";
  double value = 3.14;

  cout<< "the map is empty" <<endl;

  if (map.find(key1) != map.end()) cout<< "map.find(key1) is found" <<endl;
  else cout<< "map.find(key1) is not found" <<endl;

  if (map.find(key2) != map.end()) cout<< "map.find(key2) is found" <<endl;
  else cout<< "map.find(key2) is not found" <<endl;

  map[key1][key2] = value;

  cout<< "the map is filled" <<endl;

  if (map.find(key1) != map.end()) cout<< "map.find(key1) is found" <<endl;
  else cout<< "map.find(key1) is not found" <<endl;

  if (map.find(key2) != map.end()) cout<< "map.find(key2) is found" <<endl;
  else cout<< "map.find(key2) is not found" <<endl;
  
  cout<<endl<< "-- now" <<endl;
 
  if (map.find(key1) != map.end()) {
    cout<< "when map.find(key1) is found" <<endl;
    if (map[key1].find(key2) != map[key1].end()) cout<< "and also found map[key1][key2]" <<endl;
  }
}
