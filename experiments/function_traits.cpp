#include "function_traits.h"

#include <iostream>

namespace
{
    void do_stuff1();
    //void do_stuff1(int); // this doesn't like overloads...
    float do_stuff2(int, float);

}

void function_traits::test()
{
    std::cout << "Function Traits Test" << std::endl << std::endl;

    using do_stuff1_traits = Function_Traits < decltype(do_stuff1) > ;

    static_assert(do_stuff1_traits::arg_count == 0, "bad arg count");
    static_assert(std::is_same<do_stuff1_traits::return_type, void>::value, "bad return type count");
    

    using do_stuff2_traits = Function_Traits < decltype(do_stuff2) >;
    static_assert(do_stuff2_traits::arg_count == 2, "bad arg count");
    static_assert(std::is_same<do_stuff2_traits::return_type, float>::value, "bad return type count");
    static_assert(std::is_same<do_stuff2_traits::arg<0>::type, int>::value, "bad arg type");
    static_assert(std::is_same<do_stuff2_traits::arg<1>::type, float>::value, "bad arg type");


    std::cout << std::noboolalpha;
    std::cout << "----------------------------------------" << std::endl;
}