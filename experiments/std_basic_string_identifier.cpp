#include "std_basic_string_identifier.h"

#include <iostream>

namespace
{
    class Something{};

    class C;
    class CT;
    class A;
}

void std_basic_string_identifier::test()
{
    std::cout << "is_std_basic_string_class<T> Test" << std::endl << std::endl;
    std::cout << std::boolalpha;

    std::cout << "is_std_basic_string_class<int>::is_specialized =  " << is_std_basic_string_class<int>::is_specialized << std::endl;
    std::cout << "is_std_basic_string_class<int>::value =  " << is_std_basic_string_class<int>::value << std::endl;
    std::cout << std::endl;
    std::cout << "is_std_basic_string_class<std::string>::is_specialized =  " << is_std_basic_string_class<std::string>::is_specialized << std::endl;
    std::cout << "is_std_basic_string_class<std::string>::value =  " << is_std_basic_string_class<std::string>::value << std::endl;
    std::cout << std::endl;
    std::cout << "is_std_basic_string_class<std::wstring>::is_specialized =  " << is_std_basic_string_class<std::wstring>::is_specialized << std::endl;
    std::cout << "is_std_basic_string_class<std::wstring>::value =  " << is_std_basic_string_class<std::wstring>::value << std::endl;
    std::cout << std::endl;
    std::cout << "is_std_basic_string_class<std::basic_string<char16_t>>::is_specialized =  " << is_std_basic_string_class<std::basic_string<char16_t>>::is_specialized << std::endl;
    std::cout << "is_std_basic_string_class<std::basic_string<char16_t>>::value =  " << is_std_basic_string_class<std::basic_string<char16_t>>::value << std::endl;
    std::cout << std::endl;
    std::cout << "is_std_basic_string_class<Something>::is_specialized =  " << is_std_basic_string_class<Something>::is_specialized << std::endl;
    std::cout << "is_std_basic_string_class<Something>::value =  " << is_std_basic_string_class<Something>::value << std::endl;
    std::cout << std::endl;

    std::cout << "When the template parameters are all just forward declared classes:" << std::endl << std::endl;
    std::cout << "is_std_basic_string_class<std::basic_string<C, CT, A>>::is_specialized =  " << is_std_basic_string_class<std::basic_string<C, CT, A>>::is_specialized << std::endl;
    std::cout << "is_std_basic_string_class<std::basic_string<C, CT, A>>::value =  " << is_std_basic_string_class<std::basic_string<C, CT, A>>::value << std::endl;
    std::cout << std::endl;

    std::cout << "Only the usage of the template is identified, not whether or not it will work." << std::endl;
    
    std::cout << std::noboolalpha;
    std::cout << "----------------------------------------" << std::endl;
}