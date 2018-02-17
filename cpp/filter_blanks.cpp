#include <string>
#include <sstream>
#include <iostream>

using namespace std;

main()
{
	std::string str_in = "   this is a string with blanks and \"quoted text\" inside   ";

	cout<< "str_in: ---" << str_in << "---" <<endl;

	std::stringstream ss(str_in);
	
	cout<< "ss.str(): ---" << ss.str() << "---" <<endl;
	
	std::string str_first;
	ss >> str_first;

	cout<< "first string extracted from ss: ---" << str_first << "---" <<endl;

	std::string str_concat;
	std::string buf;
	while (ss >> buf) str_concat += buf;

	cout<< "the rest is a concatenated string: --" << str_concat << "---" <<endl;
}
