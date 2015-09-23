#ifndef STD_BASIC_STRING_IDENTIFIER_H
#define STD_BASIC_STRING_IDENTIFIER_H

#include <string>

namespace std_basic_string_identifier
{
    template <typename T>
    struct is_std_basic_string_class
    {
        static bool const is_specialised{ false };
        static bool const is_specialized{ is_specialised };
        static bool const value{ false };
    };

    template <typename C, typename CT, typename A>
    struct is_std_basic_string_class < std::basic_string<C, CT, A> >
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ is_specialised };
        static bool const value{ true };
    };

    void test();
}

#endif // STD_BASIC_STRING_IDENTIFIER_H