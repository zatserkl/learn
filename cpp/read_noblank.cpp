#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

using std::cout;      using std::endl;

main()
{
  std::string line = "   <Serial>1</Serial>";
  int serial = 0;
  sscanf(line.c_str(), "<Serial>%d</Serial>", &serial);
  cout<< "serial = " << serial <<endl;

  std::stringstream ss;
  ss.str("");
  ss << line;

  // char c_SERIAL[9];
  // int event;

  // ss >> c_SERIAL >> event;
  // cout<< "c_SERIAL = " << c_SERIAL << " event = " << event <<endl;

  cout<< "\nCurrent approach is to getline and replace tags (keywords) with space\n" <<endl;

  line = "      <Data>-5.5,5.7</Data>";
  // remove open tag
  const std::string tag_Data_begin = "<Data>";
  size_t pos = line.find(tag_Data_begin);
  if (pos != std::string::npos) line.replace(pos, tag_Data_begin.size(), " ");
  // // remove close tag (don't need, actually)
  // const std::string tag_Data_end = "</Data>";
  // line.replace(line.find(tag_Data_end), tag_Data_end.size(), " ");
  // remove comma
  line.replace(line.find(","), 1, " ");
  cout<< "line = " << line <<endl;
  // read x and y
  float x = 0, y = 0;
  ss.str("");
  ss << line;
  ss.clear();
  ss >> x >> y;
  // ss >> x;
  cout<< "x = " << x << " y = " << y <<endl;
  // if (ss.rdstate()) cout<< "ss: eofbit " << ss.eofbit << " failbit " << ss.failbit << " badbit " << ss.badbit << " goodbit " << ss.goodbit <<endl;
  // cout<< "ss: eofbit " << ss.eofbit << " failbit " << ss.failbit << " badbit " << ss.badbit << " goodbit " << ss.goodbit <<endl;
  //cout<< "ss: eofbit " << ss.rdstate()&std::iostream::eofbit << " failbit " << ss.rdstate()&std::iostream::failbit << " badbit " << ss.rdstate()&std::iostream::badbit << " goodbit " << ss.rdstate()&std::iostream::goodbit <<endl;
  if (ss.rdstate() & std::iostream::eofbit) cout<< "eofbit" <<endl;
  if (ss.rdstate() & std::iostream::failbit) cout<< "failbit" <<endl;
  if (ss.rdstate() & std::iostream::badbit) cout<< "badbit" <<endl;
  if (ss.rdstate() & std::iostream::goodbit) cout<< "goodbit" <<endl;
  cout<< "ss.good() " << ss.good() << " ss.eof() " << ss.eof() << " ss.bad() " << ss.bad() << " ss.fail() " << ss.fail() <<endl;

  line = "   <Serial>1</Serial>";

  const std::string serial_begin = "<Serial>";
  const std::string serial_end = "</Serial>";
  line.replace(line.find(serial_begin), serial_begin.size(), " ");
  line.replace(line.find(serial_end), serial_end.size(), " ");
  cout<< "line = " << line <<endl;

  line = "    <CHN2>";
  const std::string chn_begin = "<CHN";
  line.replace(line.find(chn_begin), chn_begin.size(), " ");
  ss.str("");
  ss << line;
  int osc_chan;
  ss >> osc_chan;
  cout<< "osc_chan = " << osc_chan <<endl;

  cout<< "\nAnother approach\n" <<endl;
  
  std::stringstream ssfile("      <Data>-5.5,5.7</Data>");     // this stringstream will be our "file"
  // std::getline(ssfile,line);     // <---- reads with leading spaces (as it should be)
  // ssfile >> line;
  // cout<< "line: ---" << line << "---" <<endl;

  // sscanf(line.c_str(), "<Data>%f,%f</Data>", &x,&y);
  cout<< "ssfile.str(): ---" << ssfile.str() << "---" <<endl;
  sscanf(ssfile.str().c_str(), "<Data>%f,%f</Data>", &x,&y);
  cout<< "x " << x << " y " << y <<endl;

  // ssfile.clear();
  // ssfile.str("   aa bb cc");
  // while (ssfile) {
  //   ssfile >> line;
  //   cout<< "line: ---" << line << "---" <<endl;
  // }
}
