#ifndef FUNCTION_TRAITS_H
#define FUNCTION_TRAITS_H

#include <tuple>

namespace function_traits
{
    template <typename T>
    struct Function_Traits;

    template <typename T_Return>
    struct Function_Traits < T_Return() >
    {
        static std::size_t const arg_count{ 0 };

        //using function_type = T_Return(); // this line...is calling it isn't it
        using return_type = T_Return;
    };

    template <typename T_Return, typename... T_Args>
    struct Function_Traits < T_Return(T_Args...) >
    {
        static std::size_t const arg_count{ sizeof...(T_Args) };

        //using function_type = T_Return(T_Args...);
        using return_type = T_Return;

        template <std::size_t i>
        struct arg
        {
            using type = typename std::tuple_element<i, std::tuple<T_Args...>>::type;
            // the i-th argument is equivalent to the i-th tuple element of a tuple
            // composed of those arguments.
        };
    };


    template <typename T_Func>
    // constexpr
    Function_Traits<T_Func> get_function_traits(T_Func Function)
    {
        return Function_Traits < T_Func >();
    }



    template <typename T>
    struct Is_Free_Function
    {
        static bool const value{ false };
    };

    template <typename T_Return>
    struct Is_Free_Function < T_Return() >
    {
        static bool const value{ true };
    };

    template <typename T_Return, typename... T_Args>
    struct Is_Free_Function < T_Return(T_Args...) >
    {
        static bool const value{ true };
    };


    template <typename T>
    struct Is_Member_Function
    {
        static bool const value{ false };
    };

    template <typename T_Class, typename T_Return>
    struct Is_Member_Function<T_Return(T_Class::*)()>
    {
        static bool const value{ true };
    };

    template <typename T_Class, typename T_Return>
    struct Is_Member_Function<T_Return(T_Class::*)() const>
    {
        static bool const value{ true };
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Is_Member_Function<T_Return(T_Class::*)(T_Args...)>
    {
        static bool const value{ true };
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Is_Member_Function<T_Return(T_Class::*)(T_Args...) const>
    {
        static bool const value{ true };
    };


    template <typename T>
    struct Member_Function_Traits;

    template <typename T_Class, typename T_Return>
    struct Member_Function_Traits<T_Return(T_Class::*)()>
    {
        static std::size_t const arg_count{ 0 };
        static bool const is_const{ false };

        using function_type = T_Return(T_Class::*)();
        using class_type = T_Class;
        using return_type = T_Return;
    };

    template <typename T_Class, typename T_Return>
    struct Member_Function_Traits<T_Return(T_Class::*)() const>
    {
        static std::size_t const arg_count{ 0 };
        static bool const is_const{ true };

        using function_type = T_Return(T_Class::*)() const;
        using class_type = T_Class;
        using return_type = T_Return;
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Member_Function_Traits<T_Return(T_Class::*)(T_Args...)>
    {
        static std::size_t const arg_count{ sizeof...(T_Args) };
        static bool const is_const{ false };

        using function_type = T_Return(T_Class::*)(T_Args...);
        using class_type = T_Class;
        using return_type = T_Return;

        template <std::size_t i>
        struct arg
        {
            using type = typename std::tuple_element<i, std::tuple<T_Args...>>::type;
        };
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Member_Function_Traits<T_Return(T_Class::*)(T_Args...) const>
    {
        static std::size_t const arg_count{ sizeof...(T_Args) };
        static bool const is_const{ true };

        //using function_type = T_Return(T_Class::*)(T_Args...) const;
        using class_type = T_Class;
        using return_type = T_Return;

        template <std::size_t i>
        struct arg
        {
            using type = typename std::tuple_element<i, std::tuple<T_Args...>>::type;
        };
    };



    template <typename T_Func>
    // constexpr
    Member_Function_Traits<T_Func> get_member_function_traits(T_Func Function)
    {
        return Member_Function_Traits < T_Func >();
    }



    

    template <typename T>
    struct Has_No_Args
    {
    private:
        template < typename T, bool IFF = Is_Free_Function<T>::value, bool IMF = Is_Member_Function<T>::value >
        struct Determine_Function_Type
        {
            static bool const value{ false };
        };
        template < typename T >
        struct Determine_Function_Type<T, true, false>
        {
            static bool const value{ Function_Traits<T>::arg_count == 0 };
        };
        template < typename T >
        struct Determine_Function_Type<T, false, true>
        {
            static bool const value{ Member_Function_Traits<T>::arg_count == 0 };
        };
    public:
        static bool const value{ Determine_Function_Type<T>::value };
    };

    template <typename T, std::size_t N>
    struct Has_Arg_Count_Of
    {
    private:
        template < typename T, bool IFF = Is_Free_Function<T>::value, bool IMF = Is_Member_Function<T>::value >
        struct Determine_Function_Type
        {
            static bool const value{ 0 };
        };
        template < typename T >
        struct Determine_Function_Type<T, true, false>
        {
            static bool const value{ Function_Traits<T>::arg_count == N };
        };
        template < typename T >
        struct Determine_Function_Type<T, false, true>
        {
            static bool const value{ Member_Function_Traits<T>::arg_count == N };
        };
    public:
        static bool const value{ Determine_Function_Type<T>::value };
    };

    

    template <typename F>
    bool function_has_no_args(F )
    {
        return Has_No_Args<F>::value;
    }

    template <typename F, std::size_t N>
    bool function_has_arg_count_of(F)
    {
        return Has_Arg_Count_Of<F, N>::value;
    }


    void test();
} // namespace function_traits

#endif // FUNCTION_TRAITS_H