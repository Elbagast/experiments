
namespace typedef_testing
{
    namespace internal
    {
        char const diff_array[2]{};
        auto const diff = &diff_array[1] - &diff_array[0];
    }
    using size_t = decltype(sizeof(void*));
    using nullptr_t = decltype(nullptr);
    using ptrdiff_t = decltype(internal::diff);
}

// test of typedefs
#include <cstdint>
namespace fixed_int_test
{
	using int8_t = std::int8_t;
	using int16_t = std::int16_t;
	using int32_t = std::int32_t;
	using int64_t = std::int64_t;

	using int_fast8_t = std::int_fast8_t;
	using int_fast16_t = std::int_fast16_t;
	using int_fast32_t = std::int_fast32_t;
	using int_fast64_t = std::int_fast64_t;

	using int_least8_t = std::int_least8_t;
	using int_least16_t = std::int_least16_t;
	using int_least32_t = std::int_least32_t;
	using int_least64_t = std::int_least64_t;

	using intmax_t = std::intmax_t;
	using intptr_t = std::intptr_t;

	using uint8_t = std::uint8_t;
	using uint16_t = std::uint16_t;
	using uint32_t = std::uint32_t;
	using uint64_t = std::uint64_t;

	using uint_fast8_t = std::uint_fast8_t;
	using uint_fast16_t = std::uint_fast16_t;
	using uint_fast32_t = std::uint_fast32_t;
	using uint_fast64_t = std::uint_fast64_t;

	using uint_least8_t = std::uint_least8_t;
	using uint_least16_t = std::uint_least16_t;
	using uint_least32_t = std::uint_least32_t;
	using uint_least64_t = std::uint_least64_t;

	using uintmax_t = std::uintmax_t;
	using uintptr_t = std::uintptr_t;
}

#include "enum_stuff.h"
#include "integer_id.h"
#include "enum_data_manager.h"
#include "data_pool_value.h"
#include "enum_in_class.h"
#include "grid.h"
#include "object_manager.h"
#include "member_templates.h"
#include "abstract_interface_test.h"
#include "fake_virtual_functions.h"
#include "interface_operators.h"
#include "data_policies.h"
#include "enum_stuff2.h"
#include "variadic_templates.h"
#include "reference_counting.h"
#include "indexable_tuple.h"
#include "question_based_template.h"
#include "std_basic_string_identifier.h"
#include "interface_inheritance.h"
#include "macro_class.h"
#include "macro_enum.h"
#include "function_traits.h"
#include "explicit_template_instantiation_test.h"
#include "templated_observer.h"
#include "pointer_identification.h"
#include "bit_radians.h"
#include "template_string_parameter.h"
#include "constructor_caller.h"
#include "ascii_string.h"
#include "iterator_properties.h"

#include <string>


void string_literals_test()
{
	using namespace std::string_literals; // enables s-suffix for std::string literals

	// Character literals
	auto c0 = 'A'; // char
	auto c1 = u8'A'; // char
	auto c2 = L'A'; // wchar_t
	auto c3 = u'A'; // char16_t
	auto c4 = U'A'; // char32_t

					// String literals
	auto s0 = "hello"; // const char*
	auto s1 = u8"hello"; // const char*, encoded as UTF-8
	auto s2 = L"hello"; // const wchar_t*
	auto s3 = u"hello"; // const char16_t*, encoded as UTF-16
	auto s4 = U"hello"; // const char32_t*, encoded as UTF-32

						// Raw string literals containing unescaped \ and "
	auto R0 = R"("Hello \ world")"; // const char*
	auto R1 = u8R"("Hello \ world")"; // const char*, encoded as UTF-8
	auto R2 = LR"("Hello \ world")"; // const wchar_t*
	auto R3 = uR"("Hello \ world")"; // const char16_t*, encoded as UTF-16
	auto R4 = UR"("Hello \ world")"; // const char32_t*, encoded as UTF-32

									 // Combining string literals with standard s-suffix
	auto S0 = "hello"s; // std::string
	auto S1 = u8"hello"s; // std::string
	auto S2 = L"hello"s; // std::wstring
	auto S3 = u"hello"s; // std::u16string
	auto S4 = U"hello"s; // std::u32string

						 // Combining raw string literals with standard s-suffix
	auto S5 = R"("Hello \ world")"s; // std::string from a raw const char*
	auto S6 = u8R"("Hello \ world")"s; // std::string from a raw const char*, encoded as UTF-8
	auto S7 = LR"("Hello \ world")"s; // std::wstring from a raw const wchar_t*
	auto S8 = uR"("Hello \ world")"s; // std::u16string from a raw const char16_t*, encoded as UTF-16
	auto S9 = UR"("Hello \ world")"s; // std::u32string from a raw const char32_t*, encoded as UTF-32


									  // ASCII smiling face
	const char*     ss1 = ":-)";

	// UTF-16 (on Windows) encoded WINKING FACE (U+1F609)
	const wchar_t*  ss2 = L"😉 = \U0001F609 is ;-)";

	// UTF-8  encoded SMILING FACE WITH HALO (U+1F607)
	const char*     ss3 = u8"😇 = \U0001F607 is O:-)";

	// UTF-16 encoded SMILING FACE WITH OPEN MOUTH (U+1F603)
	const char16_t* ss4 = u"😃 = \U0001F603 is :-D";

	// UTF-32 encoded SMILING FACE WITH SUNGLASSES (U+1F60E)
	const char32_t* ss5 = U"😎 = \U0001F60E is B-)";
}


template <typename T>
T default_construct()
{
	return T();
};

template <typename T>
decltype(auto) auto_test()
{
	return default_construct<T>();
}


int main(int argc, char* argv[])
{
    /*
    Char_Type<'A'> a;
    Char_Type<'b'> b;
    std::cout << a.m_char << std::endl;
    std::cout << b.m_char << std::endl;

    


    ref_ptr<int> refptrtest1 = new int;
    ref_ptr<int const> refptrtest2 = new int;
    ref_ptr<int> const refptrtest3 = new int;
    ref_ptr<int const> const refptrtest4 = new int;

    *refptrtest1 = 1;
    //*refptrtest2 = 2;
    *refptrtest3 = 3;
    //*refptrtest4 = 4;

    delete refptrtest1;
    delete refptrtest2;
    delete refptrtest3;
    delete refptrtest4;
    */

    grid::test();

    enum_in_class::test();

    enum_stuff::test();

    enum_data_manager::test();

    data_pool_value::test();

    // This has been superceeded by reference_counting which is a later version 
    object_manager::test();

    integer_id::test();

    member_templates::test();

    abstract_interface_test::test();

    fake_virtual_functions::test();

    interface_operators::test();

    data_policies::test();

    enum_stuff2::test();

    variadic_templates::test();

    reference_counting::test();

    indexable_tuple::test();

    question_based_template::test();

    std_basic_string_identifier::test();

    interface_inheritance::part1::test();
    interface_inheritance::part2::test();

    macro_class::test();

    macro_enum::test();

    function_traits::test();

    explicit_template_instantiation::test();

    templated_observer::test();

    pointer_identification::test();

    //bit_radians::test();

	template_string_parameter::test();

	constructor_caller::test();

	ascii::test();

	iterator_properties::test();


	auto l_int = auto_test<int>();



    return 0;
}