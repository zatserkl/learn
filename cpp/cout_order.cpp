#include <iostream>
#include <vector>
#include <string>

using std::cout;      using std::endl;

std::vector<std::string> vhistory;

class Class {
  std::string str_;
public:
  Class(std::string str): str_(str) {}
  std::string getString() const
  {
    // register in history
    vhistory.push_back(str_);
    return str_;
  }
};

main()
{
  Class a("a");
  Class b("b");

  cout<< a.getString() <<" "<< b.getString() <<endl;

  cout<<endl<< "order of cout arguments in cout<< a.getString() <<\" \"<< b.getString() <<endl:" <<endl;
  for (int i=0; i<vhistory.size(); ++i) {
    cout<< i <<" "<< vhistory[i] <<endl;
  }
}
