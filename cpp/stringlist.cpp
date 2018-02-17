#include <list>
#include <string>
#include <iostream>
#include <fstream>

using std::cout;      using std::endl;

class StringList {
  std::list<std::string> list_;
  std::list<std::string>::iterator curr_;
public:
  StringList() {
    curr_ = list_.end();
  }
  StringList(std::istream& ifile)
  {
    std::string line;
    while (std::getline(ifile,line))  // NB: global function std::getline(istream& is, string& str);
    {
      list_.push_back(line);
    }
    curr_ = list_.begin();
  }
  const std::string* Find(const std::string& string, std::size_t pos=0) {
    for (std::list<std::string>::iterator i_str=list_.begin(); i_str!=list_.end(); ++i_str)
    {
      if (i_str->find(string, pos) != std::string::npos) {
        return &(*i_str);
      }
    }
  }
};

main()
{
  const char ifname[] = "/home/zatserkl/pos_prod/TriDAS/pixel/PixelCalibrations/data/pixelTemperatureCalibrationData-prod.xml-2007_12_05-06_58_16-calib_-15C-6.xml";
  
  std::ifstream ifile(ifname);
  if (!ifile.is_open()) {
    cout<< "file not found: " << ifname <<endl;
    return 0;   // exception
  }
  
  StringList strlist(ifile);
  
  //-- infinite loop!
  
//   const std::string* str;
//   while (str = strlist.Find("<year>")) {
//     cout<< *str <<endl;
//   }
}


