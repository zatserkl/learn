#include <map>
#include <list>
#include <string>
#include <iostream>

using std::cout;      using std::endl;

int main()
{
  std::map<int, std::list<std::string> > mapIntList;

  std::string s1 = "a";     // size = 1
  std::string s2 = "ab";    // size = 2
  std::string s2a = "cd";   // size = 2
  std::string s3 = "abc";   // size = 3
  std::string s3a = "def";  // size = 3
  std::string s3b = "ghi";  // size = 3
  std::string s4 = "abcd";  // size = 4
  std::string s4a = "efgh"; // size = 4
  std::string s4b = "iklm"; // size = 4
  std::string s4c = "nopq"; // size = 4

  const std::string* str;
  str = &s1;  mapIntList[str->size()].push_back(*str);
  str = &s2;  mapIntList[str->size()].push_back(*str);
  str = &s2a; mapIntList[str->size()].push_back(*str);
  str = &s3;  mapIntList[str->size()].push_back(*str);
  str = &s3a; mapIntList[str->size()].push_back(*str);
  str = &s3b; mapIntList[str->size()].push_back(*str);
  str = &s4;  mapIntList[str->size()].push_back(*str);
  str = &s4a; mapIntList[str->size()].push_back(*str);
  str = &s4b; mapIntList[str->size()].push_back(*str);
  str = &s4c; mapIntList[str->size()].push_back(*str);

  for (std::map<int, std::list<std::string> >::const_iterator it=mapIntList.begin(); it!=mapIntList.end(); ++it) {
    cout<< it->first << ":";
    for (std::list<std::string>::const_iterator ilist=it->second.begin(); ilist!=it->second.end(); ++ilist) {
      cout<< " " << *ilist;
    }
    cout<<endl;
  }

  cout<< "\nremove elements from the map" <<endl;

  std::map<int, std::list<std::string> >::const_iterator it=mapIntList.begin();
  ++it;                     // points to the second element now

  mapIntList.erase(it++);   // remove the second element

  cout<< "it->first = " << it->first;
  for (std::list<std::string>::const_iterator ilist=it->second.begin(); ilist!=it->second.end(); ++ilist) {
    cout<< " " << *ilist;
  }
  cout<<endl;

  cout<< "\nmap after removing of the second element" <<endl;

  for (std::map<int, std::list<std::string> >::const_iterator it=mapIntList.begin(); it!=mapIntList.end(); ++it) {
    cout<< it->first << ":";
    for (std::list<std::string>::const_iterator ilist=it->second.begin(); ilist!=it->second.end(); ++ilist) {
      cout<< " " << *ilist;
    }
    cout<<endl;
  }

  return 0;
}
