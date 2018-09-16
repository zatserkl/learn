// http://www.cplusplus.com/reference/memory/unique_ptr/operator-%3E/

// Modified: Andriy Zatserklyaniy <zatserkl@gmail.com> Sep 15, 2018

/*
clang++ -Wall -std=c++17 unique_ptr_example.cpp
*/

#include <iostream>
#include <memory>
#include <iostream>

using std::cout;    using std::endl;

struct C {
    int a;
    int b;
    ~C() {
        cout<< "C destructor" <<endl;
    }
};

void fun()
{
    std::unique_ptr<C> foo (new C);
    std::unique_ptr<C> bar;

    foo->a = 10;
    foo->b = 20;

    bar = std::move(foo);

    if (foo) std::cout << "foo: " << foo->a << ' ' << foo->b << '\n';
    if (bar) std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';
}

std::unique_ptr<C> fun_return()
{
    std::unique_ptr<C> foo (new C);
    std::unique_ptr<C> bar;

    foo->a = 10;
    foo->b = 20;

    bar = std::move(foo);

    if (foo) std::cout << "foo: " << foo->a << ' ' << foo->b << '\n';
    if (bar) std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';

    return bar;
}

int main()
{
    fun();
    cout<< "after fun call" <<endl<<endl;

    std::unique_ptr<C> c = fun_return();
    cout<< "c->a = " << c->a << " c->b = " << c->b <<endl;

    cout<< "after fun_return call" <<endl;
}
