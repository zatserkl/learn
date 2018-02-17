// this is some comment

//DATA 1  10
//DATA 2  20
//DATA 3  30
//DATA 4  40
//DATA 5  50

#include <iostream>
#include <fstream>

using std::cout;      using std::endl;

main()
{
  const char* ifname = __FILE__;
  std::ifstream ifile(ifname);
  if (!ifile) {
    cout<< "File not found: " << ifname <<endl;
    return 0;
  }
  cout<< "ifname = " << ifname <<endl;

  std::string line;
  for (std::streampos pos; pos=ifile.tellg(), std::getline(ifile, line); )
  {
    if (line.find("//DATA ") == 0)    // line starts from "//DATA "
    {
      cout<< "the first line with \"//DATA \" is " << line <<endl;

      cout<< "return stream pointer before this line and read it again along with other four next" <<endl;
      ifile.seekg(pos);
      for (int i=0; i<5; ++i) {
          std::getline(ifile, line);
        cout<< "line = " << line <<endl;
      }
    }
  }
}
