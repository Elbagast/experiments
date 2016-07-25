#include "template_string_parameter.h"
#include <iostream>

void template_string_parameter::test()
{
	std::cout << "Template String Paramter Test" << std::endl << std::endl;

	std::cout << Char_Single<'A'>::value << std::endl;

	using array_type = Char_Array<'A', 'B', 'C'>;
	std::cout << array_type::value << std::endl;
	std::cout << array_type::value[0] << std::endl;
	std::cout << array_type::value[1] << std::endl;
	std::cout << array_type::value[2] << std::endl;
	std::cout << array_type::value[3] << std::endl;
	std::cout << array_type::size << std::endl;

	//std::cout << get_array("moo").get() << std::endl;

	//auto ca = "mooooo"_ca;

	std::cout << "----------------------------------------" << std::endl;
}