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
        static constexpr std::size_t const arg_count{ 0 };

        //using function_type = decltype(T_Return());
        using return_type = T_Return;
    };

    template <typename T_Return, typename... T_Args>
    struct Function_Traits < T_Return(T_Args...) >
    {
        static constexpr std::size_t const arg_count{ sizeof...(T_Args) };

        //using function_type = decltype(T_Return(T_Args...));
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
    constexpr decltype(auto) get_function_traits(T_Func Function)
    {
        return Function_Traits < T_Func >();
    }
	

    // This is pointless - use std::is_function<T>

    template <typename T>
    struct Is_Function
    {
        static constexpr bool const value{ false };
    };

    template <typename T_Return>
    struct Is_Function < T_Return() >
    {
        static constexpr bool const value{ true };
    };

    template <typename T_Return, typename... T_Args>
    struct Is_Function < T_Return(T_Args...) >
    {
        static constexpr bool const value{ true };
    };

    // This is pointless - use std::is_member_function_pointer<T>

    template <typename T>
    struct Is_Member_Function
    {
        static constexpr bool const value{ false };
    };

    template <typename T_Class, typename T_Return>
    struct Is_Member_Function<T_Return(T_Class::*)()>
    {
        static constexpr bool const value{ true };
    };

    template <typename T_Class, typename T_Return>
    struct Is_Member_Function<T_Return(T_Class::*)() const>
    {
        static constexpr bool const value{ true };
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Is_Member_Function<T_Return(T_Class::*)(T_Args...)>
    {
        static constexpr bool const value{ true };
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Is_Member_Function<T_Return(T_Class::*)(T_Args...) const>
    {
        static constexpr bool const value{ true };
    };


    template <typename T>
    struct Member_Function_Traits;

    template <typename T_Class, typename T_Return>
    struct Member_Function_Traits<T_Return(T_Class::*)()> :
        public Function_Traits<T_Return()>
    {
        static constexpr bool const is_const{ false };
        using class_type = T_Class;
    };

    template <typename T_Class, typename T_Return>
    struct Member_Function_Traits<T_Return(T_Class::*)() const> :
        public Function_Traits<T_Return()>
    {
        static constexpr bool const is_const{ true };
        using class_type = T_Class;
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Member_Function_Traits<T_Return(T_Class::*)(T_Args...)> :
        public Function_Traits<T_Return(T_Args...)>
    {
        static constexpr bool const is_const{ false };
        using class_type = T_Class;
    };

    template <typename T_Class, typename T_Return, typename... T_Args>
    struct Member_Function_Traits<T_Return(T_Class::*)(T_Args...) const> :
        public Function_Traits<T_Return(T_Args...)>
    {
        static constexpr bool const is_const{ true };
        using class_type = T_Class;
    };



    template <typename T_Func>
	constexpr decltype(auto) get_member_function_traits(T_Func Function)
    {
        return Member_Function_Traits < T_Func >();
    }

    /*
    template <typename T>
    struct Function_Traits
    {
    private:
        using operator_traits = decltype(get_member_function_traits(&T::operator()));
    public:
        static std::size_t const arg_count{ operator_traits::arg_count };

        //using function_type = T_Return(); // this line...is calling it isn't it
        using return_type = typename operator_traits::return_type;

        template <std::size_t i>
        struct arg
        {
            using type = typename operator_traits::arg<i>::type;
        };
    };
    */
    

    template <typename T>
    struct Has_No_Args
    {
    private:
        template < typename T, bool IF = Is_Function<T>::value, bool IMF = Is_Member_Function<T>::value >
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
        template < typename T, bool IF = Is_Function<T>::value, bool IMF = Is_Member_Function<T>::value >
        struct Determine_Function_Type
        {
            static bool const value{ 0 };
        };
        //template < typename T >
        //struct Determine_Function_Type<T, false, false>
        //{
        //    static_assert(false, "Has_Arg_Count_Of cannot be used on this type as it is not a function type.");
        //    static bool const value{ 0 };
        //};
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
        //template < typename T >
        //struct Determine_Function_Type<T, true, true>
        //{
        //    static_assert(false, "Has_Arg_Count_Of has broken in an unexpected way.");
        //    static bool const value{ 0 };
        //};
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


    template <typename F1, typename F2>
    struct Is_Function_Match
    {
    private:
        template 
            < 
            typename T1, 
            typename T2,
            bool IF = Is_Function<T1>::value && Is_Function<T2>::value,
            bool IMF = Is_Member_Function<T1>::value && Is_Member_Function<T2>::value
            >
        struct Determine_Function_Compare
        {
            static bool const value{ false };
        };
        template < typename T1, typename T2 >
        struct Determine_Function_Compare<T1, T2, true, false>
        {
            static bool const value{ std::is_same<Function_Traits<T1>, Function_Traits<T2>>::value };
        };
        template < typename T1, typename T2 >
        struct Determine_Function_Compare<T1, T2, false, true>
        {
            static bool const value{ std::is_same<Member_Function_Traits<T1>, Member_Function_Traits<T2>>::value };
        };
    public:
        static bool const value{ Determine_Function_Compare<F1, F2>::value };
    };


    void test();
} // namespace function_traits

#endif // FUNCTION_TRAITS_H