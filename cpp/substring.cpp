#include <iostream>
#include <string>

using std::cout;      using std::endl;

main()
{
  std::string portcard = "FPix_BpI_D1_PRT2";

  std::string halfcyl = portcard.substr(5,3);
  cout<< "half cylinder name is " << halfcyl <<endl;

  cout<< "disk is " << portcard.substr(10,1) <<endl;

  cout<< "portcard is " << portcard.substr(15,1) <<endl;
}
