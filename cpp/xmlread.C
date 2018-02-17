#include <list>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <cstdarg>

using std::cout;        using std::endl;

void xmlread(const char* xmlname="/home/zatserkl/pos_cvs/TriDAS/pixel/PixelCalibrations/data/pixelTemperatureCalibrationData.xml-2007_11_25-16_11_51-100points.xml")
{
  cout<< "xmlname = " << xmlname <<endl;

  std::ifstream ifile(xmlname);
  if (!ifile.is_open()) {
    cout<< "file not found: " << xmlname <<endl;
    return;
  }

  std::string line;
  while (ifile >> line) {
    cout<< line <<endl;
  }
}

// class XMLComment {
// public:
//   bool string_;
// };

class XMLChannel {
public:
  std::string name_;
  std::string start_name_;
  std::string end_name_;
  std::vector<unsigned> data_;
  XMLChannel(std::string name): name_(name) {
    start_name_ = name_;
    start_name_.insert(0, "<");
    start_name_.append(">");
    end_name_ = name_;
    end_name_.insert(0, "</");
    end_name_.append(">");
    cout<< "start_name_ = " << start_name_ << " end_name_ = " << end_name_ <<endl;
  }
  const std::vector<unsigned>& GetData() const {return data_;}
  const std::string& GetName() const {return name_;}
  void Pickup(std::list<std::string> text)
  {
    //cout<< "// Pickup for " << name_ << " line = " << *i_line <<endl;
    
    //for (std::list<std::string>::iterator i_line = text.begin(); i_line != text.end(); ++i_line)
    
    std::list<std::string>::iterator i_line = text.begin();
    while(i_line != text.end())
    {
      //cout<< "Pickup for " << name_ << ": processing line = " << *i_line <<endl;
      
      // if (*i_line != start_name_) return;         // require exect matching in case of channels
      if (*i_line != start_name_) {               // require exect matching in case of channels
        //cout<< "Channel " << name_ << ": skip" <<endl;
        ++i_line;
        continue;
      }

      cout<< "Channel " << name_ << ": picking up data" <<endl;

      i_line = text.erase(i_line);                // remove <Vaa>

      cout<< "starting loop" <<endl;

      while (i_line != text.end())
      {
        const std::string line = *i_line;         // NB: const because this we call a ctor
        //cout<< "Pickup: current line = " << line <<endl;
        i_line = text.erase(i_line);

        if (line == end_name_) break;             // found </Vaa>, normal return

        //
        // for fucken ROOT
        //
        // std::stringstream ss;
        // ss.str("");
        // ss << line;
        //

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
        data_.push_back(val);
      }
    }
    // we are here in case if </Vaa> has been lost
    cout<< "***ERROR XMLChannel::Pickup for channel " << name_ << " no terminal " << end_name_ <<endl;
    return;
  }
};

class XMLReader {
public:
  std::ifstream ifile_;
  const std::string comm_start_;
  const std::string comm_end_;
  std::list<std::string> l_noblank_;
  std::list<std::string> l_nocomm_;
  XMLReader(const char* xmlname): ifile_(xmlname)
    , comm_start_("<!--")
    , comm_end_("-->")
  {
    if (!ifile_.is_open()) {
      cout<< "file not found: " << xmlname <<endl;
      return;  // exception
    }
    // write xml lines into list ignoring blank lines and spaces inside lines
    std::string line;
    while (std::getline(ifile_,line))  // NB: global function std::getline(istream& is, string& str);
    {
      const std::string whitespace = " \t\n\r";
      // trim leading whitespace
      std::string::size_type notwhite = line.find_first_not_of(whitespace);
      line.erase(0,notwhite);

      // trim trailing whitespace
      notwhite = line.find_last_not_of(whitespace);
      line.erase(notwhite+1);
      
      if (line.size() > 0) l_noblank_.push_back(line);
    }
    //     for (std::list<std::string>::const_iterator i_str=l_noblank_.begin(); i_str!=l_noblank_.end(); ++i_str)
    //     {
    //       cout<< *i_str <<endl;
    //     }
    //     cout<< "blanks lines and leading/trailing spaces are discarded\n" <<endl;
  }
  void RunFilters() {
    FilterComments(l_noblank_, l_nocomm_);
    // for (std::list<std::string>::const_iterator i_str=l_nocomm_.begin(); i_str!=l_nocomm_.end(); ++i_str)
    // {
    //   cout<< *i_str <<endl;
    // }
  }
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
      i_line = lin.erase(i_line);
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
          comment = false;
          //
          // To check next code:
          //
          //           // skip commented out lines
          //           if (pos+comm_end_.size() < line.size())
          //           {
          //             // comment ended in current string
          //             comment = false;
          //             std::string buf = line.substr(pos+comm_end_.size());    // save part of line after the comment
          //             if (buf.size() > 0) lout.push_back(buf);
          //           }
        }
      }
    }
  }
  void GetData()
  {
    cout<< "XMLReader::GetData" <<endl;
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

    //     std::map<std::string, std::list<unsigned> > chan_map;
    // 
    //     //std::list<unsigned> vec;
    //     chan_map[name_Vaa];
    //     chan_map[name_Vdd];
    //     chan_map[name_RTD2];
    //     chan_map[name_RTD3];
    //     chan_map[name_AOH];
    //     chan_map[name_Vpc];
    //     chan_map[name_Vbg];
    //     chan_map[name_TS];
    //     
    //     for (std::map<std::string, std::list<unsigned> >::const_iterator i_chan=chan_map.begin(); i_chan!=chan_map.end(); ++i_chan)
    //     {
    //       cout<< i_chan->first << " size = " << i_chan->second.size() <<endl;
    //     }
    
    std::vector<XMLChannel> vchan;
    XMLChannel Vaa("Vaa");			vchan.push_back(Vaa);
    XMLChannel Vdd("Vdd");			vchan.push_back(Vdd);
    XMLChannel RTD2("RTD2");			vchan.push_back(RTD2);
    XMLChannel RTD3("RTD3");			vchan.push_back(RTD3);
    XMLChannel AOH("AOH");			vchan.push_back(AOH);
    XMLChannel Vpc("Vpc");			vchan.push_back(Vpc);
    XMLChannel Vbg("Vbg");			vchan.push_back(Vbg);
    XMLChannel TS("TS");				vchan.push_back(TS);

    cout<< "//-- The number of channels vchan.size() = " << vchan.size() <<endl;
    
    for (std::vector<XMLChannel>::iterator i_vchan=vchan.begin(); i_vchan!=vchan.end(); ++i_vchan)
    {
      cout<< "//-- XMLReader::GetData: try " << i_vchan->GetName() <<endl;
      i_vchan->Pickup(l_nocomm_);
    }

    //     for (std::list<std::string>::iterator i_line=l_nocomm_.begin(); i_line!=l_nocomm_.end(); ++i_line)
    //     {
    //       const std::string line = *i_line;
    //       cout<< "XMLReader::GetData: line = " << line <<endl;
    //       for (std::vector<XMLChannel>::iterator i_vchan=vchan.begin(); i_vchan!=vchan.end(); ++i_vchan)
    //       {
    //         //cout<< "XMLReader::GetData: try " << i_vchan->GetName() <<endl;
    //         i_vchan->Pickup(l_nocomm_);
    //         /////////////////////////////////////i_vchan->Pickup(i_vchan);
    //       }
    //     }

    cout<< "\nResult:" <<endl<<endl;

    for (std::vector<XMLChannel>::const_iterator i_vchan=vchan.begin(); i_vchan!=vchan.end(); ++i_vchan)
    {
      const std::vector<unsigned>& chan = i_vchan->GetData();
      cout<< "DCU channel " << i_vchan->GetName() << " has " << chan.size() << " numbers" <<endl;
      //       for (std::vector<unsigned>::const_iterator i_chan=chan.begin(); i_chan!=chan.end(); ++i_chan)
      //       {
      //         cout<< *i_chan <<endl;
      //       }
    }
  }
};

/*
main(int argc, char* argv[])
{
  const char* xmlname;
  
  //const char[] xmlname_def = "/home/zatserkl/pos_cvs/TriDAS/pixel/PixelCalibrations/data/pixelTemperatureCalibrationData.xml-2007_11_25-16_11_51-100points.xml";
  const char xmlname_def[] = "test.xml";

  XMLReader* xmlReader;

  if (argc > 1) {
    //for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;
    xmlname = argv[1];
  }
  else xmlname = xmlname_def;

  //cout<< "xmlname = " << xmlname <<endl;
    
  xmlReader = new XMLReader(xmlname);
  xmlReader->RunFilters();

  cout<<endl<< "//-- xmlReader->GetData();" <<endl<<endl;

  xmlReader->GetData();
}
*/
