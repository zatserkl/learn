/*
g++ -o changeSIEMENS changeSIEMENS.cpp
*/
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdarg>

using std::cout;      using std::endl;

std::map<std::string, std::pair<std::string,std::string> > make_map()
{
  // map: SIEMENS channel and two names: wrong and correct
  
  std::map<std::string, std::pair<std::string,std::string> > map;
  std::string key;
  
  key = "SIEMENS/cms_Pixel_rail01_module05_channel000.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD1_PNL6"), std::string("HC+Z1_Detector_D1_BLD6_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel001.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD1_PNL6"), std::string("HC+Z1_Detector_D1_BLD6_PNL2"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel002.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD1_PNL1"), std::string("HC+Z1_Detector_D1_BLD1_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel003.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD1_PNL1"), std::string("HC+Z1_Detector_D1_BLD1_PNL2"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel004.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD2_PNL6"), std::string("HC+Z1_Detector_D2_BLD6_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel005.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD2_PNL6"), std::string("HC+Z1_Detector_D2_BLD6_PNL2"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel006.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD2_PNL1"), std::string("HC+Z1_Detector_D2_BLD1_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module05_channel007.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD2_PNL1"), std::string("HC+Z1_Detector_D2_BLD1_PNL2"));
  
  key = "SIEMENS/cms_Pixel_rail01_module07_channel000.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD1_PNL7"), std::string("HC+Z1_Detector_D1_BLD12_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel001.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD2_PNL7"), std::string("HC+Z1_Detector_D1_BLD12_PNL2"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel002.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD1_PNL12"), std::string("HC+Z1_Detector_D1_BLD7_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel003.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D1_BLD2_PNL12"), std::string("HC+Z1_Detector_D1_BLD7_PNL2"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel004.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD1_PNL7"), std::string("HC+Z1_Detector_D2_BLD12_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel005.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD2_PNL7"), std::string("HC+Z1_Detector_D2_BLD12_PNL2"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel006.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD1_PNL12"), std::string("HC+Z1_Detector_D2_BLD7_PNL1"));
  key = "SIEMENS/cms_Pixel_rail01_module07_channel007.readings.calibratedTemperature";
  map[key] = std::pair<std::string, std::string>(std::string("HC+Z1_Detector_D2_BLD2_PNL12"), std::string("HC+Z1_Detector_D2_BLD7_PNL2"));
  
  return map;
}

main(int argc, char* argv[])
{
  for (int i=0; i<argc; ++i) cout<< i << "\t " << argv[i] <<endl;
  
  if (argc < 2) {
    cout<< "Usage: " << argv[0] << " ifname" <<endl;
    return 0;
  }

  std::string ifname = argv[1];

  //
  // strip path from filename
  //
  std::string filename;
  // find end of pathname if any
  std::size_t pos = ifname.rfind("/");
  if (pos != std::string::npos) filename = ifname.substr(pos+1);
  else filename = ifname;

  std::string ofname = filename + "-corr.xml";
  
  cout<< "ofname = " << ofname <<endl;
  
  std::ifstream ifile(ifname.c_str());
  if (!ifile.is_open()) {
    cout<< "file not found: " << ifname <<endl;
    return 0;
  }
  
  std::ofstream ofile(ofname.c_str());
  
  std::map<std::string, std::pair<std::string,std::string> > map = make_map();
  
  for (std::map<std::string, std::pair<std::string,std::string> >::const_iterator i_map = map.begin();
    i_map != map.end(); ++i_map)
  {
    cout<< "for " << i_map->first << " " << i_map->second.first << " --> " << i_map->second.second <<endl;
  }
  
  int nsubstitutions = 0;
  
  std::string line;
  while (std::getline(ifile,line))  // NB: global function std::getline(istream& is, string& str);
  {
    if (line.find("<dist_1:SIEMENS/cms_Pixel") != std::string::npos)
    {
      // find map key
      for (std::map<std::string, std::pair<std::string,std::string> >::const_iterator i_map=map.begin(); i_map!=map.end(); ++i_map)
      {
        if (line.find(i_map->first) != std::string::npos) {
          std::size_t pos = line.find(i_map->second.first);
          if (pos != std::string::npos) {
            line.replace(pos, i_map->second.first.size(), i_map->second.second);
            ++nsubstitutions;
          }
          else {
            cout<< "***ERROR: line " << line << " should contain " << i_map->second.first << "!" <<endl;
            return 0;
          }
        }
      }
    }
    ofile << line << endl;
  }
  cout<< "done " << nsubstitutions << " substitutions" <<endl;
  
  ifile.close();
  ofile.close();
}
