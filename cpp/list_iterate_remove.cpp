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

  cout<< "remove elements which == *it*2" <<endl;

  for (std::list<int>::const_iterator it=list.begin(); it!=list.end(); ++it) {
    std::list<int>::const_iterator next = it;
    ++next;
    while (next != list.end()) {
      if (*next == *it*2) {
        cout<< "*it = " << *it << " remove *it*2 = " << *next <<endl;
        next = list.erase(next);
      }
      else ++next;
    }
  }

  for (std::list<int>::const_iterator it=list.begin(); it!=list.end(); ++it) {
    cout<< std::distance<std::list<int>::const_iterator>(list.begin(), it) << " " << *it <<endl;
  }

  return 0;
}
