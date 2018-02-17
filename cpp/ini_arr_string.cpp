#include <iostream>
#include <string>

using std::cout;      using std::endl;

int main()
{
  std::string astr[3] = {
    "string 1",
    "string 2",
    "string 3"
  };

  for (int i=0; i<3; ++i) {
    cout<< astr[i] <<endl;
  }

  return 0;
}
