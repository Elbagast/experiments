#include "enum_stuff.h"
#include "integer_id.h"
#include "enum_data_manager.h"
#include "data_pool_value.h"
#include "enum_in_class.h"
#include "grid.h"
#include "object_manager.h"
#include "member_templates.h"
#include "abstract_interface_test.h"
#include "fake_virtual_functions.h"
#include "interface_operators.h"
#include "data_policies.h"
#include "enum_stuff2.h"
#include "variadic_templates.h"
#include "reference_counting.h"

template <char C>
struct Char_Type
{
    char m_char{ C };
};


/*
Quick typedef test..
*/
template<typename T>
using ref_ptr = T*;


int main(int argc, char* argv[])
{
    /*
    Char_Type<'A'> a;
    Char_Type<'b'> b;
    std::cout << a.m_char << std::endl;
    std::cout << b.m_char << std::endl;

    


    ref_ptr<int> refptrtest1 = new int;
    ref_ptr<int const> refptrtest2 = new int;
    ref_ptr<int> const refptrtest3 = new int;
    ref_ptr<int const> const refptrtest4 = new int;

    *refptrtest1 = 1;
    //*refptrtest2 = 2;
    *refptrtest3 = 3;
    //*refptrtest4 = 4;

    delete refptrtest1;
    delete refptrtest2;
    delete refptrtest3;
    delete refptrtest4;
    */

    grid::test();

    enum_in_class::test();

    enum_stuff::test();

    enum_data_manager::test();

    data_pool_value::test();

    // This has been superceeded by reference_counting which is a later version 
    object_manager::test();

    integer_id::test();

    member_templates::test();

    abstract_interface_test::test();

    fake_virtual_functions::test();

    interface_operators::test();

    data_policies::test();

    enum_stuff2::test();

    variadic_templates::test();

    reference_counting::test();

    return 0;
}