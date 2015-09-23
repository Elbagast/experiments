#include "question_based_template.h"

#include <iostream>

void question_based_template::test()
{
    std::cout << "Question Based Templates Test" << std::endl << std::endl;

    std::cout
        << "std::string: "
        << std::boolalpha
        << bool(Extension_Enum::StdString == Simple_Extension_Selector<std::string>::value)
        << std::noboolalpha
        << std::endl;

    std::cout
        << "std::wstring: "
        << std::boolalpha
        << bool(Extension_Enum::StdString == Simple_Extension_Selector<std::wstring>::value)
        << std::noboolalpha
        << std::endl;

    std::cout
        << "Something<int>: "
        << std::boolalpha
        << bool(Extension_Enum::Something == Simple_Extension_Selector<Something<int>>::value)
        << std::noboolalpha
        << std::endl;

    std::cout
        << "Something<int, bool>: "
        << std::boolalpha
        << bool(Extension_Enum::Something == Simple_Extension_Selector<Something<int, bool>>::value)
        << std::noboolalpha
        << std::endl;

    std::cout
        << "Else<int, bool>: "
        << std::boolalpha
        << bool(Extension_Enum::Else == Simple_Extension_Selector<Else<int, bool>>::value)
        << std::noboolalpha
        << std::endl;

    std::cout
        << "Else<std::string, double>: "
        << std::boolalpha
        << bool(Extension_Enum::Else == Simple_Extension_Selector<Else<std::string, double>>::value)
        << std::noboolalpha
        << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}