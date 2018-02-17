#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

void anErrorFunc(const std::string& x)
{
    std::ifstream file;
    file.open(x);
    if (!file) throw std::runtime_error("Could not open file");
}

void someOtherFunction(const std::string& fname)
{
    //Do stuff
    anErrorFunc(fname);
    //Do other stuff
}

int main()
{
    try {
        someOtherFunction("somefile.txt");
    } catch (std::exception &ex) {
        std::cout << "Ouch! That hurts, because: " << ex.what() << "!\n";
    }
}
