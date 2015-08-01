#include "abstract_interface_test.h"
#include <memory>
#include <iostream>

abstract_interface_test::Base_Class::~Base_Class() = default;
abstract_interface_test::Interface_Class::~Interface_Class() = default;

/*
bool abstract_interface_test::Interface_Class::func()
{
    return false;
}
*/

bool abstract_interface_test::Derived_Class::func()
{
    return true;
}

void abstract_interface_test::test()
{
    std::cout << "Abstract Interface Test" << std::endl << std::endl;

    // make a Derived_Class ptr stored as a Base_Class ptr
    std::unique_ptr<Base_Class> polymorphic_ptr{new Derived_Class};

    // cast to Derived_Class to access the interface
    std::cout << "Cast to Derived_Class then call func(): " << dynamic_cast<Derived_Class*>(polymorphic_ptr.get())->func() << std::endl;

    // cast to Interface_Class to access the interface
    std::cout << "Cast to Interface_Class then call func(): " << dynamic_cast<Interface_Class*>(polymorphic_ptr.get())->func() << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}