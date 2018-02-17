#include <vector>
#include <iostream>

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
  std::vector<Object> v_;
  Object out_of_range;    // instance to be returned in case of index is out of range
public:
  VLike() {
    for (unsigned i=0; i<3; ++i) {
      v_.push_back(Object(i));  // I use 'explicit' to forbid implicit conversion obj=5
      cout<< "v_[" << i << "] = " << v_[i] <<endl;
    }
  }
  // subscript operator for non-const objects returns modifiable lvalue
  Object& operator [](unsigned i) {                 // will be used the most
    if (i < v_.size()) return v_[i];
    else return out_of_range;
  }
  // subscript operator for const objects returns rvalue
  const Object& operator [](unsigned i) const {     // for const objects
    if (i < v_.size()) return v_[i];
    else return out_of_range;
  }
};

/*
Answer on similar problem: http://stackoverflow.com/questions/2808030/subscript-operator-on-pointers:
It's because you can't overload operators for a pointer type; you can only overload an operator where at least one of the parameters (operands) is of class type or enumeration type.

Thus, if you have a pointer to an object of some class type that overloads the subscript operator, you have to dereference that pointer in order to call its overloaded subscript operator.

In your example, a has type MyClass*; this is a pointer type, so the built-in operator[] for pointers is used. When you dereference the pointer and obtain a MyClass, you have a class-type object, so the overloaded operator[] is used.
This is basically my problem.
*/
class VLikePtr {
// private:
public:
  std::vector<Object*> v_;
  Object out_of_range;    // instance to be returned in case of index is out of range
public:
  VLikePtr() {
    for (unsigned i=0; i<3; ++i) {
      v_.push_back(new Object(i));  // I use 'explicit' to forbid implicit conversion obj=5
      cout<< "constructor VLikePtr: *v_[" << i << "] = " << *v_[i] <<endl;
    }
  }
  void Show() const {
    for (int i=0; i<v_.size(); ++i) {
      cout<< "*v_[" << i << "] = " << *v_[i] <<endl;
    }
  }
  // subscript operator for non-const objects returns modifiable lvalue
  Object* operator [](unsigned i) {                 // will be used the most
    if (i < v_.size()) return v_[i];
    // if (i < v_.size()) {
    //   Object* object = v_[i];
    //   return object;
    // }
    else return &out_of_range;
  }
  // subscript operator for const objects returns rvalue
  const Object* operator [](unsigned i) const {     // for const objects
    if (i < v_.size()) return v_[i];
    else return &out_of_range;
  }
};

main()
{
  // test of Object
  Object obj(5);
  cout<< "obj = " << obj <<endl;

  VLike vlike;
  for (unsigned i=0; i<5; ++i) {
    // cout<< "vlike[" << i << "] = ";   vlike[i].Print();   cout<<endl;
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

  ////////////////

  cout<<endl<< "--> try pointer version" <<endl;
  VLikePtr vlikePtr;
  Object* object7 = new Object(7);
  cout<< "change vlikePtr.v_[0] = object7" <<endl;
  // vlikePtr[0] = object7;
  vlikePtr.v_[0] = object7;
  vlikePtr.Show();
}
