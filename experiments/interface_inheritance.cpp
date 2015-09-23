#include "interface_inheritance.h"

#include <iostream>

void interface_inheritance::part1::test()
{
    std::cout << "Interface Inheritance Test Part 1" << std::endl << std::endl;

    Final object{};
    std::cout << "Final&.base_func() = " << object.base_func() << std::endl;
    std::cout << "Final&.part1_func() = " << object.part1_func() << std::endl;
    std::cout << "Final&.part2_func() = " << object.part2_func() << std::endl;

    IFinal& interface_reference{ object };
    std::cout << "IFinal&.base_func() = " << interface_reference.base_func() << std::endl;
    std::cout << "IFinal&.Interface1_func() = " << interface_reference.part1_func() << std::endl;
    std::cout << "IFinal&.part2_func() = " << interface_reference.part2_func() << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}

void interface_inheritance::part2::test()
{
    std::cout << "Interface Inheritance Test Part 2" << std::endl << std::endl;
    
    Final<float> float_object{};
    std::cout << "Final<float> float_object{};" << std::endl;
    std::cout << "Final<float>&.base_func() = " << float_object.base_func() << std::endl;
    std::cout << "Final<float>&.part1_func() = " << float_object.part1_func() << std::endl;
    std::cout << "Final<float>&.part2_func() = " << float_object.part2_func() << std::endl;

    // These don't work because they don't exist
    //std::cout << "Final<float>&.part1_int_func() = " << float_object.part1_int_func() << std::endl;
    //std::cout << "Final<float>&.part2_int_func() = " << float_object.part2_int_func() << std::endl;
    std::cout << std::endl;

    IFinal<float>& float_interface_reference{ float_object };
    std::cout << "IFinal<float>& float_interface_reference{ float_object };" << std::endl;
    std::cout << "IFinal<float>&.base_func() = " << float_interface_reference.base_func() << std::endl;
    std::cout << "IFinal<float>&.part1_func() = " << float_interface_reference.part1_func() << std::endl;
    std::cout << "IFinal<float>&.part2_func() = " << float_interface_reference.part2_func() << std::endl;
    std::cout << std::endl;

    Final<int> int_object{};
    std::cout << "Final<int> int_object{};" << std::endl;
    std::cout << "Final<int>&.base_func() = " << int_object.base_func() << std::endl;
    std::cout << "Final<int>&.part1_func() = " << int_object.part1_func() << std::endl;
    std::cout << "Final<int>&.part2_func() = " << int_object.part2_func() << std::endl;

    // Additional functions from the specialisation
    std::cout << "Final<int>&.part1_int_func() = " << int_object.part1_int_func() << std::endl;
    std::cout << "Final<int>&.part2_int_func() = " << int_object.part2_int_func() << std::endl;
    std::cout << std::endl;


    IFinal<int>& int_interface_reference{ int_object };
    std::cout << "IFinal<int>& int_interface_reference{ int_object };" << std::endl;
    std::cout << "IFinal<int>&.base_func() = " << int_interface_reference.base_func() << std::endl;
    std::cout << "IFinal<int>&.part1_func() = " << int_interface_reference.part1_func() << std::endl;
    std::cout << "IFinal<int>&.part2_func() = " << int_interface_reference.part2_func() << std::endl;

    std::cout << "IFinal<int>&.part1_int_func() = " << int_object.part1_int_func() << std::endl;
    std::cout << "IFinal<int>&.part2_int_func() = " << int_object.part2_int_func() << std::endl;
    std::cout << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}