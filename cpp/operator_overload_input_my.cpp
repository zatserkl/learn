#include <vector>
#include <iostream>
#include <string>

using std::cout;      using std::endl;

// declare some user-defined object (it's too simple with just int)

class Object {
private:
  int var_;
public:
  Object(): var_(-1) {}                   // default, ill-formed object
  explicit Object(int var): var_(var) {}  // 'explicit' to forbid e.g. obj=5
  void Print() {
    cout<< var_;
  }
  int var() const {return var_;}
	
  // declare global operator stream output << as a friend to let it access private data
  // (if you are going to use private data directly, not through method)
  friend std::ostream& operator <<(std::ostream&, const Object&);  // for const Object
  friend std::ostream& operator <<(std::ostream&, Object&);        // for Object
  // operator stream input (>>)
  Object& operator >>(int var) {
    var_ = var;
    return *this;
  }
};

// the best is to define standalone operator <<. (See also learn/ostream.cpp)

std::ostream& operator <<(std::ostream& os, const Object& object) {
  os << object.var();
  return os;
}
std::ostream& operator <<(std::ostream& os, Object& object) {
  os << object.var();
  return os;
}

// class to test overloading of the operator[]
//
// There are two mutually inconsistent (different return) ways:
// 1) you can return object
// 2) you can return reference on the object
// You have select one of them. If you are going use object just readonly, use (1),
// if you are going to use it in left part of assign operator, use reference.
// --> The reference should not be const.
//

class VLike {
private:
  std::vector<Object> vobj_;
  std::vector<int> vint_;
  std::vector<std::string> vstring_;
  // objects to be returned in case of out of range
  Object obj_out_of_range;    // instance to be returned in case of index is out of range
  std::string string_out_of_range;
  int int_out_of_range;
public:
  VLike(): int_out_of_range(-1) {}
  void Show() const {
    for (unsigned i=0; i<vint_.size(); ++i) cout<< "vint_[" << i << "] = " << vint_[i] <<endl;
    for (unsigned i=0; i<vstring_.size(); ++i) cout<< "vstring_[" << i << "] = " << vstring_[i] <<endl;
    for (unsigned i=0; i<vobj_.size(); ++i) cout<< "vobj_[" << i << "] = " << vobj_[i] <<endl;
  }
  Object& operator [](unsigned i) {                 // will be used the most
    if (i < vobj_.size()) return vobj_[i];
    else return obj_out_of_range;
  }
  const Object& operator [](unsigned i) const {     // for const objects
    if (i < vobj_.size()) return vobj_[i];
    else return obj_out_of_range;
  }
  //
  // redefine input stream operator in my non-standard way
  //
  VLike& operator <<(const Object& obj) {
    vobj_.push_back(obj);
    return *this;
  }
  VLike& operator <<(std::string str) {
    vstring_.push_back(str);
    return *this;
  }
  VLike& operator <<(int val) {
    vint_.push_back(val);
    return *this;
  }
};

main()
{
  // test of Object
  Object obj(5);
  cout<< "obj = " << obj <<endl;

  VLike vlike;
  for (unsigned i=0; i<5; ++i) {
    // /* trivial */ cout<< "vlike[" << i << "] = ";   vlike[i].Print();   cout<<endl;
    cout<< "vlike[" << i << "] = " << vlike[i] <<endl;
    Object obj = vlike[i];
    cout<< "vlike[" << i << "] = " << obj <<endl;
  }

  const Object& obj_const = vlike[2];
  cout<< "obj_const: " << obj_const <<endl;

  cout<< "change the first element to 5" <<endl;
  vlike[0] = Object(5); // I use 'explicit' keyword in Object c-tor to forbid vlike[0]=5;
  cout<< "the first element now is " << vlike[0] <<endl;

  cout<< "change the second element to 7 using overloaded operator of stream input" <<endl;
  vlike[1] >> 7;
  cout<< "the second element now is " << vlike[1] <<endl;

  cout<<endl<< "Test my non-standard input operator" <<endl;
  vlike << 100 << 200;
  vlike << "abc" << "def";
  vlike << Object(123) << Object(456);
  vlike.Show();
}
