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

  //////////////////////////////////////////////////
  //
  //  Uncomment to see different effects in output
  //
  //////////////////////////////////////////////////

  // int number_to_remove = 8;
  // cout<< "remove element " << number_to_remove <<endl;

  // for (std::list<int>::iterator it=list.begin(); it!=list.end(); ++it)
  // {
  //   cout<< "current element is " << *it <<endl;
  //   if (*it == number_to_remove) {
  //     it = list.erase(it);
  //   }
  // }

  // for (std::list<int>::const_iterator it=list.begin(); it!=list.end(); ++it) {
  //   cout<< std::distance<std::list<int>::const_iterator>(list.begin(), it) << " " << *it <<endl;
  // }

  cout<< "remove elements >= 3" <<endl;

  for (std::list<int>::iterator it=list.begin(); it!=list.end(); ++it)
  {
    cout<< "current element is " << *it <<endl;
    if (*it >= 3) {
      it = list.erase(it);
    }
  }

  for (std::list<int>::const_iterator it=list.begin(); it!=list.end(); ++it) {
    cout<< std::distance<std::list<int>::const_iterator>(list.begin(), it) << " " << *it <<endl;
  }

  return 0;
}
