#include "variadic_templates.h"

#include <memory>
#include <iostream>

void variadic_templates::test()
{
    std::cout << "Variadic Templates Test" << std::endl << std::endl;

    std::unique_ptr<IElement> thing{ new Concrete_Element() };

    std::cout << thing->attribute_count() << std::endl;


    using tuple = std::tuple < bool, int, std::string > ;
    using tuple_map = std::map < int, tuple >;

    tuple_map test_map{};

    test_map.emplace(5, tuple(false, 123456, "moo"));

    std::cout << get_tuple_element<0, decltype(test_map)>(test_map.find(5)) << std::endl;
    std::cout << get_tuple_element<1, decltype(test_map)>(test_map.find(5)) << std::endl;
    std::cout << get_tuple_element<2, decltype(test_map)>(test_map.find(5)) << std::endl;

    std::cout << Tuple_Map_Helper<decltype(test_map)>::get_tuple_element<0>(test_map.find(5)) << std::endl;
    std::cout << Tuple_Map_Helper<decltype(test_map)>::get_tuple_element<1>(test_map.find(5)) << std::endl;
    std::cout << Tuple_Map_Helper<decltype(test_map)>::get_tuple_element<2>(test_map.find(5)) << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}