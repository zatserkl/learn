#include <iostream>
#include <sstream>
#include <string>

using std::cout;      using std::endl;

void figure_out(const std::string& input)
{
  cout<< "\nfigure_out: input = '" << input << "'" <<endl;

  // std::stringstream ss;
  // ss << input;

  std::istringstream ss(input);

  cout<< "content of the stringstream object: '" << ss.str() << "'" <<endl;

  int number;
  ss >> number;

  if (ss.eof()) {
    cout<< "this is a number " << number <<endl;
    return;   //-- The user input was processed. Return.
  }

  cout<< "--> the input was a string <--" <<endl;

  // restore the stream
  ss.clear();
  ss.seekg(0);

  std::string str;

  /// std::getline(ss, str);  //-- to deal with spaces use getline instead of ss >> str;

  /// cout<< "after std::getline(ss, str) str = '" << str << "'" <<endl;

  /// if (str[0] == '"' && str[str.size()-1] == '"')
  /// {
  ///   cout<< "strip quoters" <<endl;

  ///   cout<< "str.size() = " << str.size() <<endl;
  ///   str.erase(str.size()-1);
  ///   cout<< "str.size() = " << str.size() << " str = '" << str << "'" <<endl; 
  ///   str.erase(0, 1);
  ///   cout<< "str.size() = " << str.size() << " str = '" << str << "'" <<endl; 
  /// }

  if (ss.str()[0] == '\"' && ss.str()[ss.str().size()-1] == '\"')
  {
    cout<< "strip quoters" <<endl;
    str = ss.str().substr(1, ss.str().size()-2);
  }
  else std::getline(ss, str);

  cout<< "this is a string '" << str << "'" <<endl;
}

int main()
{
  std::string qstr = "\"   abc   \"";
  cout<< "size of string '" << qstr << "' is " << qstr.size() <<endl;

  std::string input;

  input = "100";
  figure_out(input);

  input = "100a";
  figure_out(input);

  input = "a100";
  figure_out(input);

  input = "\"a100\"";
  figure_out(input);

  input = "\"    a100\"";
  figure_out(input);

  input = "\"a100    \"";
  figure_out(input);

  return 0;
}
