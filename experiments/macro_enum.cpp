#include "macro_enum.h"

#include <iostream>

#define TEST_ENUM_STRING(_Enum_Class, _Enum_Value) \
std::cout << "Enum_Value_String<"###_Enum_Class##", "###_Enum_Class##"::"###_Enum_Value##">::is_specialised = \"" << Enum_Value_String<_Enum_Class, _Enum_Class##::##_Enum_Value>::is_specialised << "\"" << std::endl; \
std::cout << "Enum_Value_String<"###_Enum_Class##", "###_Enum_Class##"::"###_Enum_Value##">()() = \"" << Enum_Value_String<_Enum_Class, _Enum_Class##::##_Enum_Value>()() << "\"" << std::endl; \
std::cout << "Enum_String<"###_Enum_Class##">()("###_Enum_Class##"::"###_Enum_Value##")= \"" << Enum_String<_Enum_Class>()(_Enum_Class##::##_Enum_Value) << "\"" << std::endl; \
std::cout << std::endl;

#define TEST_ENUM_FULL_STRING(_Enum_Class, _Enum_Value) \
std::cout << "Enum_Value_Full_String<"###_Enum_Class##", "###_Enum_Class##"::"###_Enum_Value##">::is_specialised = \"" << Enum_Value_Full_String<_Enum_Class, _Enum_Class##::##_Enum_Value>::is_specialised << "\"" << std::endl; \
std::cout << "Enum_Value_Full_String<"###_Enum_Class##", "###_Enum_Class##"::"###_Enum_Value##">()() = \"" << Enum_Value_Full_String<_Enum_Class, _Enum_Class##::##_Enum_Value>()() << "\"" << std::endl; \
std::cout << "Enum_Full_String<"###_Enum_Class##">()("###_Enum_Class##"::"###_Enum_Value##")= \"" << Enum_Full_String<_Enum_Class>()(_Enum_Class##::##_Enum_Value) << "\"" << std::endl; \
std::cout << std::endl;


void macro_enum::test()
{
    std::cout << "Macro Enum Class Test" << std::endl << std::endl;
    std::cout << std::boolalpha;

    //TEST_MACRO_ENUM_CLASS(Example_Enum, Foo)
   // TEST_MACRO_ENUM_CLASS(Example_Enum, Bar)

    TEST_ENUM_STRING(Example_Enum, Foo)
    TEST_ENUM_STRING(Example_Enum, Bar)
    TEST_ENUM_STRING(Example_Enum, FooBar)

    TEST_ENUM_FULL_STRING(Example_Enum, Foo)
    TEST_ENUM_FULL_STRING(Example_Enum, Bar)
    TEST_ENUM_FULL_STRING(Example_Enum, FooBar)

    std::cout << Enum_Do_Stuff()(Example_Enum::Foo, " there be poop") << std::endl;
    std::cout << Enum_Do_Stuff2()(Example_Enum::Foo) << std::endl;



    std::cout << std::noboolalpha;
    std::cout << "----------------------------------------" << std::endl;
}