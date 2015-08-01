#include "enum_stuff.h"
#include "enum_data_manager.h"

#include <iostream>

void enum_stuff::test()
{
    std::cout << "Enum Stuff" << std::endl << std::endl;

    DataType<DataEnum::Int> i{ 5 };
    std::cout << i << std::endl;
    auto e(get_enum<decltype(i)>());
    std::cout << (e == DataEnum::Int ? "i is an int" : "is is not an int") << std::endl;


    std::cout << "----------------------------------------" << std::endl;
}