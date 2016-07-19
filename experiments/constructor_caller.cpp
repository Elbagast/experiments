#include "constructor_caller.h"

#include <iostream>

namespace
{
	struct Thing
	{
		int m_1;
		int m_2;
		int m_3;

		Thing() :
			m_1{ 1 },
			m_2{ 2 },
			m_3{ 3 }
		{}
		Thing(int a_1, int a_2, int a_3) :
			m_1{ a_1 },
			m_2{ a_2 },
			m_3{ a_3 }
		{}

		Thing(Thing const& a_other) = default;
		Thing& operator=(Thing const& a_other) = default;

		Thing(Thing && a_other) = default;
		Thing& operator=(Thing && a_other) = default;
		
	};
}


void constructor_caller::test()
{
	std::cout << "Constructor Caller Test" << std::endl << std::endl;

	auto a = Default_Constructor<Thing>()();
	auto b = Constructor<Thing>()();
	auto c = Constructor<Thing, int, int, int>()(4, 5, 6);

	auto d = Copy_Constructor<Thing>()(a);
	auto e = Move_Constructor<Thing>()(std::move(d));

	auto f = Constructor<Thing, Thing const&>()(a);
	auto g = Constructor<Thing, Thing &&>()(std::move(f));

	// These get converted to int so they work
	auto h = Constructor < Thing, long long, long long, long long>()(4, 5, 6);
	auto i = Constructor < Thing, float, float, float>()(4.0f, 5.0f, 6.0f);

	// Not having enough arguments fails to compile
	//auto j = Constructor < Thing, int, int>()(4, 5);

	// Having at leas one arguemnt that cannot be implicitly converted fails to compile
	//auto k = Constructor < Thing, void*, void*, void*>()(nullptr, nullptr, nullptr);
	//auto l = Constructor < Thing, int, void*, void*>()(4, nullptr, nullptr);
	//auto m = Constructor < Thing, int, int, void*>()(4, 5, nullptr);

	std::cout << "----------------------------------------" << std::endl;
}