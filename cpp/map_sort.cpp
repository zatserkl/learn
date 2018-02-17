#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Address {
  std::string str_;
  int a_;
  Address(std::string str, int a): str_(str), a_(a) {}
  
  //
  //   wrong
  //
  //   bool operator < (const Address& address) const {
  //     return false
  //       || str_ < address.str_
  //       || a_ < address.a_
  //     ;
  //   }
  
  //
  //   wrong
  //
  //   bool operator < (const Address& address) const {
  //     if (str_ < address.str_) return true;
  //     if (str_ > address.str_) return false;
  //     if (a_ < address.a_) return true;
  //     if (a_ > address.a_) return false;
  //   }

	//
	//   wrong operator Less
	//  
	//   bool operator < (const Address& address) const {
	//     if (str_ >= address.str_) return false;
	//     if (a_ >= address.a_) return false;
	//     return false;
	//   }

	//
	// Correct operator Less
	//  
  bool operator < (const Address& address) const
  {
    //
    // If current field < address.field return true, else if field > address.field return false.
    // If they are equal check next field.
    //
    if (str_ < address.str_) return true; else if (str_ > address.str_) return false;
    if (a_ < address.a_)     return true; else if (a_ > address.a_)     return false;
    return false;   // at this point all fields are equal
  }

//  //
// 	// Study of wrong operator Less
// 	//
//   bool operator < (const Address& address) const {
//     if (str_ >= address.str_) return false;
//     if (a_ >= address.a_) return false;
//     return false;
//   }
 
  std::string prints() const {
    std::stringstream ss;
    ss.str("");
    ss << "(\"" << str_ << "\", " << a_ << ")";
    return ss.str();
  }
//  friend ostream& operator<< (ostream& o, const Address& address) {
//    address.printo(o);
//    return o;
//  }
//  void printo(ostream& o) const {
//    o << "(\"" << str_ << "\", " << a_ << ")" <<endl;
//  }
};

main()
{
  std::map<Address, int> map;

  // address1.str_ < address2.str_, but address1.a_ > address2.a_
  // the "abc" < "xyz" but 2 > 1
  Address address1("abc", 2);
  Address address2("xyz", 1);

//   // no problem with this:
//   Address address1("abc", 1);
//   Address address2("xyz", 2);
  
  map[address1] = 1;
  cout<< "Added to map pair for address1: <" << address1.prints() << ", 1>" <<endl;
  cout<< "after adding of address1: map.count(address1) = " << map.count(address1) <<endl;
	
  map[address2] = 1001;
  cout<< "Added to map pair for address2: <" << address2.prints() << ", 1001>" <<endl;
  cout<< "after adding of address2: map.count(address2) = " << map.count(address2) <<endl;

  cout<< "\nmap contents:" <<endl;
  for (std::map<Address, int>::const_iterator map_it=map.begin(); map_it!=map.end(); ++map_it)
  {
    cout<< map_it->first.prints() <<" "<< map_it->second <<endl;
  }
/*
[cmsfpix1] learn> g++ map_sort.cpp
[cmsfpix1] learn> ./a.out
Added to map pair for address1: <("abc", 2), 1>
after adding of address1: map.count(address1) = 1
Added to map pair for address2: <("xyz", 1), 1001>
after adding of address2: map.count(address2) = 0

map contents:
("xyz", 1) 1001
("abc", 2) 1
*/
}
