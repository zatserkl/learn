// works with ACLiC, but not with CINT

/*
// .L maplink.C
// maplink()
a: 1
b: 2
c: 3
Error: Can't call map<string,map<string,float,less<string>,allocator<pair<const string,float> > >,less<string>,allocator<pair<const string,map<string,float,less<string>,allocator<pair<const string,float> > > > > >::operator[]((char*)0x8464444) in current scope maplink.C:31:
 Possible candidates are...
 (in map<string,map<string,float,less<string>,allocator<pair<const string,float> > >,less<string>,allocator<pair<const string,map<string,float,less<string>,allocator<pair<const string,float> > > > > >)
Error: improper lvalue maplink.C:31:
 (const double)1.00000000000000000e+00
 *** Interpreter error recovered ***

 //--AZ: the line number in above message is clearly wrong!
*/

#include <iostream>
#include <map>

using std::cout;    using std::endl;

void maplink()
{
   std::map<std::string, float> map_float;

   map_float["a"] = 1.;
   map_float["b"] = 2.;
   map_float["c"] = 3.;

   for (std::map<std::string, float>::const_iterator
         it = map_float.begin(); it != map_float.end(); ++it)
   {
      cout<< it->first <<": " << it->second <<endl;
   }

   std::map<std::string, std::map<std::string, float> > map_map;
   map_map["a1"]["a2"] = 1.;
   map_map["a1"]["a22"] = 11.;
   map_map["b1"]["b2"] = 2.;
   map_map["b1"]["b22"] = 22.;
   map_map["c1"]["c2"] = 3.;
   map_map["c1"]["c22"] = 33.;

   for (std::map<std::string, std::map<std::string, float> >::const_iterator
         i_mapmap = map_map.begin(); i_mapmap != map_map.end(); ++i_mapmap)
   {
      cout<< i_mapmap->first <<endl;
      for (std::map<std::string,float>::const_iterator
            i_string_float = i_mapmap->second.begin(); i_string_float != i_mapmap->second.end(); ++i_string_float)
      {
         cout<< "\t" << i_string_float->first << ": " << i_string_float->second <<endl;
      }
   }
}
