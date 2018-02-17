#include <vector>
#include <iostream>

using std::cout;      using std::endl;

/* compiles, but outputs
learn> g++ vector_array.cpp
learn> ./a.out
v[0] = 0
v[1] = 1
v[2] = 2
v[3] = 3
v[4] = 4
a[0] = 30195792
a[1] = 0
a[2] = 30195812
a[3] = 0
a[4] = 30195824
a[0] = 30195792
a[1] = 0
a[2] = 30195812
a[3] = 0
a[4] = 30195824
*/

void f(unsigned int n, int* a) {
  for (int i=0; i<n; ++i) cout<< "a[" << i << "] = " << a[i] <<endl;
}

main()
{
  std::vector<int> v;
  for (int i=0; i<5; ++i) v.push_back(i);
  for (int i=0; i<v.size(); ++i) cout<< "v[" << i << "] = " << v[i] <<endl;

  int n = v.size();

  f(n, (int*)&v);

  int* a = (int*) &v;

  f(n, a);
}
