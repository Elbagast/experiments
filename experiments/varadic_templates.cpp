#include "variadic_templates.h"

#include <memory>
#include <iostream>

void variadic_templates::test()
{
    std::cout << "Variadic Templates Test" << std::endl << std::endl;

    std::unique_ptr<IElement> thing{ new Concrete_Element() };

    std::cout << thing->attribute_count() << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}