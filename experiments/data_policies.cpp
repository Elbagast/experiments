#include "data_policies.h"
#include <iostream>
#include <string>

namespace
{
	template <typename T>
	using Unconstrained_Data = data_policies::Data < T, data_policies::policies::storage::Local_Value<T>, data_policies::policies::constraints::Unconstrained<T> >;

	template <typename T>
	using Constrained_Data = data_policies::Data < T, data_policies::policies::storage::Local_Value<T>, data_policies::policies::constraints::Number_Range<T> >;
}

void data_policies::test()
{

	std::cout << std::endl;
	std::cout << "Data Policies" << std::endl << std::boolalpha;
	std::cout << std::endl;

	Unconstrained_Data<float> ud_float{};
	ud_float.set(5.1);
	std::cout << "Unconstrained_Data<float>" << std::endl;
	std::cout << "get = " << ud_float.get() << std::endl;
	std::cout << "is_constrained = " << ud_float.is_constrained() << std::endl;
	std::cout << "is_fundamental = " << ud_float.is_fundamental() << std::endl; // works
	std::cout << std::endl;

	Unconstrained_Data<std::string> ud_string{};
	ud_string.set("Weeee stuff goes here!");
	std::cout << "Unconstrained_Data<std::string>" << std::endl;
	std::cout << "get = " << ud_string.get() << std::endl;
	std::cout << "is_constrained = " << ud_string.is_constrained() << std::endl;
	std::cout << "is_fundamental = " << ud_string.is_fundamental() << std::endl; // works
	std::cout << std::endl;

	Constrained_Data<int> cd_int{};
	cd_int.set_min(0);
	cd_int.set_max(100);
	cd_int.set(12);
	std::cout << "Constrained_Data<int>" << std::endl;
	std::cout << "get = " << cd_int.get() << std::endl;
	std::cout << "is_constrained = " << cd_int.is_constrained() << std::endl;
	std::cout << "get_min = " << cd_int.get_min() << std::endl;
	std::cout << "get_max = " << cd_int.get_max() << std::endl;
	std::cout << "is_within_range(43) = " << cd_int.is_within_range(43) << std::endl;
	std::cout << "is_fundamental = " << cd_int.is_fundamental() << std::endl; // works
	std::cout << std::endl;

	Constrained_Data<std::string> cd_string{};
	std::cout << "Constrained_Data<std::string>" << " - fails to compile (what we want)"<< std::endl;
	std::cout << std::endl;

	std::cout << std::noboolalpha;
}