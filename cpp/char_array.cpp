#include <iostream>
#include <cstring>

using std::cout;      using std::endl;

main()
{
  // NB: the dimension shown is size of string: (3 chars) + '\0'
  // const char* hcname[4] = {"BmI", "BmO", "BpI", "BpO"};
  // const char hcname[][4] = {"BmI", "BmO", "BpI", "BpO"};
  const char* hcname[] = {"BmI", "BmO", "BpI", "BpO"};

  // Both approach are valid
  // See K&R Sec. 5.9 "Pointers vs. Multi-dimensional Arrays", p.101
  // Looks like the most convenient is
  // const char* hcname[] = {"BmI", "BmO", "BpI", "BpO"};

  for (int i=0; i<4; ++i) {
    cout<< hcname[i] <<endl;
  }

  // classic array (to be used in class)
  char ar_hcname[4][8];
  std::strcpy(ar_hcname[0], "aaaaaaa");   // remember about tailing '\0'
  std::strcpy(ar_hcname[1], "bbbbbbb");
  std::strcpy(ar_hcname[2], "ccccccc");
  std::strcpy(ar_hcname[3], "ddddddd");
  for (int i=0; i<4; ++i) cout<< ar_hcname[i] <<endl;
}
