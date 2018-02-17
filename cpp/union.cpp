#include <iostream>

using std::cout;      using std::endl;

main()
{
  // unnamed struct inside the union
  union Par {
    int a[10];
    struct {
      int a1;
      int a2;
      int a3;
    };          // NB: anonymous union. Does not supported by CINT
  };

  Par par;
  par.a1 = 1;
  par.a2 = 2;
  par.a3 = 3;
  for (int i=0; i<3; ++i) cout<< "par.a[" << i << "] = " << par.a[i] <<endl;

  // named struct inside the union

  union ParObject {
    int a[10];
    struct {
      int a1;
      int a2;
      int a3;
    } object;
  };

  ParObject parObject;
  parObject.object.a1 = 1;
  parObject.object.a2 = 2;
  parObject.object.a3 = 3;
  for (int i=0; i<3; ++i) cout<< "par.a[" << i << "] = " << par.a[i] <<endl;
}
