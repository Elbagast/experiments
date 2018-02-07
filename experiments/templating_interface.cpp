#include "templating_interface.hpp"

#include <iostream>
#include <exception>

void templating_interface::test()
{
	std::cout << "Templating Interface Test" << std::endl << std::endl;
	using namespace changed_to;

	using Abstract_Test_Type = Abstract_Big_Thing<Foo, Bar>;
	using Test_Type = Big_Thing<Foo, Bar>;

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

	using namespace again;

	Final<Foo,Bar> a_final{};
	A_Final<Foo, Bar>& a_afinal{ a_final };



	a_final.base_func();
	a_final.shared_func(nullptr);
	a_final.data_func(Tag<Foo>());
	a_final.data_func(Tag<Bar>());
	a_final.member_func(again::Index_Tag<0>(), l_foo);
	a_final.member_func(again::Index_Tag<1>(), l_foo);
	a_final.member_func(again::Index_Tag<2>(), l_foo);
	//a_final.member_func(again::Index_Tag<3>(), l_foo);
	a_final.member_func(again::Index_Tag<0>(), l_bar);
	a_final.member_func(again::Index_Tag<1>(), l_bar);
	a_final.member_func(again::Index_Tag<2>(), l_bar);
	a_final.member_func(again::Index_Tag<3>(), l_bar);
	//a_final.member_func(again::Index_Tag<4>(), l_bar);

	// DUN DUN DUN


	std::cout << "----------------------------------------" << std::endl;
}