#include <iostream>

// Functional programming

// data structure

struct S {
    char letter;
    int number;
};

// functions for processing of data structure

void show_letter(S s_object) {
    std::cout << "s_object.letter = " << s_object.letter << std::endl;
}

void show_number(S s_object) {
    std::cout << "s_object.number = " << s_object.number << std::endl;
}

// Object-oriented programming

class ClassS {
public:
    char letter;
    int number;
    ClassS() {
        std::cout << "Default constructor of class ClassS" << std::endl;
        letter = ' ';
        number = 0;
    }
    ClassS(char letter_0, int number_0) {
        std::cout << "Constructor of class ClassS" << std::endl;
        letter = letter_0;
        number = number_0;
    }
    void show_letter() {
        std::cout << "letter = " << letter << std::endl;
    }
    void show_number() {
        std::cout << "number = " << number << std::endl;
    }
    void Show() {
        std::cout << "letter = " << letter << " number = " << number << std::endl;
    }
};

int main()
{
    std::cout << "Hello World!" << std::endl;

    int i;

    i = 5;

    std::cout << "i = " << i << std::endl;

    int *i_ptr;

    i_ptr = &i;

    std::cout << "i_ptr = " << i_ptr << std::endl;
    std::cout << "value at address i_ptr is " << *i_ptr << std::endl;

    S s;            // create an object s of type S

    s.letter = 'a';
    s.number = 10;

    std::cout << "s.letter = " << s.letter << " s.number = " << s.number << std::endl;

    S *s_ptr;
    s_ptr = &s;
    
    std::cout << "s_ptr->letter = " << s_ptr->letter << " s_ptr->number = " << s_ptr->number << std::endl;

    show_letter(s);
    show_number(s);

    // int i;
    ClassS classS;
    classS.Show();

    ClassS classS1('x', 100);
    classS1.Show();

    return 0;
}
