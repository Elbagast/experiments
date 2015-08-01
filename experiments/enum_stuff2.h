#ifndef ENUM_STUFF2_H
#define ENUM_STUFF2_H
/*
Some more messing with enum classes
*/

namespace enum_stuff2
{
    template <typename T, typename Enum_Class, Enum_Class Enum_Value>
    struct Enum_Binder
    {
        using bound_type = T;
        using enum_type = Enum_Class;

        static enum_type enum_value() { return Enum_Value; }
    };

    

    void test();
} // enum_stuff2

#endif // ENUM_STUFF2_H