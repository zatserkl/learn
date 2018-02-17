#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <cstdarg>

using namespace std;

void xmlread(const char* xmlname="/home/zatserkl/pos_cvs/TriDAS/pixel/PixelCalibrations/data/pixelTemperatureCalibrationData.xml-2007_11_25-16_11_51-100points.xml")
{
  cout<< "xmlname = " << xmlname <<endl;

  ifstream ifile(xmlname);
  if (!ifile.is_open()) {
    cout<< "file not found: " << xmlname <<endl;
    return;
  }

  std::string line;
  while (ifile >> line) {
    cout<< line <<endl;
  }
}

class XMLComment {
public:
  bool string_;
};

class XMLReader {
public:
  //Comment comment_;
  ifstream ifile_;
  const std::string comm_start_;
  const std::string comm_end_;
  std::vector<std::string> v_noblank_;
  std::vector<std::string> v_nocomm_;
  XMLReader(const char* xmlname): ifile_(xmlname)
    , comm_start_("<!--")
    , comm_end_("-->")
  {
    if (!ifile_.is_open()) {
      cout<< "file not found: " << xmlname <<endl;
      return;  // exception
    }
    // write xml lines into vector ignoring blank lines and spaces inside lines
    std::string line;
    while (std::getline(ifile_,line))  // NB: global function std::getline(istream& is, string& str);
    {
      // rather complicated way to fill stringstream because of ROOT "features"
      // that would be
      // while (std::getline(ifile,line)) {
      //   std::stringstream ss(line);
      //   ...

      std::stringstream ss;
      ss.str("");
      ss << line;
      std::string str_concat;
      std::string str;
      while (ss >> str) str_concat += str;
      if (str_concat.size() > 0) v_noblank_.push_back(str_concat);
    }
    //     for (std::vector<std::string>::const_iterator i_str=v_noblank_.begin(); i_str!=v_noblank_.end(); ++i_str)
    //     {
    //       cout<< *i_str <<endl;
    //     }
    //     cout<< "blanks lines and spaces are discarded\n" <<endl;
  }
  void RunFilters() {
    FilterComments(v_noblank_, v_nocomm_);
    for (std::vector<std::string>::const_iterator i_str=v_nocomm_.begin(); i_str!=v_nocomm_.end(); ++i_str)
    {
      cout<< *i_str <<endl;
    }
  }
  void FilterComments(const std::vector<std::string>& vin, std::vector<std::string>& vout)
  {
    // version 0:
    // comments should not be part of quoted text like <name>"abc_<!--_xyz"</name>
    // also: no enclosed comments
    // no more than one comment in the line

    bool comment = false;
    for (std::vector<std::string>::const_iterator i_line=vin.begin(); i_line!=vin.end(); ++i_line)
    {
      const std::string& line = *i_line;
      //cout<< line <<endl;
      if (!comment)
      {
        // look for start-of-comment
        std::string::size_type pos = line.find(comm_start_);
        if (pos == std::string::npos) {
          //cout<< comm_start_ << " is not found" <<endl;
          vout.push_back(line);
        }
        else {
          //cout<< comm_start_ << " is found. pos = " << pos <<endl;
          comment = true;
          //cout<< "part of line before the comment: --" << line.substr(0, pos) << "--" <<endl;
          std::string buf = line.substr(0, pos);       // save part of line before the comment
          // look for end-of-comment in current line
          pos += comm_start_.size();                   // start of commented text
          // look for end-of-comment in current line
          pos = line.find(comm_end_, pos);
          if (pos != std::string::npos)
          {
            // comment ended in current string
            comment = false;
            buf += line.substr(pos+comm_end_.size());   // save part of line after the comment
          }
          if (buf.size() > 0) vout.push_back(buf);
        }
      }
      else
      {
        // look for end-of-comment sign in the current line
        std::string::size_type pos = line.find(comm_end_);
        // skip commented out lines
        if (pos+comm_end_.size() < line.size())
        {
          // comment ended in current string
          comment = false;
          std::string buf = line.substr(pos+comm_end_.size());    // save part of line after the comment
          if (buf.size() > 0) vout.push_back(buf);
        }
      }
    }
  }
  void GetData() {
    // standard names
    const std::string name_Vaa   = "Vaa";
    const std::string name_Vdd   = "Vdd";
    const std::string name_RTD2  = "RTD2";
    const std::string name_RTD3  = "RTD3";
    const std::string name_AOH   = "AOH";
    const std::string name_Vpc   = "Vpc";
    const std::string name_Vbg   = "Vbg";
    const std::string name_TS    = "TS";
    const std::string name_wrong = "";

    std::map<std::string, std::vector<unsigned> > chan_map;

    //std::vector<unsigned> vec;
    chan_map[name_Vaa];
  }
};

main(int argc, char* argv[])
{
  //const char[] xmlname = "/home/zatserkl/pos_cvs/TriDAS/pixel/PixelCalibrations/data/pixelTemperatureCalibrationData.xml-2007_11_25-16_11_51-100points.xml";
  const char xmlname[] = "test.xml";

  XMLReader* xmlReader;

//   if (argc > 1) {
//     //for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;
//     xmlname = argv[1];
//   }

  //cout<< "xmlname = " << xmlname <<endl;
    
  xmlReader = new XMLReader(xmlname);
  xmlReader->RunFilters();
}
