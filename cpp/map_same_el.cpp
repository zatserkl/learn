#include <map>
#include <iostream>
#include <string>

using namespace std;

main()
{
  std::map<std::string, int> map;

  map["Jan"] = 1;
  map["Feb"] = 2;
  map["Mar"] = 3;

  //-- see about the std::distance in distance.cpp

  for (std::map<std::string, int>::iterator it=map.begin(); it!=map.end(); ++it)
  {
    cout<< std::distance(map.begin(), it) << " " << it->first << " " << it->second <<endl;
  }

  // does not work
  //
  // for (std::map<std::string, int>::const_iterator const_it=map.begin(); const_it!=map.end(); ++const_it)
  // {
  //   std::map<std::string, int>::iterator it = const_cast<std::map<std::string, int>::iterator>(const_it);
  //   cout<< std::distance(map.begin(), it) << " " << const_it->first << " " << const_it->second <<endl;
  // }

  // does not work either
  //
  // for (std::map<std::string, int>::const_iterator const_it=map.begin(); const_it!=map.end(); ++const_it)
  // {
  //   std::map<std::string, int>::iterator* it = const_cast<std::map<std::string, int>::iterator*>(&const_it);
  //   cout<< std::distance(map.begin(), *it) << " " << const_it->first << " " << const_it->second <<endl;
  // }
  
	cout<< "\nThe number of elements in map now is map.size() = " << map.size() <<endl;
	
  cout<< "Let's insert another \"Feb\" element" <<endl;
  map["Feb"] = 100;

  cout<< "The number of elements in map after inserting another \"Feb\" is map.size() = " << map.size() <<endl<<endl;
	
  for (std::map<std::string, int>::iterator it=map.begin(); it!=map.end(); ++it)
  {
    cout<< std::distance(map.begin(), it) << " " << it->first << " " << it->second <<endl;
  }

	cout<< "\n   The element \"Dec\" is absend in our map" <<endl<<endl;

	//cout<< "look for absend element, e.g. Dec" <<endl;
	//cout<< "map[\"Dec\"] = " << map["Dec"] <<endl;

	//--  Terrible: looks like statement
	//--  map["Dec"]
	//--  inserte an element in the map. Actually it inserted 0
	//
	// see also from http://www.cprogramming.com/tutorial/stl/stlmap.html
	//
	// So adding keys to a map can be done without doing anything special -- 
	// we just need to use the key and it will be added automatically along with the corresponding data item.

	cout<< "//-- NB: Statement just" <<endl;
	cout<< "map[\"Dec\"] will insert pair <\"Dec\",0> in the map" <<endl;
	cout<< "\nThe only way to check for element is like map.find(\"Feb\") != map.end()" <<endl;

  cout<< "find the element whose key is Feb: map.find(\"Feb\")" <<endl;

	cout<<endl;
	
  cout<< "find the element whose key is Feb" <<endl;
	if (map.find("Feb") != map.end()) {
		cout<< "element corresponding to \"Feb\" is " << map.find("Feb")->second <<endl;
	}
	else cout<< "element corresponding to \"Feb\" is absend" <<endl;
	cout<< "find the element whose key is Dec" <<endl;
	if (map.find("Dec") != map.end()) {
		cout<< "element corresponding to \"Dec\" is " << map.find("Dec")->second <<endl;
	}
  else cout<< "element corresponding to \"Dec\" is absend" <<endl;
}
