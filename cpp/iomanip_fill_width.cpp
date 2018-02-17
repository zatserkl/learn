#include <iostream>
#include <sstream>
#include <iomanip>

using std::cout;      using std::endl;

int main()
{
    std::stringstream ss;
    ss.fill('0');
    ss.width(5);
    ss << 1;

    cout<< "ss.str() = " << ss.str() <<endl;

    return 0;
}
