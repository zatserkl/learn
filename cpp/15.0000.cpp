#include <iostream>
#include <iomanip>

using std::cout;      using std::endl;

main()
{
  for (int i=0; i<55; ++i) {
    int j = i+1;
    cout<< "15." << std::setw(4) << std::setfill('0') << j <<endl;
  }
}
