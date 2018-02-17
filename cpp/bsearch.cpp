/*
Compile for C++14 (because of auto)
clang++ -std=c++14 -Wall bsearch.cpp
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdarg>

using std::cout;      using std::endl;

inline std::vector<char>& operator << (std::vector<char>& vbyte, const char& byte) {
    vbyte.push_back(byte);
    return vbyte;
}

int main(int argc, char *argv[])
{
    // cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

    if (argc == 1) {
        cout<< "Usage:\n" << argv[0] << " fname" <<endl;
        return 0;
    }

    std::vector<char> pattern;

    // pattern << 'b' << 'y' << 't' << 'e';
    //-- pattern << 0 << 0 << 0 << 0;
    // pattern << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
    //--run-header-- pattern << 0xD2 << 0x55 << 0x4E;
    pattern << 0xF0 << 0x43 << 0x54;

    cout<< "pattern:";
    for (auto a=pattern.begin(); a!=pattern.end(); ++a) {     // auto is C++14 extension, compile with -std=c++14
        cout<< " " << std::hex << (unsigned) (unsigned char) *a << std::dec;
    }
    cout<<endl;

    const char* fname = argv[1];
    std::ifstream file(fname, std::ios::binary);
    if (!file) {
        cout<< "Could not open file " << fname <<endl;
        return 0;
    }

    // get length of file:
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    // allocate memory:
    char* buffer = new char[length];

    // read data as a block:
    file.read(buffer,length);

    file.close();

    //cout<< "buffer[1] == pattern[0] = " << std::boolalpha << (buffer[1] == pattern[0]) <<endl;

    int occurences_max = 10;

    int occurences = 0;
    for (unsigned long address=0; address<length-pattern.size(); ++address)
    // for (unsigned long address=0; address<10; ++address)
    {
        //cout<< address << "\t" << std::hex << (unsigned) (unsigned char) buffer[address] << " pattern[0] = " << (unsigned) (unsigned char) pattern[0] << std::dec <<endl;
        if (buffer[address] == pattern[0]) {
            bool found = true;
            //cout<< "address = " << address << " pattern[0] = " << pattern[0] <<endl;
            for (unsigned iaddress=1; iaddress<pattern.size(); ++iaddress) {
                if (buffer[address+iaddress] != pattern[iaddress]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                ++occurences;
                if (occurences <= occurences_max) cout<< "address = " << address << " occurences = " << occurences <<endl;
            }
        }
    }

    cout<< "occurences = " << occurences <<endl;

    delete[] buffer;
    return 0;
}
