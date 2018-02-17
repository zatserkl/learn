#include <iostream>
#include <cstdarg>

using std::cout;      using std::endl;

void fun(const char* fname) {
    cout<< "fun: fname = " << fname <<endl;
}

int main(int argc, char *argv[])
{
    cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

    if (argc == 1) {
        cout<< "Usage:" <<endl;
        cout<< argv[0] << " filename " <<endl;
        return 0;
    }

    const char* fname = argv[1];

    cout<< "fname = " << fname <<endl;

    fun(fname);

    return 0;
}
