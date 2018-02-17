#include <iostream>
#include <vector>
#include <string>

using std::cout;      using std::endl;

//------------------ these preprocessor directives do not work for ACLiC
#ifdef __CINT__
//#if defined(__CINT__) || defined(__MAKECINT__)
void vector_erase()
#else
int main()
#endif

{
  std::vector<std::string> v;
  v.push_back("abc");
  v.push_back("def");
  v.push_back("ghi");
  v.push_back("def");
  v.push_back("jkl");

  cout<< "v.size() = " << v.size() <<endl;

  // std::string pattern = "def";   // the parameter in the middle is OK
  std::string pattern = "jkl";      //-- erasing of the last element is dangerous!!!

  for (std::vector<std::string>::iterator it=v.begin(); it!=v.end(); ++it) {
    if (*it == pattern) v.erase(it);
    if (it == v.end()) break;       //-- prevents crash after erasing of the last element
  }

  cout<< "v.size() = " << v.size() <<endl;
}
