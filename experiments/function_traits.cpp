#include "function_traits.h"

#include <type_traits>
#include <iostream>

namespace
{
    void do_stuff1();
    void do_stuff1(int); // this doesn't like overloads...
    float do_stuff2(int, float);

    struct Test_Thing
    {
        void f();
        void f(int);
        int f2(int, double) const;
    };

}

void function_traits::test()
{
    std::cout << "Function Traits Test" << std::endl << std::endl;
    //using do_stuff1_traits_type = Function_Traits < decltype(do_stuff1) >;

    // getting the traits types for overloads
    using do_stuff1_traits_type = decltype(get_function_traits<void()>(do_stuff1));
    using do_stuff1_alt_traits_type = decltype(get_function_traits<void(int)>(do_stuff1));
        
    static_assert(do_stuff1_traits_type::arg_count == 0, "bad arg count");
    static_assert(std::is_same<do_stuff1_traits_type::return_type, void>::value, "bad return type");

    static_assert(do_stuff1_alt_traits_type::arg_count == 1, "bad arg count");
    static_assert(std::is_same<do_stuff1_alt_traits_type::return_type, void>::value, "bad return type");
    static_assert(std::is_same<do_stuff1_alt_traits_type::arg<0>::type, int>::value, "bad arg type");

    using do_stuff2_traits = Function_Traits < decltype(do_stuff2) >;

    static_assert(do_stuff2_traits::arg_count == 2, "bad arg count");
    static_assert(std::is_same<do_stuff2_traits::return_type, float>::value, "bad return type count");
    static_assert(std::is_same<do_stuff2_traits::arg<0>::type, int>::value, "bad arg type");
    static_assert(std::is_same<do_stuff2_traits::arg<1>::type, float>::value, "bad arg type");
    
    //using Test_Thing_f_traits = Member_Function_Traits < decltype(&Test_Thing::f) > ;
    //using Test_Thing_f_alt_traits = Member_Function_Traits < decltype(&Test_Thing::f) >;

    // getting the traits types for overloads
    using Test_Thing_f_traits = decltype(get_member_function_traits<void(Test_Thing::*)()>(&Test_Thing::f));
    using Test_Thing_f_alt_traits = decltype(get_member_function_traits<void(Test_Thing::*)(int)>(&Test_Thing::f));

    using Test_Thing_f_type = Test_Thing_f_traits::function_type;
    using Test_Thing_f_alt_type = Test_Thing_f_alt_traits::function_type;

    using Test_Thing_f2_traits = Member_Function_Traits < decltype(&Test_Thing::f2) >;

    static_assert(std::is_same<Test_Thing_f_traits::class_type, Test_Thing>::value, "bad class type");
    static_assert(Test_Thing_f_traits::arg_count == 0, "bad arg count");
    static_assert(Test_Thing_f_traits::is_const == false, "bad constness");
    static_assert(std::is_same<do_stuff1_traits_type::return_type, void>::value, "bad return type");

    static_assert(std::is_same<Test_Thing_f_alt_traits::class_type, Test_Thing>::value, "bad class type");
    static_assert(Test_Thing_f_alt_traits::arg_count == 1, "bad arg count");
    static_assert(Test_Thing_f_alt_traits::is_const == false, "bad constness");
    static_assert(std::is_same<Test_Thing_f_alt_traits::return_type, void>::value, "bad return type");
    static_assert(std::is_same<Test_Thing_f_alt_traits::arg<0>::type, int>::value, "bad arg type");

    static_assert(std::is_same<Test_Thing_f2_traits::class_type, Test_Thing>::value, "bad class type");
    static_assert(Test_Thing_f2_traits::arg_count == 2, "bad arg count");
    static_assert(Test_Thing_f2_traits::is_const == true, "bad constness");
    static_assert(std::is_same<Test_Thing_f2_traits::return_type, int>::value, "bad return type");
    static_assert(std::is_same<Test_Thing_f2_traits::arg<0>::type, int>::value, "bad arg type");
    static_assert(std::is_same<Test_Thing_f2_traits::arg<1>::type, double>::value, "bad arg type");

    //static_assert(Has_No_Args< decltype(do_stuff1) >::value == true, "bad arg count");
    static_assert(Has_No_Args< decltype(do_stuff2) >::value == false, "bad arg count");
    static_assert(Has_No_Args< Test_Thing_f_type >::value == true, "bad arg count");
    static_assert(Has_No_Args< decltype(&Test_Thing::f2) >::value == false, "bad arg count");

    //static_assert(Has_Arg_Count_Of< decltype(do_stuff1), 0>::value == true, "bad arg count");
    static_assert(Has_Arg_Count_Of< decltype(do_stuff2), 2>::value == true, "bad arg count");
    static_assert(Has_Arg_Count_Of< Test_Thing_f_type, 0>::value == true, "bad arg count");
    static_assert(Has_Arg_Count_Of< decltype(&Test_Thing::f2), 2>::value == true, "bad arg count");
    
    std::cout << "----------------------------------------" << std::endl;
}