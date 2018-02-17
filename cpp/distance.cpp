// distance example
//
// NB: to allow distance to work with const_iterator
// you have to explicitly specify type of template parameter, i.e. const_iterator: 
// int i = std::distance<std::vector<int>::const_iterator>(v.begin(), it);
//
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using std::cout;    using std::endl;

int main () 
{
  cout<< "\nstd::list\n" <<endl;

  std::list<int> mylist;
  
  for (int i=0; i<10; i++) {
    int number = i*10;
    mylist.push_back (number);
    cout<< "added to list " << number <<endl;
  }

  std::list<int>::iterator first = mylist.begin();
  std::list<int>::iterator last = mylist.end();

  cout << "The distance is: " << std::distance(first,last) << endl;

  //return 0;

  for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
  {
    int i = std::distance(mylist.begin(), it);    //-- first, last  
    cout<< "distance i = " << i << "\t list element is " << *it <<endl;
  }

  cout<< "\nstd::vector\n" <<endl;

  std::vector<int> v;
  
  for (int i=0; i<10; i++) {
    int number = i*10;
    v.push_back (number);
    cout<< "added to vector " << number <<endl;
  }

  cout<< "\n--> use iterator" <<endl;

  for (std::vector<int>::iterator it=v.begin(); it!=v.end(); ++it)
  {
    int i = std::distance(v.begin(), it);         //-- first, last
    cout<< "distance i = " << i << "\t vector element is " << *it <<endl;
  }

  //-- use const_iterator

  cout<< "\n--> use const_iterator" <<endl;

  for (std::vector<int>::const_iterator it=v.begin(); it!=v.end(); ++it)
  {
    int i = std::distance<std::vector<int>::const_iterator>(v.begin(), it);         //-- first, last
    cout<< "distance i = " << i << "\t vector element is " << *it <<endl;
  }
}
