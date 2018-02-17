#include <list>
#include <iostream>

using std::cout;      using std::endl;

int main()
{
  std::list<int> list;
  for (int i=0; i<10; ++i) list.push_back(i);

  for (std::list<int>::const_iterator it=list.begin(); it!=list.end(); ++it) {
    cout<< std::distance<std::list<int>::const_iterator>(list.begin(), it) << " " << *it <<endl;
  }

  cout<< "remove elements >= 3" <<endl;

  //
  //-- NB: there is no increment of cycle variable below!
  //

  //--const-- for (std::list<int>::const_iterator it=list.begin(); it!=list.end();) // NB: no increament
  for (std::list<int>::iterator it=list.begin(); it!=list.end();)                   // NB: no increament
  {
    if (*it < 3) ++it;
    else it = list.erase(it);
  }

  for (std::list<int>::const_iterator it=list.begin(); it!=list.end(); ++it) {
    cout<< std::distance<std::list<int>::const_iterator>(list.begin(), it) << " " << *it <<endl;
  }

  return 0;
}
