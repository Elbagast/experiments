#include "enum_stuff2.h"
#include <iostream>

namespace
{
    enum class Some_Enum
    {
        Bool,
        Int,
        Double,
    };
}

void enum_stuff2::test()
{
    std::cout << "Enum Stuff 2" << std::endl << std::endl;

    std::cout << std::boolalpha;
    std::cout << (Enum_Binder<bool, Some_Enum, Some_Enum::Bool>::enum_value() == Some_Enum::Bool) << std::endl;

    std::cout << std::noboolalpha;
    
    std::cout << "----------------------------------------" << std::endl;
}