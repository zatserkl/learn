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
  std::string portcard_curr_;		// can be pointer to element of vector portcard_names_ as well
  std::vector<std::string> portcard_names_;
  std::map< std::string, std::vector<unsigned> > data_map_;
  XMLChannel(std::string name): name_(name) {
    start_name_ = name_;
    start_name_.insert(0, "<");
    start_name_.append(">");
    end_name_ = name_;
    end_name_.insert(0, "</");
    end_name_.append(">");
    // fill possible portcard names
    portcard_names_.push_back("FPix_BmO_D1_PRT3");
    portcard_names_.push_back("FPix_BmO_D2_PRT3");
  }
  const std::map< std::string, std::vector<unsigned> >& GetDataMap() const {return data_map_;}
  const std::string& GetName() const {return name_;}
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
      
      found_end = false;

      //cout<< "Channel " << name_ << ": picking up data" <<endl;

      i_line = text.erase(i_line);                // remove <Vaa>

      while (i_line != text.end())
      {
        const std::string line = *i_line;         // NB: const because this we call a ctor?
        //cout<< "Pickup: current line = " << line <<endl;
        i_line = text.erase(i_line);

        if (line == end_name_) {
          found_end = true;                       // found </Vaa>
          break;
        }

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
        data_map_[portcard_curr_].push_back(val);
      }
    }
    if (!found_end) {
      cout<< "***ERROR XMLChannel::Pickup for channel " << name_ << " no terminal " << end_name_ <<endl;
    }
  }
};
// //
// // operator << in global scope for class XMLChannel
// //
// std::ostream& operator << (std::ostream& os, const XMLChannel& xmlChannel)
// {
//   // To much lines to output. This way is better to have a method Print()
// }

class XMLReader {
public:
  std::ifstream ifile_;
  const std::string comm_start_;
  const std::string comm_end_;
  std::list<std::string> l_noblank_;
  std::list<std::string> l_nocomm_;
  std::vector<XMLChannel> vchan_;
  XMLReader(const std::string& xmlname): ifile_(xmlname.c_str())
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
    // cout<< "XMLReader::GetData" <<endl;
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
    
    XMLChannel Vaa("Vaa");			vchan_.push_back(Vaa);
    XMLChannel Vdd("Vdd");			vchan_.push_back(Vdd);
    XMLChannel RTD2("RTD2");		vchan_.push_back(RTD2);
    XMLChannel RTD3("RTD3");		vchan_.push_back(RTD3);
    XMLChannel AOH("AOH");			vchan_.push_back(AOH);
    XMLChannel Vpc("Vpc");			vchan_.push_back(Vpc);
    XMLChannel Vbg("Vbg");			vchan_.push_back(Vbg);
    XMLChannel TS("TS");				vchan_.push_back(TS);

    //cout<< "//-- The number of channels vchan_.size() = " << vchan_.size() <<endl;

    for (std::vector<XMLChannel>::iterator i_vchan=vchan_.begin(); i_vchan!=vchan_.end(); ++i_vchan)
    {
      // cout<< "//-- XMLReader::GetData: try " << i_vchan->GetName() <<endl;
      i_vchan->Pickup(l_nocomm_);
      // cout<< "\nResult:" <<endl;
      // i_vchan->Print();
    }

    //     cout<< "\nResult:" <<endl<<endl;
    // 
    //     for (std::vector<XMLChannel>::const_iterator i_vchan=vchan_.begin(); i_vchan!=vchan_.end(); ++i_vchan)
    //     {
    //       cout<< "channel " << i_vchan
    //       // const std::map< std::string, std::vector<unsigned> >& pc_chan = i_vchan->GetDataMap();
    //       for (std::map< std::string, std::vector<unsigned> >::const_iterator i_pcard_chan = i_vchan->GetDataMap().begin();
    //            i_pcard_chan != i_vchan->GetDataMap().end(); ++i_pcard_chan)
    //       {
    //         cout<< "
    //       }
    //     }
    
  }
};

main(int argc, char* argv[])
{
  std::string ifname;

  XMLReader* xmlReader;

  //for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;
  if (argc > 1) ifname = argv[1];

  if (ifname.size() == 0) {
    cout<< "Usage: " << argv[0] << " ifname [ofname]" <<endl;
    return 0;
  }

  // cout<< "ifname = " << ifname <<endl;
    
  xmlReader = new XMLReader(ifname);
  xmlReader->RunFilters();

  //cout<<endl<< "//-- xmlReader->GetData();" <<endl<<endl;

  xmlReader->GetData();
 
//   if (ofname.size() == 0)
//   {
//    // construct output name
// 
//     // find end of pathname if any
//     std::size_t pos = ifname.rfind("/");
//     if (pos != std::string::npos) ofname = ifname.substr(pos+1);
//     else ofname = ifname;
// 
//     // add .dat
//     ofname.append(".dat");
//   }
//   std::ofstream ofile(ofname.c_str());
  
  //   const std::vector<unsigned>* vv[8];
  //   for (unsigned i=0; i<8; ++i) {
  //     const std::vector<unsigned>& v = xmlReader->vchan_[i].GetData();
  //     vv[i] = &v;
  //   }
  //   
  //   for (unsigned ipoint=0; ipoint<vv[0]->size(); ++ipoint) {
  //     for (int iv=0; iv<8; ++iv) {
  //       const std::vector<unsigned>* v = vv[iv];
  //       // ofile<< (*v)[ipoint] <<"   "<< (*v)[ipoint] <<"   ";
  //       ofile<< (*v)[ipoint] <<"   "<< 0 <<"   ";
  //     }
  //     ofile<<endl;
  //   }

  std::vector<std::string> pcard_names;
  for (std::map<std::string, std::vector<unsigned> >::const_iterator it=xmlReader->vchan_[0].GetDataMap().begin();
       it!=xmlReader->vchan_[0].GetDataMap().end(); ++it)
  {
    pcard_names.push_back(it->first);
    // cout<< "portcard it->first = " << it->first <<endl;
  }

  // input name w/o path if any
  std::string filename;
  // find end of pathname if any
  std::size_t pos = ifname.rfind("/");
  if (pos != std::string::npos) filename = ifname.substr(pos+1);
  else filename = ifname;
      
  for (std::vector<std::string>::const_iterator pcard_name=pcard_names.begin(); pcard_name!=pcard_names.end(); ++pcard_name)
    {
      // construct output name
      std::stringstream ofname;
      ofname << filename << "_" << *pcard_name << ".dat";

      std::ofstream ofile(ofname.str().c_str());
      
      // the number of points should be the same for all DCU registers
      
      const std::vector<unsigned>* vv[8];
      for (unsigned i=0; i<8; ++i) {
        //std::map<std::string, std::vector<unsigned> >::const_iterator it_map = xmlReader->vchan_[i].GetDataMap().find(*pcard_name);
        //vv[i] = &it_map->second;

        vv[i] = &xmlReader->vchan_[i].GetDataMap().find(*pcard_name)->second;
      }
      
      for (unsigned ipoint=0; ipoint<vv[0]->size(); ++ipoint) {
        for (int iv=0; iv<8; ++iv) {
          const std::vector<unsigned>* v = vv[iv];
          // ofile<< (*v)[ipoint] <<"   "<< (*v)[ipoint] <<"   ";
          ofile<< (*v)[ipoint] <<"   "<< 0 <<"   ";
        }
        ofile<<endl;
      }

      ofile.close();
    }
}
