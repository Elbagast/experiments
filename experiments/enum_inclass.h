#ifndef ENUM_INCLASS_H
#define ENUM_INCLASS_H
/*
Can you have an enum class of the same name in multiple classes?
*/

class EnumInClass1
{
public:
    enum class Values
    {
        First,
        Second
    };
};


class EnumInClass2
{
public:
    enum class Values
    {
        First,
        Second
    };
};

void test_EnumInClass()
{
    auto a = EnumInClass1::Values::First;
    auto b = EnumInClass2::Values::First;

}
/*
Duh, of course you can, they're distinct types. So you could have this:
*/
template <typename T>
class EnumInClass
{
public:
    enum class Values
    {
        First,
        Second
    };
};

/*
EnumInClass<T>::Values will be distinct for all template types
*/


#endif