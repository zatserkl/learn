#include <map>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

main()
{
  typedef
  std::map<std::string          // key1
    , std::map<std::string      // key2
    , double                    // value
  > > Map_StringString_Double;

  Map_StringString_Double map;
  
  std::string key1 = "key1";
  std::string key2 = "key2";
  double value = 3.14;
  bool found = false;

  // map::find is looking for key of the pair <key,value>
  // for the map that key is key1: map.find(key1) != map.end()
  // for the enclosed map that key is key2: map[key1].find(key2) != map[key1].end()

  cout<< "Search before inserting" <<endl;

  // the most simple and elegant way. See below some other options
  found = false;
  if (map.find(key1) != map.end() && map[key1].find(key2) != map[key1].end()) found = true;
  cout<< "found = " << std::boolalpha << found <<endl;

  // //if (map.find(key1) != map.end() && map.find(key1)->find(key2) != map.find(key1)->end()) cout<< "found" <<endl;
  // if (map.find(key1) != map.end()) {
  //   std::map<std::string, double>::iterator && map.find(key1)->find(key2) != map.find(key1)->end()) cout<< "found" <<endl;
  // // else cout<< "not found" <<endl;

  map[key1][key2] = value;

  cout<< "Search after inserting" <<endl;
  // std::map<std::string, double>::const_iterator i_key = map.find(key);
  // if (i_key != map.end()) cout<< "found" <<endl;
  // else cout<< "not found" <<endl;

  double value_found = 0;
  Map_StringString_Double::iterator i_map1 = map.find(key1);
  if (i_map1 != map.end()) {
    std::map<std::string, double>::iterator i_map2 = i_map1->second.find(key2);
    if (i_map2 != i_map1->second.end()) {
      found = true;
      value_found = i_map2->second;
    }
  }
  cout<< "found = " << found << " value_found = " << value_found <<endl;

  //--
  //-- See how easy and elegant!
  //--

  found = false;
  if (map.find(key1) != map.end() && map[key1].find(key2) != map[key1].end()) found = true;
  cout<< "again: found = " << found <<endl;
}
