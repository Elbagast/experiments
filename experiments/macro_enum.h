#ifndef MACRO_ENUM_H
#define MACRO_ENUM_H

/*
Tying an enum to string representations of the enum values
using a bunch of macros to build the code.
*/

#include <string>
#include <type_traits>

namespace macro_enum
{
    template <typename T>
    struct Class_String
    {
        static bool const is_specialised{ false };
        char const* operator()() const { return nullptr; }
    };

#define MACRO_GENERATED_CLASS_STRING(_T) \
    template <> struct Enum_Class_String<_T> \
    { \
        static bool const is_specialised{ true }; \
        char const* operator()() const { return #_T; } \
    };


    // template and macro for easy specialisation
    template <typename T_Enum_Class, T_Enum_Class T_Enum_Value>
    struct Enum_Value_String
    {
        static bool const is_specialised{ false };
        char const* operator()() const { return nullptr; }
    };

#define MACRO_GENERATED_ENUM_STRING(_Enum_Class, _Enum_Value) \
    template <> struct Enum_Value_String<_Enum_Class, _Enum_Class##::##_Enum_Value> \
    { \
        static bool const is_specialised{ true }; \
        char const* operator()() const { return #_Enum_Value; } \
    };

    
    // template and macro for easy specialisation
    template <typename T_Enum_Class, T_Enum_Class T_Enum_Value>
    struct Enum_Value_Full_String
    {
        static bool const is_specialised{ false };
        char const* operator()() const { return nullptr; }
    };

#define MACRO_GENERATED_ENUM_FULL_STRING(_Enum_Class, _Enum_Value) \
    template <> struct Enum_Value_Full_String<_Enum_Class, _Enum_Class##::##_Enum_Value> \
    { \
        static bool const is_specialised{ true }; \
        char const* operator()() const { return #_Enum_Class##"::"###_Enum_Value; } \
    };


    template <typename T_Enum_Class>
    struct Enum_String
    {
        char const* operator() (T_Enum_Class value) const
        {
            switch (value)
            {
            default: return nullptr;
            }
        }
    };

#define MACRO_GENERATED_ENUM_STRING_START(_Enum_Class) \
    template<> struct Enum_String<_Enum_Class> \
    { \
        char const* operator() (_Enum_Class value) const \
        { \
            switch (value) \
            {

#define MACRO_GENERATED_ENUM_STRING_VALUE(_Enum_Class, _Enum_Value) \
            case _Enum_Class##::##_Enum_Value: return Enum_Value_String<_Enum_Class, _Enum_Class##::##_Enum_Value>()();

#define MACRO_GENERATED_ENUM_STRING_DEFAULT() \
            default: return nullptr;

#define MACRO_GENERATED_ENUM_STRING_END() \
            } \
        } \
    };


    template <typename T_Enum_Class>
    struct Enum_Full_String
    {
        char const* operator() (T_Enum_Class value) const
        {
            switch (value)
            {
            default: return nullptr;
            }
        }
    };

#define MACRO_GENERATED_ENUM_FULL_STRING_START(_Enum_Class) \
    template<> struct Enum_Full_String<_Enum_Class> \
    { \
        char const* operator() (_Enum_Class value) const \
        { \
            switch (value) \
            {

#define MACRO_GENERATED_ENUM_FULL_STRING_VALUE(_Enum_Class, _Enum_Value) \
            case _Enum_Class##::##_Enum_Value: return Enum_Value_Full_String<_Enum_Class, _Enum_Class##::##_Enum_Value>()();

#define MACRO_GENERATED_ENUM_FULL_STRING_DEFAULT() \
            default: return nullptr;

#define MACRO_GENERATED_ENUM_FULL_STRING_END() \
            } \
        } \
    };

    enum class Example_Enum
    {
        Foo = 1,
        Bar = 2,
        FooBar = 3
    };

    MACRO_GENERATED_ENUM_STRING(Example_Enum, Foo)
    MACRO_GENERATED_ENUM_STRING(Example_Enum, Bar)
    MACRO_GENERATED_ENUM_STRING(Example_Enum, FooBar)

    MACRO_GENERATED_ENUM_FULL_STRING(Example_Enum, Foo)
    MACRO_GENERATED_ENUM_FULL_STRING(Example_Enum, Bar)
    MACRO_GENERATED_ENUM_FULL_STRING(Example_Enum, FooBar)

    MACRO_GENERATED_ENUM_STRING_START(Example_Enum)
    MACRO_GENERATED_ENUM_STRING_VALUE(Example_Enum, Foo)
    MACRO_GENERATED_ENUM_STRING_VALUE(Example_Enum, Bar)
    MACRO_GENERATED_ENUM_STRING_VALUE(Example_Enum, FooBar)
    MACRO_GENERATED_ENUM_STRING_DEFAULT()
    MACRO_GENERATED_ENUM_STRING_END()

    MACRO_GENERATED_ENUM_FULL_STRING_START(Example_Enum)
    MACRO_GENERATED_ENUM_FULL_STRING_VALUE(Example_Enum, Foo)
    MACRO_GENERATED_ENUM_FULL_STRING_VALUE(Example_Enum, Bar)
    MACRO_GENERATED_ENUM_FULL_STRING_VALUE(Example_Enum, FooBar)
    MACRO_GENERATED_ENUM_FULL_STRING_DEFAULT()
    MACRO_GENERATED_ENUM_FULL_STRING_END()

    template <typename T_Enum_Class, template<T_Enum_Class> class T_Functor_Template, class T_Functor_Default, typename T_Return, typename... T_Args>
    struct Enum_Switch
    {
        T_Return operator() (T_Enum_Class value, T_Args&&... args) const
        {
            switch (value)
            {
            default: return T_Functor_Default()(std::forward<T_Args>(args...));
            }
        }
    };

    template <typename T_Return>
    T_Return make_Enum_Switch()
    {

    }


#define MACRO_GENERATED_ENUM_SWITCH_START(_Enum_Class) \
    template<template<_Enum_Class> class T_Functor_Template, class T_Functor_Default, typename T_Return, typename... T_Args> \
    struct Enum_Switch<_Enum_Class, T_Functor_Template, T_Functor_Default, T_Return, T_Args...> \
    { \
        T_Return operator() (_Enum_Class value, T_Args&&... args) const \
        { \
            switch (value) \
            {

#define MACRO_GENERATED_ENUM_SWITCH_VALUE(_Enum_Class, _Enum_Value) \
            case _Enum_Class##::##_Enum_Value: return T_Functor_Template<_Enum_Class##::##_Enum_Value>()(std::forward<T_Args>(args)...);

#define MACRO_GENERATED_ENUM_SWITCH_DEFAULT() \
            default: return T_Functor_Default()(std::forward<T_Args>(args)...);

#define MACRO_GENERATED_ENUM_SWITCH_STRING_END() \
            } \
        } \
    };
    /*
    template < template<Example_Enum> class T_Functor_Template, class T_Functor_Default, typename T_Return, typename... T_Args>
    struct Enum_Switch<Example_Enum, T_Functor_Template, T_Functor_Default, T_Return, T_Args...>
    {
        T_Return operator() (Example_Enum value, T_Args&&... args) const
        {
            switch (value)
            {
            case Example_Enum::Foo: return T_Functor_Template<Example_Enum::Foo>()(std::forward<T_Args>(args)...);
            case Example_Enum::Bar: return T_Functor_Template<Example_Enum::Bar>()(std::forward<T_Args>(args)...);
            case Example_Enum::FooBar: return T_Functor_Template<Example_Enum::FooBar>()(std::forward<T_Args>(args)...);
            default: return T_Functor_Default()(std::forward<T_Args>(args)...);
            }
        }
    };
    */
    
    MACRO_GENERATED_ENUM_SWITCH_START(Example_Enum)
    MACRO_GENERATED_ENUM_SWITCH_VALUE(Example_Enum, Foo)
    MACRO_GENERATED_ENUM_SWITCH_VALUE(Example_Enum, Bar)
    MACRO_GENERATED_ENUM_SWITCH_VALUE(Example_Enum, FooBar)
    MACRO_GENERATED_ENUM_SWITCH_DEFAULT()
    MACRO_GENERATED_ENUM_SWITCH_STRING_END()
    
    template <Example_Enum T_Enum_Value>
    struct Enum_Do_Stuff_Value
    {
        std::string operator()(std::string const& value) const { return std::string("unspecialised Do_Stuff ") + Enum_Value_String<Example_Enum, T_Enum_Value>()() + " style " + value; }
    };

    template <>
    struct Enum_Do_Stuff_Value<Example_Enum::Foo>
    {
        std::string operator()(std::string const& value) const { return std::string("Do_Stuff for Example_Enum::Foo style ") + value; }
    };

    struct Enum_Do_Stuff_Default
    {
        std::string operator()(std::string const& value) const { return std::string("Do_Stuff_Default" ) + value; }
    };
    
    struct Enum_Do_Stuff
    {
        std::string operator()(Example_Enum value, std::string const& str) const
        {
            return Enum_Switch<Example_Enum, Enum_Do_Stuff_Value, Enum_Do_Stuff_Default, std::string, std::string const&>()(value, str);
        }
    };

    
    template <Example_Enum T_Enum_Value>
    struct Enum_Do_Stuff_Value2
    {
        std::string operator()() const { return std::string("unspecialised Do_Stuff2 ") + Enum_Value_String<Example_Enum, T_Enum_Value>()() + " style "; }
    };

    struct Enum_Do_Stuff_Default2
    {
        std::string operator()() const { return std::string("Do_Stuff_Default2"); }
    };

    struct Enum_Do_Stuff2
    {
        std::string operator()(Example_Enum value) const
        {
            return Enum_Switch<Example_Enum, Enum_Do_Stuff_Value2, Enum_Do_Stuff_Default2, std::string>()(value);
        }
    };

    

    void test();
} // namespace macro_enum

#endif // MACRO_ENUM_H