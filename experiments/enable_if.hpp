#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

#include <type_traits>
#include <iostream>

/*
Figuring out how to use std::enable_if
*/

namespace enable_if
{
	class Default
	{
	public:
		Default() = default;
	};
	class Non_Default
	{
	public:
		Non_Default() = delete;
	};

	class Explicit
	{
	private:
		int m_int;
	public:
		explicit Explicit(int a) : m_int{ a } 
		{
			std::cout << "Explicit::Explicit(int)" << std::endl;
		}
	};

	class Implicit
	{
	private:
		int m_int;
	public:
		Implicit(int a) : m_int{ a }
		{
			std::cout << "Implicit::Implicit(int)" << std::endl;
		}
	};

	template <typename T>
	class Tester
	{
	private:
		T m_data;
	public:

		// default construct only if available
		// this bit is doing its job
		template <typename = std::enable_if_t<std::is_default_constructible_v<T>> >
		Tester() :
			m_data{}
		{
			std::cout << "Tester<T>::Tester()" << std::endl;
		}
		
		// construct from T
		explicit Tester(T const& a_data) :
			m_data{ a_data }
		{
			std::cout << "Tester<T>::explicit Tester(T const&)" << std::endl;
		}
		
		// construct from something T can construct from
		// Hmm. in this case the compiler seems to do the implicit type conversion beforehand
		template
		<
			typename U, 
			typename = std:enable_if_t
			<
				//!std::is_same_V< T, U > &&// U is not T
				!std::is_base_of_v< Tester<T>, std::decay_t<U> > // U is not Tester<T> or derived from it
				&& std::is_constructible_v<T,U&&> // T can be made from U
				&& std::is_convertible_v<U&&, T>
			>
		>
		explicit Tester(U&& a_data) :
			m_data{ std::forward<U>(a_data) }
		{
			std::cout << "Tester<T>::explicit Tester<U>(U&&)" << std::endl;
		}
		/*
		template
		<
			typename U,
			typename = std:enable_if_t
			<
				!std::is_base_of_v< Tester<T>, std::decay_t<U> > // U is not Tester<T> or derived from it
				&& std::is_constructible_v<T, U&&> // T can be made from U
				&& !std::is_convertible_vnstructible_v<U&&,T>
			>
		>
		Tester(U&& a_data) :
			m_data{ std::forward<U>(a_data) }
		{
			std::cout << "Tester<T>::Tester<U>(U&&)" << std::endl;
		}
		*/

		Tester(Tester const& a_other) :
			m_data{ a_other.m_data }
		{
			std::cout << "Tester<T>::Tester(Tester<T> const&)" << std::endl;
		}
		Tester(Tester&& a_other) :
			m_data{ std::move(a_other.m_data) }
		{
			std::cout << "Tester<T>::Tester(Tester<T> &&)" << std::endl;
		}
		
		~Tester()
		{
			std::cout << "Tester<T>::~Tester()" << std::endl;
		}
	};

	void test();

} // abstract_interface_test


#endif // ENABLE_IF_HPP
