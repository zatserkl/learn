#include <iostream>

//
// It turned out that I select Clone instead of overload of the assign operator
//

using std::cout;      using std::endl;

class Base {
public:
  int* i0_;
  Base(int i0) {
    i0_ = new int;
    *i0_ = i0;
  }
  Base(const Base& base) {
    i0_ = new int;
    *i0_ = *base.i0_;
  }
  virtual ~Base() {
    cout<< "destructor ~Base: *i0_ = " << *i0_ <<endl;
    delete i0_;
    i0_ = 0;
  }
  // Base& operator =(const Base& base) {
  //   cout<< "Base::operator =" <<endl;
  //   if (i0_) delete i0_;
  //   i0_ = new int;
  //   *i0_ = *base.i0_;
  //   return *this;
  // }
  virtual Base* Clone() const = 0;  // pure virtual method to prevent creation of Base object
  virtual void Show() const {
    cout<< "Base::Show: *i0_ = " << *i0_ <<endl;
  }
};

class Child1: public Base {
public:
  int* i1_;
  Child1(int i0, int i1): Base(i0) {
    i1_ = new int;
    *i1_ = i1;
  }
  Child1(const Child1& child1): Base(child1) {
    i1_ = new int;
    *i1_ = *child1.i1_;
  }
  ~Child1() {
    cout<< "destructor ~Child1: *i1_ = " << *i1_ <<endl;
    delete i1_;
    i1_ = 0;
  }
  Child1* Clone() const {
    Child1* child1 = new Child1(*this);
    return child1;
  }
  // -- do not need this operator really
  // Child1& operator =(const Child1& child1) {
  //   cout<< "Child1::operator =" <<endl;
  //   if (i1_) delete i1_;
  //   i1_ = new int;
  //   *i1_ = *child1.i1_;
  //   return *this;
  // }
  virtual void Show() const {
    cout<< "Child1::Show: *i0_ = " << *i0_ << " *i1_ = " << *i1_ <<endl;
  }
};

class Child2: public Base {
public:
  int* i2_;
  Child2(int i0, int i2): Base(i0) {
    i2_ = new int;
    *i2_ = i2;
  }
  Child2(const Child2& child2): Base(child2) {
    i2_ = new int;
    *i2_ = *child2.i2_;
  }
  ~Child2() {
    cout<< "destructor ~Child2: *i2_ = " << *i2_ <<endl;
    delete i2_;
    i2_ = 0;
  }
  Child2* Clone() const {
    Child2* child2 = new Child2(*this);
    return child2;
  }
  // -- I do not really need this operator
  // Child2& operator =(const Child2& child2) {
  //   cout<< "Child2::operator =" <<endl;
  //   if (i2_) delete i2_;
  //   i2_ = new int;
  //   *i2_ = *child2.i2_;
  //   return *this;
  // }
  virtual void Show() const {
    cout<< "Child2::Show: *i0_ = " << *i0_ << " *i2_ = " << *i2_ <<endl;
  }
};

int main()
{
  Base* a[3];
  a[0] = new Child1(0,1);
  cout<< "*(*a)[0].i0_ = " << *(*a)[0].i0_ <<endl;
  //-- cout<< "(*a)[0].i1_ = " << (*a)[0].i1_ <<endl; // error: ‘class Base’ has no member named ‘i1_’
  a[0]->Show();
  (*a)[0].Show();

  cout<< "Clone default to all channels" <<endl;

  for (int i=1; i<3; ++i) {
    a[i] = a[0]->Clone();
  }

  for (int i=0; i<3; ++i) {
    cout<< "i = " << i << "\t ";
    a[i]->Show();
  }

  cout<< "Change the last object to Child2" <<endl;

  delete a[2];
  a[2] = new Child2(10,12);

  for (int i=0; i<3; ++i) {
    cout<< "i = " << i << "\t ";
    a[i]->Show();
  }

  cout<< "\nFinal clean up of the memory" <<endl;
  for (int i=0; i<3; ++i) delete a[i];
  return 0;
}
