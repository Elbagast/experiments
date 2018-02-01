#include "lambda_class.h"
#include <functional>
#include <iostream>

namespace
{
	template <typename T>
	T returner();


	template <typename T, decltype(&returner<T>) T_Func>
	class Outputter
	{
	public:
		void operator()()
		{
			std::cout << "value is '" << (*T_Func)() << "'" << std::endl;
		}
	};

	int some_int()
	{
		return 7;
	}
}


void lambda_class::test()
{
	std::cout << "Lambda Class Test" << std::endl << std::endl;
	
	Outputter<int, some_int>()();

	auto bar_func =  [](){ return "bar"; };
	using bar_func_type = decltype(bar_func);

	// turns out this was a fantasy
	//Outputter<bar_func_type> ()();
		
	//Outputter<decltype([]() {return "foo"; }) > ()();


	std::cout << "----------------------------------------" << std::endl;
}
