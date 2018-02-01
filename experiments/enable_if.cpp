#include "enable_if.hpp"

#include <string>
#include <tuple>

namespace enable_if
{
	class Reporting
	{
	private:
		int m_int;
		std::string m_string;
	public:
		Reporting() :
			m_int{ 0 },
			m_string{}
		{
			std::cout << "Reporting()" << std::endl;
		}
		

		template 
		<
			typename T, 
			std::enable_if_t
			<
			!std::is_base_of_v< Reporting, std::decay_t<T> >
			&& !std::is_integral_v<std::remove_reference_t<T>>
			//&& std::is_constructible_v<std::string, T>
			>
		>
		explicit  Reporting(T&& a) :
			m_int{ 0 },
			m_string{ std::forward<T>(a) }
		{
			static_assert(std::is_constructible_v<std::string, T>, "bad parameter");
			std::cout << "explicit Reporting(T&&)" << std::endl;
		}
		
		explicit Reporting(std::string const& a) :
			m_int{ 0 },
			m_string{ a }
		{
			std::cout << "explicit Reporting(std::string const&)" << std::endl;
		}

		explicit Reporting(int a) :
			m_int{ a },
			m_string{}
		{
			std::cout << "explicit Reporting(int)" << std::endl;
		}

		Reporting(Reporting const& a) :
			m_int{ a.m_int },
			m_string{ a.m_string }
		{
			std::cout << "Reporting(Reporting const&)" << std::endl;
		}
		Reporting& operator=(Reporting const& a)
		{
			m_int = a.m_int;
			m_string = a.m_string;
			std::cout << "Reporting& operator=(Reporting const&)" << std::endl;
		}
		
		Reporting(Reporting && a) :
			m_int{ std::move(a.m_int) },
			m_string{ std::move(a.m_string) }
		{
			std::cout << "Reporting(Reporting &&)" << std::endl;
		}

		Reporting& operator=(Reporting && a)
		{
			m_int = std::move(a.m_int);
			m_string = std::move(a.m_string);
			std::cout << "Reporting& operator=(Reporting &&)" << std::endl;
		}

		~Reporting()
		{
			std::cout << "~Reporting()" << std::endl;
		}
	};
}


void enable_if::test()
{
	std::cout << "enable_if Test" << std::endl << std::endl;
	{
		Tester<Default> a{};
		// Cannot compile
		//Tester<Non_Default> b{};
	}
	{
		Tester<int> b( 2 );
		Tester<int> c( b );
		Tester<int> d( std::move(c) );
	}

	{
		Tester<Implicit> a(123);
	}
	{
		//Tester<Explicit> a(123);
		Tester<Explicit> a(Explicit(123));
	}
	{
		Tester<std::string> a{};
	} 
	{
		Tester<std::string> a("abc");
	}
	{
		Tester<std::string> a{ std::string("abc") };
	}


	{
		//Reporting a("abc");
	}

	{
		std::tuple<Reporting, Reporting, Reporting>a{1,2,3};
	}

	{
		//std::tuple<Reporting, Reporting, Reporting>a = std::make_tuple( "a","b","c" );
	}

	std::cout << "----------------------------------------" << std::endl;
}