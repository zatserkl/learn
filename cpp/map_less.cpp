/*
  This is a wrong version of std::less

#include <map>
#include <string>
#include <iostream>

using namespace std;

struct Set {
  int a_;
  int b_;
  Set(int a, int b): a_(a), b_(b) {}
  bool operator < (const Set& set) const {
    if (a_ != set.a_) return a_ < set.a_;
    if (b_ != set.b_) return b_ < set.b_;
  } //-- need to add return false
};

main()
{
  std::map<Set, std::string> map;

  Set set1(1, 1);
  Set set2(0, 2);

  map[set1] = "set1";
  map[set2] = "set2";

  if (map.find(set1) != map.end()) cout<< "set1 is found" <<endl;
  else  cout<< "set1 is not found" <<endl;

  if (map.find(set2) != map.end()) cout<< "set2 is found" <<endl;
  else  cout<< "set2 is not found" <<endl;

  for (std::map<Set, std::string>::const_iterator i_map=map.begin(); i_map!=map.end(); ++i_map)
  {
    cout<< i_map->first.a_ <<" "<< i_map->first.b_ << " --> " << i_map->second <<endl;
  }
}

// The result:
//
// set1 is not found
// set2 is found
// 0 2 --> set2
// 1 1 --> set1
*/

#include <map>
#include <string>
#include <iostream>

using namespace std;

struct Set {
  int a_;
  int b_;
  Set(int a, int b): a_(a), b_(b) {}
  //
  //   this is presumably wrong operator
  //
     bool operator < (const Set& set) const {
       if (a_ != set.a_) return a_ < set.a_;
       if (b_ != set.b_) return b_ < set.b_;
       return false;
     }

//   //
//   //   this is correct operator
//   //
//   bool operator < (const Set& set) const {
//     return (a_ < set.a_)
//     || (a_ == set.a_ && b_ < set.b_);
//   }
// 
//   //
//   //   this is presumably correct operator
//   //
//   bool operator < (const Set& set) const {
//     return (a_ < set.a_)
//     || (a_ == set.a_ && b_ < set.b_);
//   }
};

main()
{
  std::map<Set, std::string> map;

  Set set1(1, 1);
  Set set2(0, 2);

  map[set1] = "set1";
  map[set2] = "set2";

  if (map.find(set1) != map.end()) cout<< "set1 is found" <<endl;
  else  cout<< "set1 is not found" <<endl;

  if (map.find(set2) != map.end()) cout<< "set2 is found" <<endl;
  else  cout<< "set2 is not found" <<endl;

  for (std::map<Set, std::string>::const_iterator i_map=map.begin(); i_map!=map.end(); ++i_map)
  {
    cout<< i_map->first.a_ <<" "<< i_map->first.b_ << " --> " << i_map->second <<endl;
  }
}
