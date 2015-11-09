#include "explicit_template_instantiation_test.h"
#include "explicit_template_instantiation.h"

#include <iostream>
#include <string>


void explicit_template_instantiation::test()
{
    std::cout << "Explicit Template Instantiation Test" << std::endl << std::endl;

    //Some_Template<short> st_short{ 987 }; // cannot instantiate - as expected
    Some_Template<int> st_int{ 123456 };
    Some_Template<double> st_double{ 1234.56789 };
    Some_Template<std::string> st_std_string{ "this is a std::string" };

    //std::cout << "Some_Template<short>::get_value() = \"" << st_short.get_value() << "\"" << std::endl; // cannot instantiate - as expected
    std::cout << "Some_Template<int>::get_value() = \"" << st_int.get_value() << "\"" << std::endl;
    std::cout << "Some_Template<double>::get_value() = \"" << st_double.get_value() << "\"" << std::endl;
    std::cout << "Some_Template<std::string>::get_value() = \"" << st_std_string.get_value() << "\"" << std::endl;

    std::cout << std::endl;

    //Other_Template<short> ot_short{ 987 }; // static_assert - as expected
    Other_Template<int> ot_int{ 123456 };
    Other_Template<double> ot_double{ 1234.56789 };
    //Other_Template<std::string> ot_std_string{ "this is a std::string" }; // static_assert - as expected

    //std::cout << "Other_Template<short>::get_value() = \"" << ot_short.get_value() << "\"" << std::endl; // static_assert - as expected
    std::cout << "Other_Template<int>::get_value() = \"" << ot_int.get_value() << "\"" << std::endl;
    std::cout << "Other_Template<double>::get_value() = \"" << ot_double.get_value() << "\"" << std::endl;
    //std::cout << "Other_Template<std::string>::get_value() = \"" << ot_std_string.get_value() << "\"" << std::endl; // static_assert - as expected

    std::cout << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}