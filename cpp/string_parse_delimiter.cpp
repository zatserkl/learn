#include <iostream>
#include <string>
#include <sstream>

using std::cout;      using std::endl;

int main()
{
    std::string input = "abc,def,ghi";
    std::istringstream ss(input);
    std::string token;

    while(std::getline(ss, token, ',')) {
        cout << token << '\n';
    }

    return 0;
}
