#ifndef ASCII_STRING_H
#define ASCII_STRING_H

/*
Test of requirements for string classes, starting with an ascii string.

Requirements:
- Char and String can never have incorrect data for the given encoding.
- User can select how to deal with incorrect input data.
- Interface as close to std::string as possible.
- Read access to raw data so that they can be used with old apis.
- Want to have some means of safely using the class with string literals

Have Learned:
- If we have invalid inputs the output needs to be consistent.
	- replace with a fixed value or throw an exception
- Custom literals are a pain to make.
*/
#include <string>
#include <vector>

namespace ascii
{
	class Char;
	class String;
	class Bad_Char_Input;

	// Custom string literals to force ascii characters.
	constexpr Char operator""_ascii_replace(char a_value);
	constexpr Char operator""_ascii_except(char a_value);
	String operator""_ascii(char const* a_cstring, std::size_t a_length);

	constexpr Char make_ascii_char_replace(char a_char);
	constexpr Char make_ascii_char_ignore(char a_char);
	constexpr Char make_ascii_char_except(char a_char);

	// is the given char a 7-bit value?
	constexpr bool is_valid_char(char a_value);

	bool is_valid_cstring(char const* a_cstring);
	bool is_valid_string(char const* a_string, std::size_t a_length);
	bool is_valid_std_string(std::string const& a_string);

	// if a_value > 128 then return '~'
	constexpr char if_invalid_replace(char a_value) noexcept;
	// if  a_value > 128 then return a_value - 128
	// (this one seems to be a garbage conversion...)
	constexpr char if_invalid_ignore(char a_value) noexcept;
	// if a_value > 128 throw an exception containing the value
	constexpr char if_invalid_except(char a_value);
	


	class Char
	{
	private:
		// Allow only these functions to use this constructor
		friend constexpr Char make_ascii_char_replace(char);
		friend constexpr Char make_ascii_char_ignore(char);
		friend constexpr Char make_ascii_char_except(char);
		explicit constexpr Char(char a_value);
	public:
		constexpr Char();
		constexpr Char(Char const& a_other);
		constexpr Char(Char && a_other);

		char data() const noexcept;

		explicit operator char() const;

	private:
		char m_data;
	};

	class String
	{
	public:
		using char_type = Char;
		using size_type = std::size_t;
		
		String();
		String(char_type const* a_cstring, size_type a_size);
		template <typename Iter>
		String(Iter a_begin, Iter a_end):
			m_data{ a_begin , a_end }
		{
		}

		char_type& at(size_type a_index);
		char_type const& at(size_type a_index) const;

		std::string to_std_string() const;
	private:
		std::vector<Char> m_data;
	};

	class Bad_Char_Input
	{
	public:
		constexpr Bad_Char_Input(char a_char);

		constexpr char data() const noexcept;
		std::string message() const;
	private:
		char m_char;
	};

	void test();
}

#endif
