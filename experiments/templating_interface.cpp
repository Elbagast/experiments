#include "templating_interface.hpp"

#include <iostream>
#include <exception>

void templating_interface::test()
{
	std::cout << "Templating Interface Test" << std::endl << std::endl;
	using namespace changed_to;

	using Abstract_Test_Type = Abstract_Big_Thing<Foo, Bar>;
	using Test_Type = Big_Thing<Foo, Bar>;

	try
	{

	//Abstract_Test_Type l_test1{};
	Test_Type l_test2{};
	//Abstract_Test_Type& l_test3 = l_test2;

	std::cout << "here" << std::endl;


	Foo l_foo{};
	Bar l_bar{};

	auto l_foo0 = l_test2.use_index(Index_Tag<0>(), l_foo);
	auto l_foo1 = l_test2.use_index(Index_Tag<1>(), l_foo);

	auto l_bar0 = l_test2.use_index(Index_Tag<0>(), l_bar);
	auto l_bar1 = l_test2.use_index(Index_Tag<1>(), l_bar);


	Thing_User l_test99{};
	l_test99.f();

	}
	catch (std::exception& a_exception)
	{
		std::cout << a_exception.what() << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;
}