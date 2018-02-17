#include <iostream>

using std::cout;      using std::endl;

class Class {
private:
  int val_;
  std::string name_;
public:
  Class(const std::string& name, int val): val_(val), name_(name) {}
  void print() const {
    cout<< name_ << " val_ = " << val_ <<endl;
  }
  void Access(Class& instance) {
    instance.val_ = val_;
  }
};

main()
{
  Class class1("class1", 1);
  Class class2("class2", 2);

  class1.print();
  class2.print();

  cout<< "access private member of class1 to set corresponding member of class2 to its value" <<endl;
  class2.Access(class1);

  class1.print();
  class2.print();
}
