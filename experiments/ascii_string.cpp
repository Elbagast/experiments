#include "ascii_string.h"
#include <iostream>

constexpr ascii::Char ascii::operator""_ascii_replace(char a_value)
{
	return make_ascii_char_replace(a_value);
}
constexpr ascii::Char ascii::operator""_ascii_except(char a_value)
{
	return make_ascii_char_except(a_value);
}


ascii::String ascii::operator""_ascii(char const* a_cstring, std::size_t a_length)
{
	if (!is_valid_string(a_cstring, a_length))
	{
		// what happens here?
	}
	return String();
}

constexpr ascii::Char ascii::make_ascii_char_replace(char a_char)
{
	return Char(if_invalid_replace(a_char));
}

constexpr ascii::Char ascii::make_ascii_char_ignore(char a_char)
{
	return Char(if_invalid_ignore(a_char));
}

constexpr ascii::Char ascii::make_ascii_char_except(char a_char)
{
	return Char(if_invalid_except(a_char));
}

// is the given char a 7-bit value?
constexpr bool ascii::is_valid_char(char a_value)
{
	// if the 8th bit is set, then this is not an ascii char
	return !(a_value & 0b10000000);
}

bool ascii::is_valid_cstring(char const* a_cstring)
{
	if (a_cstring != nullptr)
	{
		for (; *a_cstring != '\0'; ++a_cstring)
		{
			if (!is_valid_char(*a_cstring))
			{
				return false;
			}
		}
	}
	return true;
}

bool ascii::is_valid_string(char const* a_string, std::size_t a_length)
{
	for (std::size_t l_index{ 0 }; l_index != a_length; ++l_index, ++a_string)
	{
		if (!is_valid_char(*a_string))
		{
			return false;
		}
	}
	return true;
}

bool ascii::is_valid_std_string(std::string const& a_string)
{
	for (auto l_iterator{ a_string.cbegin() }, l_end{a_string.cend()}; l_iterator != l_end; ++l_iterator)
	{
		if (!is_valid_char(*l_iterator))
		{
			return false;
		}
	}
	return true;
}


constexpr char ascii::if_invalid_replace(char a_value) noexcept
{
	// if the 8th bit is set, then return the char '~', otherwise return the input
	return (a_value & 0b10000000 ? '~' : a_value);
}

constexpr char ascii::if_invalid_ignore(char a_value) noexcept
{
	// return only the first 7 bits
	return (a_value & 0b10000000 ? a_value & 0b01111111 : a_value);
}

constexpr char ascii::if_invalid_except(char a_value)
{
	return (a_value & 0b10000000 ? throw Bad_Char_Input(a_value) : a_value);
	// I can throw an exception in a constexpr?...
}


constexpr ascii::Char::Char(char a_value) :
	m_data{ a_value }
{

}

constexpr ascii::Char::Char() :
	m_data{ 0 }
{

}
constexpr ascii::Char::Char(Char const& a_other) = default;
constexpr ascii::Char::Char(Char && a_other) = default;

char ascii::Char::data() const noexcept
{
	return m_data;
}

ascii::Char::operator char() const
{
	return m_data;
}

ascii::String::String():
	m_data{}
{

}

ascii::String::String(char_type const* a_cstring, size_type a_length):
	m_data{}
{
	m_data.reserve(a_length);
	for (size_type l_index = 0; l_index != a_length; ++l_index, ++a_cstring)
	{
		m_data.push_back(*a_cstring);
	}
}

ascii::String::char_type& ascii::String::at(size_type a_index)
{
	return m_data.at(a_index);
}

ascii::String::char_type const& ascii::String::at(size_type a_index) const
{
	return m_data.at(a_index);
}

std::string ascii::String::to_std_string() const
{
	return std::string{ m_data.cbegin(), m_data.cend() };
}



constexpr ascii::Bad_Char_Input::Bad_Char_Input(char a_char):
	m_char{ a_char }
{
}

constexpr char ascii::Bad_Char_Input::data() const noexcept
{
	return m_char;
}

std::string ascii::Bad_Char_Input::message() const
{
	static std::string const s_message{ "Invalid ascii char value of " };
	return s_message + std::to_string(static_cast<int>(m_char));
}

// Can't stop a compile this way, even though I can throw in a constexpr...
//ascii::Char const exception_test{ ascii::make_ascii_char_except(char(128)) };

void ascii::test()
{
	std::cout << "Ascii String Test" << std::endl << std::endl;

	// make a vector of all char values
	std::vector<char> l_values{};
	l_values.reserve(255);
	char l_value{ 0 };
	do
	{
		l_values.push_back(l_value);
		++l_value;
	} 
	while (l_value != 0);

	std::cout << "char values 0-255 :" << std::endl;
	for (auto l_char : l_values)
	{
		std::cout << l_char;
	}
	std::cout << std::endl << std::endl;

	std::cout << "make_ascii_char_replace(char) :" << std::endl;
	for (auto l_char : l_values)
	{
		std::cout << static_cast<char>(make_ascii_char_replace(l_char));
	}
	std::cout << std::endl << std::endl;

	std::cout << "make_ascii_char_ignore(char) :" << std::endl;
	for (auto l_char : l_values)
	{
		std::cout << static_cast<char>(make_ascii_char_ignore(l_char));
	}
	std::cout << std::endl << std::endl;

	std::cout << "make_ascii_char_except(char) :" << std::endl;
	std::vector<char> l_failed_converts{};
	int l_fail_count{0};
	for (auto l_char : l_values)
	{
		try
		{
			std::cout << static_cast<char>(make_ascii_char_except(l_char));
		}
		catch (Bad_Char_Input& l_exception)
		{
			l_failed_converts.push_back(l_exception.data());
			++l_fail_count;
		}
	}
	std::cout << std::endl << "failed to convert " << l_fail_count  << " chars : " << std::endl;
	for (auto l_char : l_failed_converts)
	{
		std::cout << l_char;
	}
	std::cout << std::endl << std::endl;


	std::cout << "----------------------------------------" << std::endl;
}