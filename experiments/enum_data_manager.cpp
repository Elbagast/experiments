#include "enum_data_manager.h"

#include <iostream>

void enum_data_manager::test()
{
    std::cout << "Enum Data Manager" << std::endl << std::endl;

    MultiDataManager mdm{};
    mdm.set_value<DataEnum::Int>(1, 5);
    std::cout << mdm.get_value<DataEnum::Int>(1) << std::endl;
    std::cout << mdm.get_value<int>(1) << std::endl;

    mdm.set_value<bool>(2, false);
    std::cout << mdm.get_value<DataEnum::Bool>(2) << std::endl;
    std::cout << mdm.get_value<bool>(2) << std::endl;
    std::cout << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}