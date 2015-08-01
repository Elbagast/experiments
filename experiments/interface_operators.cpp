#include "interface_operators.h"

#include <iostream>

int interface_operators::external_get_something(Interface const& object)
{
    return object.get_value();
}

void interface_operators::external_set_something(Interface& object, int value)
{
    object.set_value(value);
}

void interface_operators::test()
{
    std::cout << "Interface Operators Test" << std::endl << std::endl;

    Derived thing{20};
    //Interface& thing2{thing};

    //std::cout << external_get_something(thing2) << std::endl;


    std::cout << "----------------------------------------" << std::endl;
}