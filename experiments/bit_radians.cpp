#include "bit_radians.h"

#include <thread>
#include <future>

#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>
#include <cstring>
#include <vector>


/*
namespace
{
    template <std::size_t N>
    struct Uint;

    template <>
    struct Uint < 1 >
    {
        using type = std::uint8_t;
    };

    template <>
    struct Uint < 2 >
    {
        using type = std::uint16_t;
    };

    template <>
    struct Uint < 4 >
    {
        using type = std::uint32_t;
    };

    template <>
    struct Uint < 8 >
    {
        using type = std::uint64_t;
    };

    template <typename U>
    struct Test_Results
    {
        U m_nan_count{ 0 };
        U m_equivalent_count{ 0 };
    };

    template <typename T, typename U = Uint<sizeof(T)>::type>
    bool bitwise_is_nan(U a_bit_value)
    {
    }

    template <typename T, typename U = Uint<sizeof(T)>::type>
    bool logical_sin_test(U a_bit_value)
    {
        static_assert(sizeof(U) >= sizeof(T), "bad size");

        // configure a T with the given bit values
        T l_start{};
        //std::memcpy(static_cast<void*>(&l_start), static_cast<void const*>(&a_bit_value), sizeof(T));
        std::memcpy(&l_start, &a_bit_value, sizeof(T));

        T const l_sin = std::sin(l_start);
        T const l_asin = std::asin(l_sin);

        return l_start == l_asin;
    }

    template <typename T, typename U = Uint<sizeof(T)>::type>
    bool bitwise_sin_test(U a_bit_value)
    {
        static_assert(sizeof(U) >= sizeof(T), "bad size");

        // configure a T with the given bit values
        T l_start{};
        //std::memcpy(static_cast<void*>(&l_start), static_cast<void const*>(&a_bit_value), sizeof(T));
        std::memcpy(&l_start, &a_bit_value, sizeof(T));
        
        T const l_sin = std::sin(l_start);
        T const l_asin = std::asin(l_sin);
        U l_final_bits{};
        std::memcpy(&l_final_bits, &l_asin, sizeof(T));
        return a_bit_value == l_final_bits;
    }

    template <typename T, typename U = Uint<sizeof(T)>::type>
    std::uint64_t range_bitwise_sin_test(U a_start, U a_end)
    {
        std::uint64_t l_uneqivalent_count{ 0 };

        for (U bit_config = a_start + 1; bit_config != a_end; ++bit_config)
        {

            if (!bitwise_sin_test<T>(bit_config))
            {
                ++l_uneqivalent_count;
            }
        }
        return l_uneqivalent_count;
    }

    // for all values of a number type, determine whether arcsin(sin(x)) == x
    template <typename T>
    std::uint64_t all_bitwise_sin_test(std::size_t a_thread_count)
    {
        using Uint = typename Uint<sizeof(T)>::type;

        // for all values of a number type
        Uint l_min = std::numeric_limits<Uint>::min();
        Uint l_max = std::numeric_limits<Uint>::max();

        //U l_block_size = l_max / 4;

        std::cout << l_max << " values to consider..." << std::endl;

        using future_type = decltype(std::async(range_bitwise_sin_test<T>, Uint(0), Uint(0)));
        
        std::vector<future_type> l_futures{};

        Uint const l_block_size{ l_max / a_thread_count };

        for (Uint l_thread = 0, l_start = 0, l_end = l_block_size; l_thread != a_thread_count; ++l_thread)
        {
            l_futures.push_back(std::async(range_bitwise_sin_test<T>, l_start, l_end));
            l_start = l_end;
            l_end += l_block_size;
        }

        std::uint64_t l_uneqivalent_count{ 0 };

        for (auto& l_future : l_futures)
        {
            l_uneqivalent_count += l_future.get();
        }

        return l_uneqivalent_count;
    }
}*/

void bit_radians::test()
{
    std::cout << "Bit Radians" << std::endl << std::endl;
	/*
    static float const pi_single{ 3.1415927f };
    static float const halfpi_single{ pi_single/2 };

    static double const pi_double{ 3.1415926535897932 };
    static double const halfpi_double{ pi_double/2 };

    Radians_Single rs1{ pi_single/2 };
    Radians_Double rd1{ -pi_single/4 };

    Degrees_Single ds1{ 90.0f };
    Degrees_Double dd1{ -45.0 };

    std::cout << "Test whether arcsin(sin(x)) == x" << std::endl;
    std::cout << "For type float:" << std::endl;
    std::uint64_t l_float_result = all_bitwise_sin_test<float>(5);
    std::cout << l_float_result << " non-equivalent values" << std::endl;
    //std::cout << "double has " << all_sin_test <float>() << " non-equivalent values" << std::endl;
	*/
    std::cout << "----------------------------------------" << std::endl;
}