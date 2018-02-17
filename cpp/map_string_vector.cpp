#include <iostream>
#include <string>
#include <vector>
#include <map>

//? std::istream& operator << (std::istream& is, std::vector<int> v)

using std::cout;      using std::endl;

// 
// does not work: to be understood
// 
// class Quoted: public std::string {
// public:
//   Quoted(std::string str) {
//     *this = str;
//   }
//   Quoted(const char* str) {
//     *this = str;
//   }
// };
// 
// std::ostream& operator << (std::ostream& os, const Quoted& str) {
//   os << "\"" << str << "\"";
//   return os;
// }
 
main()
{
  std::string abc("abc");
  cout<< abc <<endl;
  
  std::map< std::string, std::vector<int> > map;

  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  v.push_back(2);

  map["explicit"] = v;

  std::vector<int>* v_ptr = &map["implicit"];
  v_ptr->push_back(1000);
  v_ptr->push_back(1001);
  v_ptr->push_back(1002);
  
  for (std::map< std::string, std::vector<int> >::const_iterator i_map=map.begin(); i_map!=map.end(); ++i_map)
  {
    std::string key = i_map->first;
    std::vector<int> vec = i_map->second;
    cout<< "map[" << key << "] has " << vec.size() << " entries:" <<endl;
    for (std::vector<int>::const_iterator i_vec=vec.begin(); i_vec!=vec.end(); ++i_vec) {
      cout<< *i_vec <<endl;
    }
  }

  cout<<endl<< "The best way to store in std::map< std::string, std::vector<int> > is just add to vector!" <<endl;
  cout<< "map_string_vector[\"key1\"].push_back(1);" <<endl<<endl;

  std::map< std::string, std::vector<int> > map_string_vector;

  map_string_vector["key1"].push_back(1);
  map_string_vector["key1"].push_back(2);
  map_string_vector["key2"].push_back(1001);
  map_string_vector["key2"].push_back(1002);

  for (std::map< std::string, std::vector<int> >::const_iterator i_map=map_string_vector.begin(); i_map!=map_string_vector.end(); ++i_map)
  {
    std::string key = i_map->first;
    std::vector<int> vec = i_map->second;
    cout<< "map_string_vector[" << key << "] has " << vec.size() << " entries:" <<endl;
    for (std::vector<int>::const_iterator i_vec=vec.begin(); i_vec!=vec.end(); ++i_vec) {
      cout<< *i_vec <<endl;
    }
  }
}

