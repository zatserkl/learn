#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using std::cout;
using std::endl;

using std::map;
using std::pair;
using std::vector;

main()
{
  time_t seconds;

  seconds = time(0);
  cout<< "hours since January 1, 1970 " << seconds/3600 <<endl;

  int year   = 0;
  int month  = 0;
  int day    = 0;
  int hour   = 0;
  int min    = 0;       
  int sec    = 0;
  int sec100 = 0;       // hundredth of the seconds
  
  // NB: 
  // std::tm timeinfo0;
  // correct as well as
  // struct std::tm timeinfo0;
  //
  struct std::tm timeinfo;

  timeinfo.tm_year  = year - 1900;
  timeinfo.tm_mon   = month - 1;
  timeinfo.tm_mday  = day;
  timeinfo.tm_hour  = hour;
  timeinfo.tm_min   = min;
  timeinfo.tm_sec   = sec;

  std::stringstream ifname;
  ifname << "rawadc_voltage.dat";
  std::ifstream ifile(ifname.str().c_str());
  if (!ifile) {
    cout<< "File not found: " << ifname.str().c_str() <<endl;
    return 0;
  }

  // map structure: <name, alias> --- vector of <date, ADC>
  typedef map<pair<std::string, std::string>, vector<pair<std::string, int> > > Map_NameAlias_DateValue;
  Map_NameAlias_DateValue mapVpc;

  std::string dpname;
  std::string alias;
  std::string date_yyyymmdd;
  std::string date_hhmmss;
  int adc;
  //double vcalib;

  std::string line;
  while (getline(ifile, line))  // NB: global function getline(istream& is, std::string& str);
  {
    //cout<< line <<endl;
    const std::string pattern = "_dcuChannelVPC";
    if (line.find(pattern, 0) != std::string::npos) {
      //cout<< line <<endl;
      dpname = line;
      ifile >> alias;
      ifile >> date_yyyymmdd >> date_hhmmss;
      ifile >> adc;
      // insert this info in the map
      const std::string realdata = "2008.10.10 00:00:00";     //-- first real data started from 2008.10.11 13:22:38
      std::string date = date_yyyymmdd + " " + date_hhmmss;
      if (date > realdata) {
        pair<std::string, std::string> dpname_alias(dpname, alias);
        pair<std::string, int> date_adc(date, adc);
        mapVpc[dpname_alias].push_back(date_adc);
      }
    }
  }

  for (Map_NameAlias_DateValue::iterator it=mapVpc.begin(); it!=mapVpc.end(); ++it)
  {
    // cout<< it->first.first << " " << it->second.at(0).second <<endl;
    // cout<< it->first.first << " " << it->second.at(0).first <<endl;
    // cout<< it->first.first << " size = " << it->second.size() <<endl;
    cout<< std::distance(mapVpc.begin(),it) << "\t " << it->first.first << " size = " << it->second.size() <<endl;
  }
}
