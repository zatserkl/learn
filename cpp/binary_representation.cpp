// Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 13, 2018

/*
clang++ -std=c++17 binary_representation.cpp -o binary_representation
*/

#include <iostream>
#include <vector>
#include <cstdarg>

using std::cout;    using std::endl;

// https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
void bin(unsigned n) 
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
    {
        (n & i)? printf("1"): printf("0");
    }
}

std::vector<int> binary(int number)
{
    std::vector<int> vbinary;

    for (unsigned int i=1<<31; i>0; i = i/2)
    {
        // int bit = number & i;
        bool bit = number & i;
        // cout<< "i = " << i << " bit = " << bit <<endl;
        vbinary.push_back(bit);
    }

    cout<< "vbinary.size() = " << vbinary.size() <<endl;

    return vbinary;
}

int longest_zeros(const std::vector<int>& vbinary)
{
    int i1 = 0;
    while (vbinary[i1] == 0) i1++;

    int len = 0;
    int len_max = 0;
    for (int i=i1+1; i<vbinary.size(); ++i) {
        if (vbinary[i] == 0) len++;
        else {
            if (len > len_max) len_max = len;
            len = 0;
        }
    }

    return len_max;
}

int main(int argc, const char* argv[])
{
    for (int i=0; i<argc; ++i) cout<< i << "\t" << argv[i] <<endl;

    int number = 529;   // 1000010001
    if (argc > 1) number = atoi(argv[1]);
    cout<< "number = " << number <<endl;

    auto vbinary = binary(number);

    cout<< "1 987654321 987654321 9876543210" <<endl;
    for (auto bit: vbinary) {
        cout<< bit;
    }
    cout<<endl;

    int len_max = longest_zeros(vbinary);
    cout<< "len_max = " << len_max <<endl;
}
