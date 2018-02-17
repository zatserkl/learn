// asctime example
#include <ctime>
#include <iostream>

using std::cout;    using std::endl;

int main (int argc, char* argv[])
{
    // time_t works as well as std::time_t
    time_t rawtime;                   // time_t: the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC

    time(&rawtime);                   // Get the current calendar time as a time_t object

    // cout<< "date/time is: " << asctime(localtime(&rawtime)) <<endl; // the same as ctime(&rawtime)
    cout<< "date/time is: " << ctime(&rawtime) <<endl;
    cout<< "Note that asciitime inserts carrige return (\\n) into the string!" <<endl;

    return 0;
}
