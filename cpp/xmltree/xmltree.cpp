/*
rootcint -f xmltree_dict.cxx -c xmltree.h xmltree_linkdef.h
g++ `$ROOTSYS/bin/root-config --cflags --glibs` -o xmltree xmltree.cpp xmltree_dict.cxx

.L xmltree.h
TFile *_file0 = TFile::Open("cut.xml.root")

--> the same result:
pvss->Draw("RTD","d==1")
pvss->Draw("disk.RTD","d==1")
pvss->Draw("disk[0].RTD","")

*/

#include "xmltree.h"

#include <list>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <cstdarg>
#include <ctime>

#include <TRint.h>        // to compile standalone ROOT program
#include <TROOT.h>        // to use gPad, etc.

#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <TCanvas.h>

using std::cout;        using std::endl;

//
// class XMLDp
//

class XMLDp {
public:
  std::string name_;
  std::vector<float> vdata_;
  XMLDp() {}
  XMLDp(std::string name): name_(name) {}
  XMLDp(const XMLDp& xmlDp): name_(xmlDp.name_) {
    vdata_ = xmlDp.GetDataVector();
  }
  const std::string& GetName() const {return name_;}
  const std::vector<float>& GetDataVector() const {return vdata_;}
  void Pickup(std::list<std::string> text)
  {
    std::list<std::string>::iterator i_line = text.begin();
    while(i_line != text.end())
    {
      float val;
      if (Extract(*i_line, name_, val)) {
        vdata_.push_back(val);
        i_line = text.erase(i_line);    // iterator increament
        continue;
      }
      ++i_line;
    }
  }
  bool Extract(const std::string& line, const std::string& name, float& val)
  {
    val = 0;
    std::size_t pos = line.find(name);
    if (pos != std::string::npos)
    {
      std::size_t pos_ket = line.find(">", pos);
      std::size_t pos_bra = line.find("<", pos);
      std::size_t length = pos_bra - pos_ket - 1;
      std::string ch_val = line.substr(pos_ket+1, length);
      //cout<< "length = " << length << " ch_val = " << ch_val <<endl;
      std::stringstream ss;
      ss << ch_val;
      ss >> val;
      return true;
    }
    return false;
  }
};

//
// class XMLChannel
//

class XMLChannel {
public:
  std::string name_;
  std::string start_name_;
  std::string end_name_;
  std::string mode_;
  std::string portcard_curr_;	 // can be pointer to element of vector portcard_names_ as well
  std::vector<std::string> portcard_names_;
  std::map< std::string, std::vector<unsigned> > data_map_;
  int np_sec_;                    // the number of points per one read out section
  XMLChannel(std::string name): name_(name), np_sec_(0)
  {
    start_name_ = name_;
    start_name_.insert(0, "<");
    start_name_.append(">");
    end_name_ = name_;
    end_name_.insert(0, "</");
    end_name_.append(">");
    // fill possible portcard names
    // Pilot Run Detector
    portcard_names_.push_back("FPix_BmO_D1_PRT3");
    portcard_names_.push_back("FPix_BmO_D2_PRT3");
    // HC+Z1 == FPix_BpO
    portcard_names_.push_back("FPix_BpO_D1_PRT1");
    portcard_names_.push_back("FPix_BpO_D1_PRT2");
    portcard_names_.push_back("FPix_BpO_D1_PRT3");
    portcard_names_.push_back("FPix_BpO_D1_PRT4");
    portcard_names_.push_back("FPix_BpO_D2_PRT1");
    portcard_names_.push_back("FPix_BpO_D2_PRT2");
    portcard_names_.push_back("FPix_BpO_D2_PRT3");
    portcard_names_.push_back("FPix_BpO_D2_PRT4");
    // HCxxx == FPix_BmI
    portcard_names_.push_back("FPix_BmI_D1_PRT1");
    portcard_names_.push_back("FPix_BmI_D1_PRT2");
    portcard_names_.push_back("FPix_BmI_D1_PRT3");
    portcard_names_.push_back("FPix_BmI_D1_PRT4");
    portcard_names_.push_back("FPix_BmI_D2_PRT1");
    portcard_names_.push_back("FPix_BmI_D2_PRT2");
    portcard_names_.push_back("FPix_BmI_D2_PRT3");
    portcard_names_.push_back("FPix_BmI_D2_PRT4");
    // HCxxx == FPix_BpI
    portcard_names_.push_back("FPix_BpI_D1_PRT1");
    portcard_names_.push_back("FPix_BpI_D1_PRT2");
    portcard_names_.push_back("FPix_BpI_D1_PRT3");
    portcard_names_.push_back("FPix_BpI_D1_PRT4");
    portcard_names_.push_back("FPix_BpI_D2_PRT1");
    portcard_names_.push_back("FPix_BpI_D2_PRT2");
    portcard_names_.push_back("FPix_BpI_D2_PRT3");
    portcard_names_.push_back("FPix_BpI_D2_PRT4");
    // HCxxx == FPix_BmO
    portcard_names_.push_back("FPix_BmO_D1_PRT1");
    portcard_names_.push_back("FPix_BmO_D1_PRT2");
    portcard_names_.push_back("FPix_BmO_D1_PRT3");
    portcard_names_.push_back("FPix_BmO_D1_PRT4");
    portcard_names_.push_back("FPix_BmO_D2_PRT1");
    portcard_names_.push_back("FPix_BmO_D2_PRT2");
    portcard_names_.push_back("FPix_BmO_D2_PRT3");
    portcard_names_.push_back("FPix_BmO_D2_PRT4");
  }
  const std::map< std::string, std::vector<unsigned> >& GetDataMap() const {return data_map_;}
  const std::string& GetName() const {return name_;}
  const std::string& GetMode() const {return mode_;}
  unsigned GetNpSection() const {return np_sec_;}
  void Print() const
  {
    cout<< "DCU channel " << name_ <<endl;
    for (std::map< std::string, std::vector<unsigned> >::const_iterator pcname_vdata=data_map_.begin(); 
         pcname_vdata!=data_map_.end(); ++pcname_vdata)
    {
      cout<< pcname_vdata->first <<endl;
      for (std::vector<unsigned>::const_iterator i_data=pcname_vdata->second.begin();
           i_data!=pcname_vdata->second.end(); ++i_data)
      {
        cout<< *i_data <<endl;
      }
    }
  }
  void Pickup(std::list<std::string> text)
  {
    bool found_end = true;
    
    std::list<std::string>::iterator i_line = text.begin();
    while(i_line != text.end())
    {
      //cout<< "XMLChannel::Pickup for " << name_ << ": processing line = " << *i_line <<endl;
      
      // <dataSet type="DCU" mode="LIR">
      if (i_line->find("<dataSet type=\"DCU\" mode=") != std::string::npos) {
        if (i_line->find("LIR") != std::string::npos) mode_ = "LIR";
        if (i_line->find("HIR") != std::string::npos) mode_ = "HIR";
        // do nothing with this line
      }
      
      // look if it's portcard name
      bool name_line = false;
      for (std::vector<std::string>::const_iterator i_name=portcard_names_.begin(); i_name!=portcard_names_.end(); ++i_name)
      {
        std::stringstream ss_start;
        ss_start << "<" << *i_name << ">";
        std::stringstream ss_end;
        ss_end << "</" << *i_name << ">";
        
        if (i_line->find(ss_start.str()) != std::string::npos) {  // start of current portcard
          portcard_curr_ = *i_name;
          name_line = true;
          break;
        }
        if (i_line->find(ss_end.str()) != std::string::npos) {    // end of current portcard
          portcard_curr_ = "";
          name_line = true;
          break;
        }
      }
      if (name_line) {
        ++i_line;
        continue;                         // we cannot remove line with portcard name because it needed for other channels
      }

      if (*i_line != start_name_) {       // require exect matching in case of channels
        ++i_line;
        continue;
      }
      
      //-- here we start taking data

      if (portcard_curr_ == "") cout<< "***WARNING XMLChannel::Pickup: channel " << name_ << ": missing portcard name!" <<endl;
      
      found_end = false;

      // cout<< "Channel " << name_ << ": picking up data for portcard_curr_ = " << portcard_curr_ <<endl;

      i_line = text.erase(i_line);                // remove <Vaa>
      
      int nDataPoints = 0;

      while (i_line != text.end())
      {
        const std::string line = *i_line;         // NB: const because this we call a ctor?
        //cout<< "Pickup: current line = " << line <<endl;
        i_line = text.erase(i_line);              // iterator increament

        if (line == end_name_) {
          found_end = true;                       // found </Vaa>
          break;
        }

        unsigned val;
        char bra;
        char ket;
        std::stringstream ss(line);
        ss >> bra >> val >> ket;
        if (ss.fail()) {
          cout<< "***ERROR XMLChannel::Pickup for channel " << name_ << " conversion error for " << line <<endl;
          return;
        }
        //cout<< "converted val = " << val <<endl;
        data_map_[portcard_curr_].push_back(val);
        ++nDataPoints;
      }
      // some analysis for this section
      if (nDataPoints == 0) {
        cout<< "***WARNING: XMLChannel::Pickup: for channel " << name_ << " portcard " << portcard_curr_ << " nDataPoints == 0" <<endl;
      }
      if (np_sec_ > 0) {
        if (nDataPoints != np_sec_) {
          cout<< "***WARNING: XMLChannel::Pickup: for channel " << name_ << " portcard " << portcard_curr_
            << " nDataPoints = " << nDataPoints << " is different from np_sec_ = " << np_sec_
          <<endl;
        }
      }
      else np_sec_ = nDataPoints;
    }
    if (!found_end) {
      cout<< "***ERROR XMLChannel::Pickup for channel " << name_ << " no terminal " << end_name_ <<endl;
    }
  }
};

//
// class XMLDate
//

class XMLDate {
  const std::string startTime_;
  const std::string endTime_;
  const std::string year_;
  const std::string month_;
  const std::string day_;
  const std::string hour_;
  const std::string min_;
  const std::string sec_;
  // std::time_t is time passed from 1/1/1970
  // struct std::tm is C time structure
  std::time_t time0_;
  std::time_t time_start_;
  std::time_t time_end_;
public:
  XMLDate(): time_start_(0), time_end_(0)
    , startTime_("startTime")
    , endTime_("endTime")
    , year_("year")
    , month_("month")
    , day_("day")
    , hour_("hour")
    , min_("minute")
    , sec_("second")
  {
    int year   = 2007;
    int mon    = 12;
    int day    = 3;
    int hour   = 0;
    int min    = 0;
    int sec    = 0;
    
    struct std::tm timeinfo;
    timeinfo.tm_year  = year - 1900;
    timeinfo.tm_mon   = mon - 1;
    timeinfo.tm_mday  = day;
    timeinfo.tm_hour  = hour;
    timeinfo.tm_min   = min;
    timeinfo.tm_sec   = sec;
    time0_ = std::mktime(&timeinfo);
  }
  void SetT0(const std::string& t0)
  {
    int year   = 2007;
    int mon    = 1;
    int day    = 1;
    int hour   = 0;
    int min    = 0;
    int sec    = 0;
    std::stringstream ss(t0);
    ss >> day >> mon >> year;
    
    struct std::tm timeinfo;
    timeinfo.tm_year  = year - 1900;
    timeinfo.tm_mon   = mon - 1;
    timeinfo.tm_mday  = day;
    timeinfo.tm_hour  = hour;
    timeinfo.tm_min   = min;
    timeinfo.tm_sec   = sec;
    time0_ = std::mktime(&timeinfo);
  }
  int GetStartTime() const {return time_start_;}
  int GetEndTime() const {return time_end_;}
  void FindTimes(std::list<std::string> text) {
    time_start_ = Time(startTime_, text) - time0_;
    time_end_ = Time(endTime_, text) - time0_;
  }
protected:
  int GetDateFild(std::string line, std::string field)
  {
    std::size_t pos;
    std::string str;
    std::stringstream ss;
    
    str = std::string("<") + field + std::string(">");
    pos = line.find(str);
    line.erase(0, pos+str.size());
    str = std::string("</") + field + std::string(">");
    pos = line.find(str);
    line.erase(pos);
    //cout<< "XMLDate::GetDateFild: current line: " << line <<endl;
    ss.str("");
    ss << line;
    int res;
    ss >> res;
    return res;
  }
  std::time_t Time(const std::string& time_section, std::list<std::string> text)
  {
    //cout<< "XMLDate::Time for " << time_section <<endl;
    
    std::list<std::string>::iterator i_line;
    for (i_line=text.begin(); i_line!=text.end(); ++i_line) {
      if (i_line->find(std::string("<") + std::string(time_section)) != std::string::npos) break;
    }
    if (i_line == text.end()) return -1;
    
    i_line = text.erase(i_line);    // iterator increament
    
    struct std::tm timeinfo;
    
    //cout<< "current line: " << *i_line <<endl;
    timeinfo.tm_year = GetDateFild(*i_line, year_) - 1900;
    i_line = text.erase(i_line);
    timeinfo.tm_mon = GetDateFild(*i_line, month_) - 1;
    i_line = text.erase(i_line);
    timeinfo.tm_mday = GetDateFild(*i_line, day_);
    i_line = text.erase(i_line);
    timeinfo.tm_hour = GetDateFild(*i_line, hour_);
    i_line = text.erase(i_line);
    timeinfo.tm_min = GetDateFild(*i_line, min_);
    i_line = text.erase(i_line);
    timeinfo.tm_sec = GetDateFild(*i_line, sec_);
    i_line = text.erase(i_line);
    // erase closing line like </startTime>
    i_line = text.erase(i_line);
    
    cout<< "XMLDate::Time year = " << timeinfo.tm_year+1900 << " mon = " << timeinfo.tm_mon+1 << " day = " << timeinfo.tm_mday << " hour = " << timeinfo.tm_hour << " min = " << timeinfo.tm_min << " sec = " << timeinfo.tm_sec <<endl;
    
    return std::mktime(&timeinfo);
  }
};

//
// class XMLReader
//

class XMLReader {
public:
  std::ifstream ifile_;
  const std::string comm_start_;
  const std::string comm_end_;
  std::list<std::string> list_noblank_;
  std::list<std::string> list_nocomm_;
  XMLDate xmlDate;
  std::vector<XMLChannel>       vchan_;
  std::map<std::string, XMLDp>  dp_map_;
  
  XMLReader(std::ifstream& ifile, const std::string& t0="1 12 2007"):
      comm_start_("<!--")
    , comm_end_("-->")
  {
    // write xml lines into list ignoring blank lines and leading/trailing spaces (why? -- historically)
    std::string line;
    while (std::getline(ifile,line))  // NB: global function std::getline(istream& is, string& str);
    {
      const std::string whitespace = " \t\n\r";
      // trim leading whitespace
      std::string::size_type notwhite = line.find_first_not_of(whitespace);
      line.erase(0,notwhite);

      // trim trailing whitespace
      notwhite = line.find_last_not_of(whitespace);
      line.erase(notwhite+1);
      
      if (line.size() > 0) list_noblank_.push_back(line);
    }
    //     for (std::list<std::string>::const_iterator i_str=list_noblank_.begin(); i_str!=list_noblank_.end(); ++i_str)
    //     {
    //       cout<< *i_str <<endl;
    //     }
    //     cout<< "blanks lines and leading/trailing spaces are discarded\n" <<endl;

    //-- time
    xmlDate.SetT0(t0);
    cout<< "XMLReader::XMLReader: time0 = " << t0 <<endl;
    
    //-- DCU channels: order matters! E.g. vchan_[0] is Vaa, vchan_[1] is Vdd, etc.
    vchan_.push_back(XMLChannel("Vaa"));
    vchan_.push_back(XMLChannel("Vdd"));
    vchan_.push_back(XMLChannel("RTD2"));
    vchan_.push_back(XMLChannel("RTD3"));
    vchan_.push_back(XMLChannel("AOH"));
    vchan_.push_back(XMLChannel("Vpc"));
    vchan_.push_back(XMLChannel("Vbg"));
    vchan_.push_back(XMLChannel("TS"));
    
    std::string dpname;
    dpname = "Portcards_D1_LV_iMon";  dp_map_[dpname] = XMLDp(dpname);
    dpname = "Portcards_D1_LV_vMon";  dp_map_[dpname] = XMLDp(dpname);
    dpname = "Portcards_D2_LV_iMon";  dp_map_[dpname] = XMLDp(dpname);
    dpname = "Portcards_D2_LV_vMon";  dp_map_[dpname] = XMLDp(dpname);
    dpname = "CCU_LV_iMon";           dp_map_[dpname] = XMLDp(dpname);
    dpname = "CCU_LV_vMon";           dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.1_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.1_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.1_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.1_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.2_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.2_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.2_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.2_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.3_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.3_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.3_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.3_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.4_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig1.4_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.4_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana1.4_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.1_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.1_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.1_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.1_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.2_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.2_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.2_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.2_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.3_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.3_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.3_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.3_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.4_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Dig2.4_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.4_LV_iMon";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "Ana2.4_LV_vMon";        dp_map_[dpname] = XMLDp(dpname);
    
    //-- SIEMENS

//     dpname = "HC+Z1_Detector_D1_BLD1_PNL1";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD1_PNL2";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD6_PNL1";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD6_PNL2";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD7_PNL1";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD7_PNL2";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD12_PNL1";       dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D1_BLD12_PNL2";       dp_map_[dpname] = XMLDp(dpname);
//     
//     dpname = "HC+Z1_Detector_D2_BLD1_PNL1";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD1_PNL2";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD6_PNL1";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD6_PNL2";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD7_PNL1";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD7_PNL2";        dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD12_PNL1";       dp_map_[dpname] = XMLDp(dpname);
//     dpname = "HC+Z1_Detector_D2_BLD12_PNL2";       dp_map_[dpname] = XMLDp(dpname);
    
    dpname = "_Detector_D1_BLD1_PNL1";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD1_PNL2";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD6_PNL1";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD6_PNL2";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD7_PNL1";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD7_PNL2";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD12_PNL1";       dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D1_BLD12_PNL2";       dp_map_[dpname] = XMLDp(dpname);
    
    dpname = "_Detector_D2_BLD1_PNL1";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD1_PNL2";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD6_PNL1";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD6_PNL2";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD7_PNL1";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD7_PNL2";        dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD12_PNL1";       dp_map_[dpname] = XMLDp(dpname);
    dpname = "_Detector_D2_BLD12_PNL2";       dp_map_[dpname] = XMLDp(dpname);
    
    // Half-cylinder Air RTD
    dpname = "_Detector_Air";                 dp_map_[dpname] = XMLDp(dpname);
    
    FilterComments(list_noblank_, list_nocomm_);
    RemoveLastDacSettings();
  }
  
  const XMLChannel& GetVaa()  const {return vchan_.at(0);}
  const XMLChannel& GetVdd()  const {return vchan_.at(1);}
  const XMLChannel& GetRTD2() const {return vchan_.at(2);}
  const XMLChannel& GetRTD3() const {return vchan_.at(3);}
  const XMLChannel& GetAOH()  const {return vchan_.at(4);}
  const XMLChannel& GetVpc()  const {return vchan_.at(5);}
  const XMLChannel& GetVbg()  const {return vchan_.at(6);}
  const XMLChannel& GetTS()   const {return vchan_.at(7);}
  const std::vector<XMLChannel>& GetDataVector() const {return vchan_;}
  const std::map<std::string, XMLDp>& GetDpMap() const {return dp_map_;}
  
  void FilterComments(std::list<std::string>& lin, std::list<std::string>& lout)
  {
    // version 0:
    //
    // comments should not be part of quoted text like <name>"abc_<!--_xyz"</name>
    // also: no enclosed comments
    // no more than one comment in the line (including comment after end of comment started in some previous line)

    bool comment = false;
    std::list<std::string>::iterator i_line = lin.begin();
    while (i_line != lin.end())
    {
      const std::string line = *i_line;   // NB: const because this we call a ctor
      //cout<< "XMLReader::FilterComments: line = " << line <<endl;
      i_line = lin.erase(i_line);         // iterator increament
      //cout<< line <<endl;
      if (!comment)
      {
        // look for start-of-comment
        std::string::size_type pos = line.find(comm_start_);
        if (pos == std::string::npos) {
          //cout<< comm_start_ << " is not found" <<endl;
          lout.push_back(line);
        }
        else {
          cout<< "//-- XMLReader::FilterComments: " << comm_start_ << " is found. pos = " << pos <<endl;
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
          if (buf.size() > 0) lout.push_back(buf);
        }
      }
      else
      {
        // look for end-of-comment sign in the current line
        std::string::size_type pos = line.find(comm_end_);
        if (pos != std::string::npos)
        {
          // do not expect more than one comment in one line
          comment = false;
        }
      }
    }
  }
  
  void RemoveLastDacSettings()
  {
    // removes ~30K lines of LastDAC settings

    std::string daqSettings_start = "<dacSettings>";
    std::string daqSettings_end   = "</dacSettings>";

    std::list<std::string>::iterator start = find(list_nocomm_.begin(), list_nocomm_.end(), daqSettings_start);
    std::list<std::string>::iterator end   = find(list_nocomm_.begin(), list_nocomm_.end(), daqSettings_end);
    //cout<< "*start = " << *start << " *end = " << *end <<endl;
    if (start != list_nocomm_.end() && end != list_nocomm_.end()) {
      unsigned nlines = std::distance(start, end) + 1;
      cout<< "XMLReader::RemoveLastDacSettings: removing " << nlines << " lines with dac settings" <<endl;
      list_nocomm_.erase(start, end);
    }
    else {
      cout<< "***WARNING XMLReader::RemoveLastDacSettings: could not remove dacSettings:";
      if (start == list_nocomm_.end()) cout<< " start line " << daqSettings_start << " is not found";
      if (end   == list_nocomm_.end()) cout<< " end line " << daqSettings_end << " is not found";
      cout<<endl;
    }
  }
  
  void GetData()
  {
    // cout<< "XMLReader::GetData" <<endl;
    
    xmlDate.FindTimes(list_nocomm_);
    // cout<< "xmlDate.GetStartTime() = " << xmlDate.GetStartTime() << " xmlDate.GetEndTime() = " << xmlDate.GetEndTime() << " diff = " << xmlDate.GetEndTime() - xmlDate.GetStartTime() <<endl;
    
    for (std::vector<XMLChannel>::iterator i_vchan=vchan_.begin(); i_vchan!=vchan_.end(); ++i_vchan)
    {
      cout<< "XMLReader::GetData: run channel " << i_vchan->GetName() <<endl;
      i_vchan->Pickup(list_nocomm_);
      // cout<< "    i_vchan->GetDataMap().begin()->size() = " << i_vchan->GetDataMap().begin()->second.size() <<endl;
    }
    
    for (std::map<std::string, XMLDp>::iterator i_dp=dp_map_.begin(); i_dp!=dp_map_.end(); ++i_dp)
    {
      i_dp->second.Pickup(list_nocomm_);
      // cout<< "dp name " << i_dp->second.GetName() << " size = " << i_dp->second.GetDataVector().size() <<endl;
      // cout<< "dp name " << i_dp->second.GetName() << " size = " << i_dp->second.GetDataVector().size() << " first element = " << (i_dp->second.GetDataVector().size()? i_dp->second.GetDataVector().at(0): 0) <<endl;
    }
  }
};

ClassImp(LV);
ClassImp(Disk);
ClassImp(HCyl);
ClassImp(DCU);
ClassImp(DiskDCU);
ClassImp(HCylDCU);

/////////////////////////////////////////////
//
//                main
//
/////////////////////////////////////////////

main(int argc, char* argv[])
{
  //for (int i=0; i<argc; ++i) cout<< i << "\t " << argv[i] <<endl;

  if (argc < 2) {
    cout<< "Usage: " << argv[0] << " ifname << [time0=\"1 12 2007\"] [-b]" <<endl;
    return 0;
  }

  std::string ifname = argv[1];
  
  std::ifstream ifile(ifname.c_str());
  if (!ifile.is_open()) {
    cout<< "file not found: " << ifname <<endl;
    return 0;   // exception
  }
  cout<< "\nProcessing file = " << ifname <<endl;
  
  // std::string t0 = "3 12 2007";
  std::string t0 = "15 1 2008";
  if (argc > 2) t0 = argv[2];
  
  bool batch = false;
  std::string batch_str;
  if (argc > 3) batch_str = argv[3];
  if (batch_str == "-b") batch = true;
    
  XMLReader* xmlReader = new XMLReader(ifile, t0);

  xmlReader->GetData();
  
  // cout<< "xmlReader->GetDataVector().size() = " << xmlReader->GetDataVector().size() <<endl;

  //
  // strip path from filename
  //
  std::string filename;
  // find end of pathname if any
  std::size_t pos = ifname.rfind("/");
  if (pos != std::string::npos) filename = ifname.substr(pos+1);
  else filename = ifname;
  
  argc = 1;
  TRint* theApp = new TRint("Rint", &argc, argv, 0, 0, 1);  // do not show splash screen and print ROOT version
  //TRint* theApp = new TRint("Rint");

  // ROOT file
  TFile* oroot = TFile::Open(Form("%s.root",filename.c_str()), "recreate");
  
  // XDAQ tree
  
  HCylDCU* hcylDCU = new HCylDCU();
  TTree* treeXDAQ = new TTree("xdaq","DCU readout for production module");
  treeXDAQ->Branch("xdaq", "HCylDCU", &hcylDCU);
  // colors
  treeXDAQ->SetMarkerStyle(6);
  int colorXDAQ = 2;
  treeXDAQ->SetMarkerColor(colorXDAQ);
  treeXDAQ->SetLineColor(colorXDAQ);
  
  // PVSS tree
  HCyl* hcyl = new HCyl();
  TTree* treePVSS = new TTree("pvss","PVSS readout for production module");
  treePVSS->Branch("pvss", "HCyl", &hcyl);
  // colors
  treePVSS->SetMarkerStyle(6);
  int colorPVSS = 2;
  treePVSS->SetMarkerColor(colorPVSS);
  treePVSS->SetLineColor(colorPVSS);
  
  std::vector<std::string> pcard_names;
  for (std::map<std::string, std::vector<unsigned> >::const_iterator it=xmlReader->GetDataVector().at(0).GetDataMap().begin();
       it!=xmlReader->GetDataVector().at(0).GetDataMap().end(); ++it)
  {
    pcard_names.push_back(it->first);
    //cout<< "portcard it->first = " << it->first <<endl;
  }
  
  // time
  Int_t t_start = xmlReader->xmlDate.GetStartTime();
  Int_t dt_tot = xmlReader->xmlDate.GetEndTime() - xmlReader->xmlDate.GetStartTime();
  
  //-- fill DCU tree
  
  // how many points for DCU readout?
  Int_t npDCU = xmlReader->GetDataVector().at(0).GetDataMap().begin()->second.size();
  // cout<< "xmlReader->GetDataVector().at(0).GetDataMap().begin()->second.size() = " << npDCU <<endl;
  cout<< "npDCU = " << npDCU <<endl;
  
  Float_t dtDCU = Float_t(dt_tot) / Float_t(npDCU);
  if (xmlReader->xmlDate.GetEndTime() < 0) {
    dtDCU = 2.2;   // from experience
    cout<< "--> No endTime information. Using dtDCU = " << dtDCU <<endl;
  }
  cout<< "dtDCU = " << dtDCU <<endl;
  
  Int_t modeLIR = 0;
  Int_t modeHIR = 0;
  if (xmlReader->GetDataVector().at(0).GetMode() == "LIR") modeLIR = 1;
  if (xmlReader->GetDataVector().at(0).GetMode() == "HIR") modeHIR = 1;

  for (unsigned ipoint=0; ipoint<npDCU; ++ipoint)
  {
    hcylDCU->clear();
    
    // time
    hcylDCU->t = t_start + ipoint*dtDCU;
    for (std::vector<std::string>::const_iterator i_name=pcard_names.begin(); i_name!=pcard_names.end(); ++i_name)
    {
      Int_t disk = 0;
      Int_t pc   = 0;
      // 0123456789*12345
      // FPix_BpO_D1_PRT1
      if (i_name->size() == 16) {
        disk = Int_t((*i_name)[10] - '0');
        pc   = Int_t((*i_name)[15] - '0');
      }
      if (ipoint == 0) {
        cout<< "port card " << *i_name << " disk = " << disk << " pc = " << pc <<endl;
      }
      
      // convert to indices
      Int_t idisk = disk - 1;
      Int_t ipc  = pc - 1;
      // get data for this portcard
      hcylDCU->disk[idisk].dcu[ipc].Vaa = xmlReader->GetVaa().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].Vdd = xmlReader->GetVdd().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].rtd2 = xmlReader->GetRTD2().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].rtd3 = xmlReader->GetRTD3().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].aoh = xmlReader->GetAOH().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].Vpc = xmlReader->GetVpc().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].Vbg = xmlReader->GetVbg().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].ts = xmlReader->GetTS().GetDataMap().find(*i_name)->second.at(ipoint);
      hcylDCU->disk[idisk].dcu[ipc].LIR = modeLIR;
      hcylDCU->disk[idisk].dcu[ipc].HIR = modeHIR;
      // T in degrees of Celsium
      hcylDCU->disk[idisk].dcu[ipc].Trtd2 = (2./3850e-6) * (1. - hcylDCU->disk[idisk].dcu[ipc].rtd2 / hcylDCU->disk[idisk].dcu[ipc].Vpc);
      hcylDCU->disk[idisk].dcu[ipc].Trtd3 = (2./3850e-6) * (1. - hcylDCU->disk[idisk].dcu[ipc].rtd3 / hcylDCU->disk[idisk].dcu[ipc].Vpc);
      hcylDCU->disk[idisk].dcu[ipc].Taoh  = (2./3850e-6) * (1. - hcylDCU->disk[idisk].dcu[ipc].aoh / hcylDCU->disk[idisk].dcu[ipc].Vpc);
      //-- cross-reference
      hcylDCU->disk[idisk].dcu[ipc].d = idisk;
      hcylDCU->disk[idisk].dcu[ipc].pc = ipc;
    }
    
    //--
    //-- hardcode pedestals
    //--
    // HC+Z1 (type FPix_BpO)
//     hcylDCU->disk[0].dcu[0].ped = 2;
//     hcylDCU->disk[0].dcu[1].ped = 12.99;
//     hcylDCU->disk[0].dcu[2].ped = 2.98676;
//     hcylDCU->disk[0].dcu[3].ped = 15.9809;
//     hcylDCU->disk[1].dcu[0].ped = 2.14142;
//     hcylDCU->disk[1].dcu[1].ped = 4.99951;
//     hcylDCU->disk[1].dcu[2].ped = 10.2792;
//     hcylDCU->disk[1].dcu[3].ped = 3.86078;
    
    treeXDAQ->Fill();
  }
  
  //-- fill PVSS tree
  
  // how many points for PVSS readout? Ask, to say, the first element
  Int_t npPVSS = xmlReader->GetDpMap().begin()->second.GetDataVector().size();
  cout<< "npPVSS = " << npPVSS <<endl;
  
  Float_t dtPVSS = Float_t(dt_tot) / Float_t(npPVSS);
  if (xmlReader->xmlDate.GetEndTime() < 0) {
    dtPVSS = 22.;   // from experience
    cout<< "--> No endTime information. Using dtPVSS = " << dtPVSS <<endl;
  }
  cout<< "dtPVSS = " << dtPVSS <<endl;
  
  for (unsigned ipoint=0; ipoint<npPVSS; ++ipoint)
  {
    hcyl->clear();
    
    hcyl->t = t_start + ipoint*dtPVSS;
    hcyl->ccu.i = xmlReader->GetDpMap().find("CCU_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->ccu.v = xmlReader->GetDpMap().find("CCU_LV_vMon")->second.GetDataVector().at(ipoint);
    
    if (xmlReader->GetDpMap().find("_Detector_Air") != xmlReader->GetDpMap().end()) {
      // the _Detector_Air has been mapped in xmlReader map
      const std::vector<float>& vchan = xmlReader->GetDpMap().find("_Detector_Air")->second.GetDataVector();
      if (vchan.size() > 0) hcyl->air = vchan.at(ipoint);
    }
    
    Int_t idisk;
    //
    // disk 1
    //
    idisk = 0;
    hcyl->disk[idisk].pcard.i = xmlReader->GetDpMap().find("Portcards_D1_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].pcard.v = xmlReader->GetDpMap().find("Portcards_D1_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[0].i = xmlReader->GetDpMap().find("Dig1.1_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[0].v = xmlReader->GetDpMap().find("Dig1.1_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[0].i = xmlReader->GetDpMap().find("Ana1.1_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[0].v = xmlReader->GetDpMap().find("Ana1.1_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[1].i = xmlReader->GetDpMap().find("Dig1.2_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[1].v = xmlReader->GetDpMap().find("Dig1.2_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[1].i = xmlReader->GetDpMap().find("Ana1.2_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[1].v = xmlReader->GetDpMap().find("Ana1.2_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[2].i = xmlReader->GetDpMap().find("Dig1.3_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[2].v = xmlReader->GetDpMap().find("Dig1.3_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[2].i = xmlReader->GetDpMap().find("Ana1.3_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[2].v = xmlReader->GetDpMap().find("Ana1.3_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[3].i = xmlReader->GetDpMap().find("Dig1.4_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[3].v = xmlReader->GetDpMap().find("Dig1.4_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[3].i = xmlReader->GetDpMap().find("Ana1.4_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[3].v = xmlReader->GetDpMap().find("Ana1.4_LV_vMon")->second.GetDataVector().at(ipoint);

    // hardwired RTDs
    hcyl->disk[idisk].RTD[0] = xmlReader->GetDpMap().find("_Detector_D1_BLD1_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[1] = xmlReader->GetDpMap().find("_Detector_D1_BLD1_PNL2")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[2] = xmlReader->GetDpMap().find("_Detector_D1_BLD6_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[3] = xmlReader->GetDpMap().find("_Detector_D1_BLD6_PNL2")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[4] = xmlReader->GetDpMap().find("_Detector_D1_BLD7_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[5] = xmlReader->GetDpMap().find("_Detector_D1_BLD7_PNL2")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[6] = xmlReader->GetDpMap().find("_Detector_D1_BLD12_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[7] = xmlReader->GetDpMap().find("_Detector_D1_BLD12_PNL2")->second.GetDataVector().at(ipoint);

    //
    // disk 2
    //
    idisk = 1;
    hcyl->disk[idisk].pcard.i = xmlReader->GetDpMap().find("Portcards_D2_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].pcard.v = xmlReader->GetDpMap().find("Portcards_D2_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[0].i = xmlReader->GetDpMap().find("Dig2.1_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[0].v = xmlReader->GetDpMap().find("Dig2.1_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[0].i = xmlReader->GetDpMap().find("Ana2.1_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[0].v = xmlReader->GetDpMap().find("Ana2.1_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[1].i = xmlReader->GetDpMap().find("Dig2.2_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[1].v = xmlReader->GetDpMap().find("Dig2.2_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[1].i = xmlReader->GetDpMap().find("Ana2.2_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[1].v = xmlReader->GetDpMap().find("Ana2.2_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[2].i = xmlReader->GetDpMap().find("Dig2.3_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[2].v = xmlReader->GetDpMap().find("Dig2.3_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[2].i = xmlReader->GetDpMap().find("Ana2.3_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[2].v = xmlReader->GetDpMap().find("Ana2.3_LV_vMon")->second.GetDataVector().at(ipoint);
    
    hcyl->disk[idisk].dig[3].i = xmlReader->GetDpMap().find("Dig2.4_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].dig[3].v = xmlReader->GetDpMap().find("Dig2.4_LV_vMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[3].i = xmlReader->GetDpMap().find("Ana2.4_LV_iMon")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].ana[3].v = xmlReader->GetDpMap().find("Ana2.4_LV_vMon")->second.GetDataVector().at(ipoint);

    // hardwired RTDs
    hcyl->disk[idisk].RTD[0] = xmlReader->GetDpMap().find("_Detector_D2_BLD1_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[1] = xmlReader->GetDpMap().find("_Detector_D2_BLD1_PNL2")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[2] = xmlReader->GetDpMap().find("_Detector_D2_BLD6_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[3] = xmlReader->GetDpMap().find("_Detector_D2_BLD6_PNL2")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[4] = xmlReader->GetDpMap().find("_Detector_D2_BLD7_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[5] = xmlReader->GetDpMap().find("_Detector_D2_BLD7_PNL2")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[6] = xmlReader->GetDpMap().find("_Detector_D2_BLD12_PNL1")->second.GetDataVector().at(ipoint);
    hcyl->disk[idisk].RTD[7] = xmlReader->GetDpMap().find("_Detector_D2_BLD12_PNL2")->second.GetDataVector().at(ipoint);
    
    treePVSS->Fill();
  }

  cout<< "writing trees in output file " << oroot->GetName() <<endl;
  oroot->Write();
  if (batch) oroot->Close();
  
  // work in command line mode
  if (!batch) theApp->Run();
  delete theApp;
}
