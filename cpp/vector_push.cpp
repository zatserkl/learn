#include <iostream>
#include <vector>

using std::cout;      using std::endl;

struct Struct {
  int a;
  int b;
};

void fill(std::vector<Struct>& v, int a, int b) {
  Struct local;
  local.a = a;
  local.b = b;

  v.push_back(local);
}

int main()
{
  std::vector<Struct> v;

  fill(v, 1, 2);

  cout<< "v.size() = " << v.size() <<endl;

  if (v.size() > 0) {
    cout<< "v[0].a = " << v[0].a << " v[0].b = " << v[0].b <<endl;
  }

  return 0;
}
