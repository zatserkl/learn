#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;      using std::endl;

class IndentStream: public std::stringstream {
public:
  int nindents_;
  void indent() {++nindents_;}
};

main()
{
  std::stringstream indent;
  char null;

  std::string extension_table_name = "DCU_CALIB_FILTER_PARAMS";
  std::string table_name = "DCU Calibration Filter Parameters";

  std::string ofname = "dbtable.xml";

  // std::ofstream o(ofname.c_str());
  std::ostream& o = cout;

  o<<indent.str()<< "<?xml version='1.0' encoding='UTF-8'?>" <<endl;
  o<<indent.str()<< "<!DOCTYPE root []>" <<endl;
  o<<indent.str()<< "<ROOT>" <<endl;

    indent << '\t';
    o<<indent.str()<< "<TYPE>" <<endl;
      indent << '\t';
      o<<indent.str()<< "<EXTENSION_TABLE_NAME>" << extension_table_name << "</EXTENSION_TABLE_NAME>" <<endl;
      o<<indent.str()<< "<NAME>" << table_name << "</NAME>" <<endl;
      indent >> null;
    o<<indent.str()<< "</TYPE>" <<endl;
    indent >> null;

    o<<indent.str()<< "<RUN>" <<endl;
    o<<indent.str()<< "</RUN>" <<endl;

  o<<indent.str()<< "</ROOT>" <<endl;

  // o.close();
}
