// Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 13, 2018

/*
clang++ -Wall -std=c++17 binary_representation_convert.cpp -o binary_representation_convert
*/

#include <iostream>
#include <cstdarg>
#include <string>

using std::cout;    using std::endl;

int convert(const char* bin_number_char)
{
    // cout<< "bin_number_char: " << bin_number_char <<endl;

    unsigned int number = 0;

    for (auto c: std::string(bin_number_char)) {
        cout<< c;
        
        number = (number << 1) + int(c - '0');
    }
    cout<<endl;

    return number;
}

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        cout<< "Usage example: " << argv[0] << " 10010001" <<endl;
        return 0;
    }

    unsigned int number = convert(argv[1]);
    cout<< "number = " << number <<endl;
}
