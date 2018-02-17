#include "ANSIColor.h"
#include <iostream>

using std::cout;    using std::endl;
main()
{
  // suggested correct line
  cout << ACSave << ACBlue << "Here is the " << ACRed << "example!" << ACRecall << endl;

  // cout << ACSave << ACBlue << "Here is the " << ACRed << "example!" /* << ACRecall */ << endl;

  // leave cursor not in proper place
  // cout<< /* ACSave << */ ACBlue << "Here is the " << ACRed << "example!" << ACRecall << endl;

  cout<< "Ciao!" <<endl;
}
