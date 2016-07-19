#include "pointer_identification.h"

#include <iostream>
#include <cassert>

void pointer_identification::test()
{
    std::cout << "Pointer Identification" << std::endl << std::endl;

    int l_int{123};
    int l_int_array[]{1,2,3};

    int const* l_int_pointer{ &l_int };
    int const* l_int_array_pointer{ &l_int_array[0] };

    assert(Is_Basic_Pointer<decltype(l_int_pointer)>::value);
    assert(!Is_Basic_Pointer<decltype(l_int_array)>::value);

    assert(!Is_Array<decltype(l_int_pointer)>::value);
    assert(Is_Array<decltype(l_int_array)>::value);

    assert(Array_Size<decltype(l_int_pointer)>::value == 0);
    assert(Array_Size<decltype(l_int_array)>::value == 3);

    assert(array_size(l_int_pointer) == 0);
    assert(array_size(l_int_array) == 3);
    

    char l_char{'x'};
    char l_char_array[]{"moo"};

    char const* l_char_pointer = &l_char;
    char const* l_char_array_pointer = l_char_array;


    std::cout << "----------------------------------------" << std::endl;
}