/* Andriy Zatserklyaniy <zatserkl@gmail.com> Mar 5, 2017

See article "A Brief Introduction to Rvalue References" by Stroustrup at al.
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html#Move_Semantics

NB: std::move with vectors:
	std::vector and std::string have move operations coded 
	which will completely avoid the tremendously more expensive copy operations.

clang++ -Wall -std=c++14 move14.cpp
*/

#include <iostream>
#include <numeric>      // std::iota
#include <vector>

using std::cout;	using std::endl;

class A {
protected:
    std::vector<int> vA_;
public:
    //
    // Copy semantics
    //
    A(int n=0) {
	cout<< "Default constructor A::A" <<endl;
	vA_.resize(n);
	std::iota(vA_.begin(), vA_.end(), 0);
	print();
    }
    A(const A& a) {
	cout<< "Copy constructor A::A(const A& a), copy semantics" <<endl;
	vA_ = a.vA_;
	print();
    }
    A& operator=(const A& a) {
	cout<< "Copy semantics operator A::=(const A& a)" <<endl;
	if (this != &a) {
	    vA_ = a.vA_;
	}
	print();
	return *this;
    }
    //
    // Move semantics
    //
    A(A&& a) {			// NB: argument is non-const
	cout<< "Copy constructor, move semantics A::A(A&& a)" <<endl;
	vA_ = std::move(a.vA_);		// for pointers to vector: pv = a.pv; a.pv = 0;
	print();
    }
    // A& operator=(A&& a) {
    // 	if (this != &a) {
    // 	    vA_ = std::move(a.vA_);
    // 	}
    // 	return *this;
    // }
    A& operator=(A&& a) {
	cout<< "Move semantics operator A::=(A&& a)" <<endl;
	std::swap(vA_, a.vA_);	//--NB: with std::swap we don't check this != &a
	print();
	return *this;
    }

    //
    // general methods
    //
    virtual int size() const {return vA_.size();}
    virtual void print() const {
	cout<< "vA_.size() = " << vA_.size() <<endl;
	for (auto element:vA_) cout<< element << " ";
	cout<<endl;
    }
};

class B: public A {
protected:
    std::vector<int> vB_;
public:
    B(int nA=0, int nB=0): A(nA)
    {
	cout<< "Default constructor B::B" <<endl;
	vB_.resize(nB);
	std::iota(vB_.begin(), vB_.end(), 100);
	print();
    }
    //
    // Copy semantics
    //
    B(const B& b): A(b), vB_(b.vB_) {
	cout<< "Copy constructor (copy semantics) B::B(const B&)" <<endl;
	
    }
    B& operator=(const B& b) {
	cout<< "Copy semantics operator=(const B& b)" <<endl;
	if (this != &b) {
	    A::operator=(b);
	    vB_ = b.vB_;
	}
	print();
	return *this;
    }
    //
    // Move semantics
    //
    B(B&& b): A(std::move(b)), vB_(std::move(b.vB_)) {	// no const here!
	cout<< "Copy constructor (move semantics) B::B(B&&)" <<endl;
    }
    B& operator=(B&& b) {
	cout<< "Move semantics operator=(B&& b)" <<endl;
	A::operator=(std::move(b));
	vB_ = std::move(b.vB_);
	print();
	return *this;
    }
    //
    // general methods
    //
    virtual int size() const {return vB_.size();}
    virtual void print() const {
	cout<< "vB_.size() = " << vB_.size() <<endl;
	for (auto element:vB_) cout<< element << " ";
	cout<<endl;
    }
};

int main()
{
    const int nA = 20;
    
    A a1(nA);

    cout<<endl;

    // std::vector<int> v;
    // v.resize(nA);
    
    // std::iota(v.begin(), v.end(), 0);
    // // std::iota(v.begin(), v.begin()+nA, 0);
    
    // cout<< "v.size() = " << v.size() <<endl;
    // for (auto element:v) cout<< element << " ";
    // cout<<endl;

    A a2(a1);

    cout<<endl;

    A a3(std::move(a2));	// calls move semantics copy constructor

    cout<< "a2.size() = " << a2.size() <<endl;	// a2.vA_ == 0 after move

    cout<<endl;

    A a4;
    a4 = a1;

    cout<< "a1.size() = " << a1.size() <<endl;	// a1.vA_ unchanged after copy

    cout<<endl;

    A a5;
    a5 = std::move(a4);

    cout<< "a4.size() = " << a4.size() <<endl;	// a4.vA_ == 0 after move

    cout<<endl;

    //
    // Derived class
    //

    cout<< "Derived class B\n" <<endl;

    B b1(20, 22);

    cout<< "Make new objects\n" <<endl;

    B b2(b1);

    cout<<endl;

    B b3(std::move(b2));
    cout<< "b3.print(): ";
    b3.print();

    cout<< "\nAfter explicit use of move semantics" <<endl;
    cout<< "the object b2 has been left in some strange but valid state\n" <<endl;
    b2.print();

    cout<< "\nCopy semantics assignment operator\n" <<endl;

    B b4;
    cout<< "perform the copy b4 = b3. b3.print() = ";
    b3.print();
    b4 = b3;
    cout<< "\nb4.print() = ";
    b4.print();

    cout<< "\nMove semantics assignment operator\n" <<endl;

    B b5;
    cout<< "-- assign b5 = std::move(b4)" <<endl;
    b5 = std::move(b4);

    cout<< "\nAfter explicit use of move semantics" <<endl;
    cout<< "the object b4 has been left in some strange but valid state\n" <<endl;
    b4.print();
    
    return 0;
}
