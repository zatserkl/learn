#include <iostream>
#include <vector>
#include <string>

using std::cout;      using std::endl;

main()
{
  std::vector<std::vector<int> > vvint;
  std::vector<int> vint;

  vint.clear();
  vint.push_back(1);
  vint.push_back(2);
  vint.push_back(3);
  vvint.push_back(vint);

  vint.clear();
  vint.push_back(10);
  vint.push_back(20);
  vint.push_back(30);
  vvint.push_back(vint);

  for (std::vector<std::vector<int> >::iterator i_vv=vvint.begin(); i_vv!=vvint.end(); ++i_vv)
  {
    std::vector<int>& v = *i_vv;
    for (std::vector<int>::iterator i_v=v.begin(); i_v!=v.end(); ++i_v)
    {
      int& str = *i_v;
      cout<< str <<endl;
    }
  }

  std::vector<std::vector<std::string> > vvstring;
  std::vector<std::string> vstring;

  vstring.clear();
  vstring.push_back("one");
  vstring.push_back("two");
  vstring.push_back("three");
  vvstring.push_back(vstring);

  vstring.clear();
  vstring.push_back("ONE");
  vstring.push_back("TWO");
  vstring.push_back("THREE");
  vvstring.push_back(vstring);

  for (std::vector<std::vector<std::string> >::iterator i_vv=vvstring.begin(); i_vv!=vvstring.end(); ++i_vv)
  {
    std::vector<std::string>& v = *i_vv;
    for (std::vector<std::string>::iterator i_v=v.begin(); i_v!=v.end(); ++i_v)
    {
      std::string& str = *i_v;
      cout<< str <<endl;
    }
  }
}
