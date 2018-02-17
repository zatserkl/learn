/*
[lxplus100] ~/learn > vi list.cpp
[lxplus100] ~/learn > g++ list.cpp
[lxplus100] ~/learn > ./a.out
Segmentation fault
*/

#include <list>
#include <string>
#include <iostream>

using std::cout;    using std::endl;

int main()
{
  std::list<std::string> list;
  // cout<< list.back() <<endl;   // results in Segmentation fault

  //--error: std::list<std::string>::const_iterator last = list.rbegin();
  // std::list<std::string>::iterator last = --list.end();

  list.push_back("last element");
  list.insert(--list.end(), std::string("before the last"));  // works with empty list too

  for (std::list<std::string>::const_iterator it_list=list.begin(); it_list!=list.end(); ++it_list) {
    cout<< std::distance<std::list<std::string>::const_iterator>(list.begin(), it_list) << "\t " << *it_list <<endl;
  }

  return 0;
}
