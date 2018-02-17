// based on http://stackoverflow.com/questions/236129/split-a-string-in-c

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>

using std::cout;      using std::endl;

void no_copy(const std::string& str) {
    std::stringstream ss(str);
    std::string token;
    while (ss >> token) cout<< token <<endl;
}

void copy_cout(const std::string& str)
{
    std::istringstream ss(str);
    std::copy(std::istream_iterator<std::string>(ss),
              std::istream_iterator<std::string>(),             // the default ctor: end-of-stream
              std::ostream_iterator<std::string>(cout, "\n")    // NB: ostream_iterator, cout here
              );
    cout<< "after the copy ss.str() = " << ss.str() <<endl;
}

std::vector<std::string> copy_vector(const std::string& str)
{
    std::vector<std::string> v;

    std::istringstream ss(str);
    std::copy(std::istream_iterator<std::string>(ss),
              std::istream_iterator<std::string>(),             // the default ctor: end-of-stream
              std::back_inserter(v)
              );

    for (unsigned i=0; i<v.size(); ++i) cout<< v[i] <<endl;
    cout<< "after the copy ss.str() = " << ss.str() <<endl;
    return v;
}

std::vector<std::string> copy_vector_direct(const std::string& str)
{
    std::istringstream ss(str);

    // std::istream_iterator<std::string> first(ss);
    // std::istream_iterator<std::string> last;
    // std::vector<std::string> v(first,last);

    std::vector<std::string> v(
                               (std::istream_iterator<std::string>(ss)),    // NB: parenthises around the first parameter to avoid compiler message
                               std::istream_iterator<std::string>()
                               );

    for (unsigned i=0; i<v.size(); ++i) cout<< v[i] <<endl;
    cout<< "after the copy ss.str() = " << ss.str() <<endl;
    return v;
}

int main()
{
    std::string string = "This is a string";

    cout<< "---> no_copy" <<endl;
    no_copy(string);

    cout<< "\n---> copy_string" <<endl;
    copy_cout(string);

    cout<< "\n---> copy_vector" <<endl;
    std::vector<std::string> v = copy_vector(string);

    cout<< "\n---> copy_vector_direct" <<endl;
    std::vector<std::string> v_direct = copy_vector_direct(string);

    return 0;
}
