#include <iostream>
#include"ANSIColor.h"

using std::cout;      using std::endl;

int main()
{
  cout<< ACPlain <<"ANSI colors\n" <<endl;

  cout<< ACUnderline <<"Main colors:" << ACPlain <<endl;

  cout<< ACBlack <<"ACBlack" << ACPlain <<endl;
  cout<< ACRed <<"ACRed" << ACPlain <<endl;
  cout<< ACGreen <<"ACGreen" << ACPlain <<endl;
  cout<< ACBrown <<"ACBrown" << ACPlain <<endl;
  cout<< ACBlue <<"ACBlue" << ACPlain <<endl;
  cout<< ACPurple <<"ACPurple" << ACPlain <<endl;
  cout<< ACCyan <<"ACCyan" << ACPlain <<endl;
  cout<< ACGray <<"ACGray" << ACPlain <<endl;
  
  cout<< ACUnderline <<"\nLight colors:" << ACPlain <<endl;
  cout<< ACDarkGray <<"ACDarkGray" << ACPlain <<endl;
  cout<< ACLightRed <<"ACLightRed" << ACPlain <<endl;
  cout<< ACLightGreen <<"ACLightGreen" << ACPlain <<endl;
  cout<< ACYellow <<"ACYellow" << ACPlain <<endl;
  cout<< ACLightBlue <<"ACLightBlue" << ACPlain <<endl;
  cout<< ACLightPurple <<"ACLightPurple" << ACPlain <<endl;
  cout<< ACLightCyan <<"ACLightCyan" << ACPlain <<endl;
  cout<< ACWhite <<"ACWhite" << ACPlain <<endl;
  cout<< ACBlack <<"ACBlack" << ACPlain <<endl;
  cout<< ACBold <<"ACBold" << ACPlain <<endl;
  cout<< ACUnderline <<"ACUnderline" << ACPlain <<endl;
  cout<< ACBlink <<"ACBlink" << ACPlain <<endl;
  cout<< ACReverse <<"ACReverse" << ACPlain <<endl;

  // restore colors
  // cout<< ACPlain <<"ACPlain to restore" <<endl;
}
