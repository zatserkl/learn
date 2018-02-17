#include <iostream>
#include <vector>

using std::cout;      using std::endl;

main()
{
  std::vector<int> v;

  for (int i=0; i<5; ++i) v.push_back(10+i);

  for (std::vector<int>::const_iterator i_v=v.begin(); i_v!=v.end(); ++i_v)
  {
    // NB: to use distance for const_iterator you need to specify the type: std::vector<int>::const_iterator> here
    cout<< "std::distance<std::vector<int>::const_iterator>(v.begin(), i_v) = " << std::distance<std::vector<int>::const_iterator>(v.begin(), i_v) << "\t *i_v = " << *i_v <<endl;
    std::vector<int>::const_iterator prev = i_v;
    std::advance(prev, -1);
    if (prev == v.end()) cout<< "   prev == v.end()" <<endl;       // no such events!
    if (prev < v.begin()) cout<< "   prev < v.begin()" <<endl;     // for the first element
    if (prev >= v.begin()) cout<< "   prev >= v.begin(), prev element is " << *prev <<endl;
  }
}
