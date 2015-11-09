#ifndef FUNCTION_TRAITS_H
#define FUNCTION_TRAITS_H

#include <tuple>

namespace function_traits
{
    template <typename T>
    struct Function_Traits;

    template <typename T_Return_Type, typename... T_Args>
    struct Function_Traits < T_Return_Type(T_Args...) >
    {
        static std::size_t const arg_count{ sizeof...(T_Args) };

        using return_type = T_Return_Type;

        template <std::size_t i>
        struct arg
        {
            using type = typename std::tuple_element<i, std::tuple<T_Args...>>::type;
            // the i-th argument is equivalent to the i-th tuple element of a tuple
            // composed of those arguments.
        };
    };

    void test();
} // namespace function_traits

#endif // FUNCTION_TRAITS_H