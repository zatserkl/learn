#include <string>
#include <iostream>

using std::cout;			using std::endl;

void print(const std::string& str, std::ostream& out=std::cout) {
  out<< str <<std::endl;
}

class PrintToStream {
private:
	std::string str_;	
public:
	PrintToStream(std::string str): str_(str) {}
	
	//
	// there is no much sence to do this way.
	// call should be
	// ... << printToStream.printout() << ...
	//
	std::ostream& printout(std::ostream& stream) const {
		stream << str_;
		return stream;
	}
	
	//
	// Operator << should not be defined in class:
	// where is no sence to do that: how it suppose to use it this way: printToStream.operator<< ???
	//
	// std::ostream& operator << (std::ostream& os) const {
	//	os << str_;
	//	return os;
	// }
	
	// declare a global operator << as a friend to let it access the private data
	friend std::ostream& operator <<(std::ostream&, PrintToStream&);
};

//-- The best is
//-- standalone operator <<
//
// Overloading of the iostream << and >> operators
// These must be declared ouside our class, with global scope
// http://www.codeproject.com/cpp/cfraction.asp?df=100&forumid=15432&exp=0&select=501053
//
std::ostream& operator << (std::ostream& os, PrintToStream& printToStream) {
	os << printToStream.str_;
	return os;
}

int main()
{
  std::string str = "this is a string";
  print(str, std::cout);

  // test PrintToStream
  PrintToStream printToStream("This is a string to be sent through PrintToStream");

	//cout<<endl;
	//cout<< "Wrong output (osream address at the end of string)" <<endl;
	//cout<< printToStream <<endl;

	//cout<<endl;
	printToStream.printout(std::cout) << " <-- used method printout: printToStream.printout(std::cout)" <<endl;

	cout<<endl<< "Attempt to print in stream with line: cout<< printToStream <<endl;" <<endl;
	cout<< printToStream <<endl;

  return 0;
}
