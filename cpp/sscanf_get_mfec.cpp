#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

using std::cout;      using std::endl;

int get_mfec(const std::string& name) {
   int number = -1;
   unsigned pos = name.find("mfec");
   if (pos != std::string::npos) {
      sscanf(name.substr(pos).c_str(), "mfec%d", &number);
   }
   return number;
}

int get_number(const std::string& name, const std::string& pattern)
{
   // cms_pix_dcs_01:XDAQ/cms_Pixel_trkfecBoard01_mfec05_ccu123_ccuChannel00_dcuChannelAOH
   // int mfec = get_number(name, "mfec")
   int number = -1;
   unsigned pos = name.find(pattern);
   if (pos != std::string::npos) {
      sscanf(name.substr(pos+pattern.size()).c_str(), "%d", &number);
   }
   return number;
}

std::string get_portcardName(const std::string& alias)
{
  // CMS_Pixel/Endcap/BmO/D1/ROG4/Portcard/Temperature_RAWADC/AOH
  // FPix_BmO_D1_PRT1
  char endcap[] = "CMS_Pixel/Endcap";
  char hc[] = "BmO";
  char disk[] = "D1";
  char rog[] = "ROG";
  unsigned irog = 0;
  if (alias.find(endcap) != 0) return "";

  sscanf(alias.c_str(),"%16s/%3s/%2s/%3s%d", endcap, hc, disk, rog, &irog);

  std::ostringstream portcardName;
  portcardName.str("");             // to be sure with ROOT
  portcardName << "FPix" << "_" << hc << "_" << disk << "_" << rog << irog;

  return portcardName.str();
}

main()
{
  std::string name = "cms_pix_dcs_01:XDAQ/cms_Pixel_trkfecBoard01_mfec05_ccu123_ccuChannel00_dcuChannelAOH";
  // std::string name = "cms_pix_dcs_01:XDAQ/cms_Pixel_trkfecBoard01_mfec09_ccu123_ccuChannel00_dcuChannelAOH";

  cout<< "mfec = " << get_mfec(name) <<endl;
  cout<< "mfec = " << get_number(name, "mfec") <<endl;
  cout<< "ccu = " << get_number(name, "ccu") <<endl;
  cout<< "ccuChannel = " << get_number(name, "ccuChannel") <<endl;

  std::string alias = "CMS_Pixel/Endcap/BmO/D1/ROG4/Portcard/Temperature_RAWADC/AOH";
  cout<< "portcardName = " << get_portcardName(alias) <<endl;
}
