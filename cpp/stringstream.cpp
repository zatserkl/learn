#include <iostream>
#include <sstream>

using namespace std;

main()
{
  unsigned number = 0;
  std::string str;
  
  str = "400";    // this should work
  str = "abc";    // this shouldn't
  
  std::stringstream ss;
  ss << str;
  
  if (ss >> number) cout<< "OK" <<endl;
  else cout<< "conversion error" <<endl;
  cout<< "string = " << str << " number = " << number <<endl;
  
  cout<<endl<< "Try now to output to string without resetting of stream after the error" <<endl;
  
  std::string str_out;
  
  if (ss >> str_out) cout<< "OK" <<endl;
  else cout<< "conversion error" <<endl;
  cout<< "string = " << str << " str_out = " << str_out <<endl;
  
  cout<<endl<< "OK. ss.clear();" <<endl;
  ss.clear();
  
  if (ss >> str_out) cout<< "OK" <<endl;
  else cout<< "conversion error" <<endl;
  cout<< "string = " << str << " str_out = " << str_out <<endl;
  
  cout<<endl<< "--> You see: it works" <<endl;
}
