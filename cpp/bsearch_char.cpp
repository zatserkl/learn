/*
Compile for C++14 (because of auto)
clang++ -std=c++14 -Wall bsearch_char.cpp
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdarg>

using std::cout;      using std::endl;

inline std::vector<unsigned char>& operator << (std::vector<unsigned char>& vbyte, const unsigned char& byte) {
    vbyte.push_back(byte);
    return vbyte;
}

int main(int argc, char *argv[])
{
    // cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

    // if (argc == 1) {
    //   cout<< "Usage:\n" << argv[0] << " par1 par2 par3" <<endl;
    //   return 0;
    // }

    std::vector<unsigned char> pattern;

    pattern << 'b' << 'y' << 't' << 'e';
    //--binary-- pattern << 0 << 0 << 0 << 0;

    for (auto a=pattern.begin(); a!=pattern.end(); ++a) {     // auto is C++14 extension, compile with -std=c++14
        cout<< (char) *a;
        //--binary-- cout<< std::hex << (unsigned) (unsigned char) *a << " ";
    }
    cout<<endl;

    return 0;
}
