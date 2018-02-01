#include "object_address.h"

#include <iostream>

/*
Some tests on references and pointers with regards to object locations, mostly
for establising what we should be using when tracking objects in certain ways.
*/

namespace
{
	class Thing
	{
	public:
		Thing() : m_value{ 0 } {}
		explicit Thing(int a_value) : m_value{ a_value } {}
		~Thing() = default;
		Thing(Thing const&) = default;
		Thing& operator=(Thing const&) = default;
		Thing(Thing && a_other) : 
			m_value{ std::move(a_other.m_value) }
		{
			a_other.m_value = 0;
		}
		Thing& operator=(Thing && a_other)
		{
			m_value = a_other.m_value;
			a_other.m_value = 0;
			return *this;
		}




		int value() const { return m_value; }
	private:
		int m_value;
	};

	std::ostream& operator<<(std::ostream& a_ostream, Thing const& a_thing)
	{
		return a_ostream << a_thing.value();
	}

}



void object_address::test()
{
	std::cout << "Object Address" << std::endl << std::endl;


	{
		Thing l_var1{ 12345 };
		Thing& l_ref1{ l_var1 };
		Thing* l_ptr1{ &l_var1 };

		std::cout << "Thing 1:"  << std::endl;

		std::cout << "Thing =             " << l_var1 << std::endl;
		std::cout << "Thing address =     " << std::addressof(l_var1) << std::endl;
		std::cout << "Thing& address =    " << std::addressof(l_ref1) << std::endl;
		std::cout << "Thing* address =    " << std::addressof(l_ptr1) << std::endl;
		std::cout << "*(Thing*) address = " << std::addressof(*l_ptr1) << std::endl;
		std::cout << std::endl;

		{
			Thing l_var2{std::move(l_var1)};
			Thing& l_ref2{ l_var2 };
			Thing* l_ptr2{ &l_var2 };

			std::cout << "after move from Thing 1 to Thing 2" << std::endl << std::endl;

			std::cout << "Thing 1:" << std::endl;
			std::cout << "Thing =             " << l_var1 << std::endl;
			std::cout << "Thing address =     " << std::addressof(l_var1) << std::endl;
			std::cout << "Thing& address =    " << std::addressof(l_ref1) << std::endl;
			std::cout << "Thing* address =    " << std::addressof(l_ptr1) << std::endl;
			std::cout << "*(Thing*) address = " << std::addressof(*l_ptr1) << std::endl;
			std::cout << std::endl;
			
			std::cout << "Thing 2:" << std::endl;
			std::cout << "Thing =             " << l_var2 << std::endl;
			std::cout << "Thing address =     " << std::addressof(l_var2) << std::endl;
			std::cout << "Thing& address =    " << std::addressof(l_ref2) << std::endl;
			std::cout << "Thing* address =    " << std::addressof(l_ptr2) << std::endl;
			std::cout << "*(Thing*) address = " << std::addressof(*l_ptr2) << std::endl;
			std::cout << std::endl;


			l_var1 = std::move(l_var2);

			std::cout << "after move assign Thing 1 to Thing 2" << std::endl << std::endl;

			std::cout << "Thing 1:" << std::endl;
			std::cout << "Thing =             " << l_var1 << std::endl;
			std::cout << "Thing address =     " << std::addressof(l_var1) << std::endl;
			std::cout << "Thing& address =    " << std::addressof(l_ref1) << std::endl;
			std::cout << "Thing* address =    " << std::addressof(l_ptr1) << std::endl;
			std::cout << "*(Thing*) address = " << std::addressof(*l_ptr1) << std::endl;
			std::cout << std::endl;

			std::cout << "Thing 2:" << std::endl;
			std::cout << "Thing =             " << l_var2 << std::endl;
			std::cout << "Thing address =     " << std::addressof(l_var2) << std::endl;
			std::cout << "Thing& address =    " << std::addressof(l_ref2) << std::endl;
			std::cout << "Thing* address =    " << std::addressof(l_ptr2) << std::endl;
			std::cout << "*(Thing*) address = " << std::addressof(*l_ptr2) << std::endl;
			std::cout << std::endl;

		}
		/*
		A reference points to an object's location regardless of state. This is why returning a
		reference to a value that is only inside a function's scope is a dumb thing to do.

		Suddenly I'm not sure what I was testing here...

		If an object needs to communicate with another then that other object has to not be
		destroyed before it, regardless of whether it's accessed by a reference or a pointer.
		*/
	}

	std::cout << "----------------------------------------" << std::endl;
}