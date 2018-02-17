// Andriy Zatserklyaniy   April 17, 2014

#include <iostream>
#include <string>
#include <map>

using std::cout;      using std::endl;

int main()
{
  std::map<std::string, int> map;

  map["a"] = 1;
  map["b"] = 2;
  map["c"] = 3;
  map["d"] = 4;
  map["e"] = 5;

  for (std::map<std::string, int>::const_iterator it=map.begin(); it!=map.end(); ++it)
  {
    cout<< it->first <<"\t "<< it->second <<endl;
  }

  cout<< "\nerase b and d" <<endl;

  for (std::map<std::string, int>::iterator it=map.begin(); it!=map.end(); ++it)
  {
    if (it->first == "b") map.erase(it);
    // if (it->first == "d") map.erase(it);
  }

  // can be done without any iterators!
  map.erase("d");

  for (std::map<std::string, int>::const_iterator it=map.begin(); it!=map.end(); ++it)
  {
    cout<< it->first <<"\t "<< it->second <<endl;
  }

  cout<< "\nerase elements starting from the second" <<endl;

  //--const-- std::map<std::string, int>::const_iterator it=map.begin();
  std::map<std::string, int>::iterator it=map.begin();
  if (it != map.end()) ++it;      // it points to the second element now

  while (it != map.end()) {
    map.erase(it++);
  }

  for (std::map<std::string, int>::const_iterator it=map.begin(); it!=map.end(); ++it)
  {
    cout<< it->first <<"\t "<< it->second <<endl;
  }

  return 0;
}
