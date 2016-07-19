#ifndef POINTER_IDENTIFICATION_H
#define POINTER_IDENTIFICATION_H

#include <cstddef>

namespace pointer_identification
{
    template <typename T>
    struct Is_Basic_Pointer
    {
        static bool const value{ false };
    };

    template <typename T>
    struct Is_Basic_Pointer<T*>
    {
        static bool const value{ true };
    };

    template <typename T>
    struct Is_Basic_Pointer<T const*>
    {
        static bool const value{ true };
    };

    template <typename T>
    struct Is_Basic_Pointer<T *const>
    {
        static bool const value{ true };
    };

    template <typename T>
    struct Is_Basic_Pointer<T const*const>
    {
        static bool const value{ true };
    };

    template <typename T, std::size_t N>
    struct Is_Basic_Pointer < T[N] >
    {
        static bool const value{ false };
    };

    template <typename T, std::size_t N>
    struct Is_Basic_Pointer < T const[N] >
    {
        static bool const value{ false };
    };



    template <typename T>
    struct Is_Array
    {
        static bool const value{ false };
    };

    template <typename T, std::size_t N>
    struct Is_Array<T[N]>
    {
        static bool const value{ true };
    };

    template <typename T, std::size_t N>
    struct Is_Array<T const [N]>
    {
        static bool const value{ true };
    };


    template <typename T>
    struct Array_Size
    {
        static std::size_t const value{ 0 };
    };

    template <typename T, std::size_t N>
    struct Array_Size<T[N]>
    {
        static std::size_t const value{ N };
    };

    template <typename T, std::size_t N>
    struct Array_Size<T const[N]>
    {
        static std::size_t const value{ N };
    };

    template <typename T>
    std::size_t array_size(T const& a_array)
    {
        return Array_Size<T>::value;
    }



    void test();

}

#endif // POINTER_IDENTIFICATION_H