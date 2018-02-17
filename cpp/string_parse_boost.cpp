/*
clang++ -Wall string_parse_boost.cpp -I/opt/local/include
*/
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using std::cout;      using std::endl;

int main()
{
    std::string str = "This is a string";
    std::vector<std::string> vstring;
    boost::split(vstring, "string to split", boost::is_any_of("\t "));

    for (unsigned i=0; i<vstring.size(); ++i) cout<< vstring[i] <<endl;

    return 0;
}
