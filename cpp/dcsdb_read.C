#include <map>
#include <string>
#include <iostream>
#include <fstream>

using std::cout;     using std::endl;

typedef std::pair<std::string, std::string> NameAlias;
typedef std::map<std::string, float> DateValueMap;
typedef std::map<NameAlias, DateValueMap> NameAlias_DateValueMap;

void dcsdb_read(const char ifname[]="dcsdb-2008.dat")
{
   std::fstream ifile(ifname);
   if (!ifile) {
      cout<< "File not found: " << ifname <<endl;
      return;
   }

   NameAlias_DateValueMap nameAlias_dateValue;

   std::string name, alias, date1, date2;
   float value;

   int nrecords = 0;
   while (ifile >> name >> alias >> date1 >> date2 >> value) {
      std::string date = date1 + " " + date2;
      nameAlias_dateValue[NameAlias(name,alias)][date] = value;
      ++nrecords;
      if (nrecords == 3) break;
   }
   ifile.close();

   cout<< "Processed " << nrecords << " records" <<endl;

   for (NameAlias_DateValueMap::const_iterator
         i_map=nameAlias_dateValue.begin(); i_map!=nameAlias_dateValue.end(); ++i_map)
   {
      const NameAlias& nameAlias = i_map->first;
      const DateValueMap& dateValueMap = i_map->second;
      cout<< nameAlias.first <<"\n"<< nameAlias.second <<endl;
      for (DateValueMap::const_iterator
            i_dateValue=dateValueMap.begin(); i_dateValue!=dateValueMap.end(); ++i_dateValue)
      {
         cout<< i_dateValue->first <<"\t "<< i_dateValue->second <<endl;
      }
      cout<<endl;
   }
}

#if !defined(__CINT__)
// #ifndef __CINT__
main(int argc, char* argv[])
{
   dcsdb_read();
}
#endif
