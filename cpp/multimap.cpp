#include <map>
#include <string>
#include <iostream>

using std::cout;      using std::endl;

int main()
{
  std::multimap<int, std::string> mm;

  std::string s1 = "a";     // size = 1
  std::string s2 = "ab";    // size = 2
  std::string s2a = "cd";   // size = 2
  std::string s3 = "abc";   // size = 3
  std::string s3a = "def";  // size = 3
  std::string s3b = "ghi";  // size = 3
  std::string s2b = "zz";   // size = 2

  const std::string* str;
  str = &s1;  mm.insert(std::make_pair(str->size(), *str));
  str = &s2;  mm.insert(std::make_pair(str->size(), *str));
  str = &s2a; mm.insert(std::make_pair(str->size(), *str));
  str = &s3;  mm.insert(std::make_pair(str->size(), *str));
  str = &s3a; mm.insert(std::make_pair(str->size(), *str));
  str = &s3b; mm.insert(std::make_pair(str->size(), *str));
  str = &s2b; mm.insert(std::make_pair(str->size(), *str));

  cout<< "print the whole map" <<endl;
  for (std::multimap<int, std::string>::const_iterator it=mm.begin(); it!=mm.end(); ++it) {
    cout<< it->first << " " << it->second <<endl;
  }

  int key = 2;
  cout<< "print all strings for key = " << key <<endl;

  std::multimap<int, std::string>::const_iterator it = mm.lower_bound(key);
  std::multimap<int, std::string>::const_iterator itend = mm.upper_bound(key);

  while (it != itend) {
    cout<< it->first << " " << it->second <<endl;
    ++it;
  }

  return 0;
}
