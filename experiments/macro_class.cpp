#include "macro_class.h"

#include <iostream>

#define TEST_MACRO_CLASS(type) \
    std::cout << #type " : is_specialised=" << Macro_Generated_Name<type>::is_specialised \
    << " name=\"" << Macro_Generated_Name<type>::name() << "\"" << std::endl;


void macro_class::test()
{
    std::cout << "Macro Class Test" << std::endl << std::endl;
    std::cout << std::boolalpha;

    TEST_MACRO_CLASS(bool)
    TEST_MACRO_CLASS(int)
    TEST_MACRO_CLASS(float)
    TEST_MACRO_CLASS(double)
    TEST_MACRO_CLASS(std::string)
    TEST_MACRO_CLASS(std::wstring)

    std::cout << std::noboolalpha;
    std::cout << "----------------------------------------" << std::endl;
}