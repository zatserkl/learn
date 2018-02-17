// http://www.cprogramming.com/c++11/c++11-lambda-closures.html

/* compile on Mac OS X with 
clang++ -Wall -std=c++11 lambda_function.cpp
*/

#include <iostream>

using namespace std;

int main()
{
    // basic syntax for lambda function
    auto func = [] () {cout << "Hello world\n";};   // NB trailing semicolon

    // use the lambda function
    func(); // now call the function
}
