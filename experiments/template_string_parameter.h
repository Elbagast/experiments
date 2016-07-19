#ifndef TEMPLATE_STRING_PARAMETER_H
#define TEMPLATE_STRING_PARAMETER_H

#include <tuple>
#include <array>
/*
Is it possible to make a string into a template parameter?
This is possible:

template <char C>
class Single_Char;

And so is this:

template <char C...>
class Char_Tuple;

So can we take a string imbed it into the template something like this:

template <char const* C>
class Char_Array;

Basically we want something that is as close to this declaration as possible:

Some_Type<"string literal", Other_Type> l_value{};

So maybe a macro like this:
Some_Type<LITERAL_CLASS("string literal"), Other_Type> l_value{};

*/

namespace template_string_parameter
{
	// Capture a char from a template parameter
	template <char C>
	struct Char_Single
	{
		static constexpr char const value{ C };
	};
	
	// Creates a null terminated char array based on the supplied chars
	// e.g.
	// Char_Array<'M','o','o'>::value == char const[4]{ "Moo\0" }
	template <char... C>
	struct Char_Array
	{
		static constexpr std::size_t const size{ sizeof...(C) };

		static constexpr char const value[size + 1]{ C... , '\0' };
	};

	// So can we get from char const[] to this?
	// or from constexpr char const* to this?




	#define DECLTYPE_C_STRING_CLASS(_arg) C_String_##_arg

	#define C_STRING_CLASS(_arg) struct C_String_##_arg { static constexpr char const value[sizeof(#_arg)/sizeof(char)]{ #_arg }; };

	


	//C_STRING_CLASS(mooo)

	/*
	template <std::size_t N>
	constexpr decltype(auto) get_array(char const[N] a_literal)
	{
		return std::array<char, N>{ a_literal };
	}
	*/

	constexpr std::size_t string_literal_length(const char* a_str)
	{
		return *a_str != 0 ? 1 + string_literal_length(++a_str) : 0;
	}

	struct String_Literal
	{
		constexpr String_Literal(char const* a_value) : value{ a_value }, size{ string_literal_length(a_value) } {}
		constexpr String_Literal(char const* a_value, std::size_t a_size) : value{ a_value }, size{ a_size } {}
		
		char const* value;
		std::size_t const size;
	};
	
	// Now have constexpr access to a string literal and it's size

	void test();
}

//template <char C...>
//std::tuple<C...> template_string_parameter::Char_Tuple::values{ C... };

#endif //TEMPLATE_STRING_PARAMETER_H