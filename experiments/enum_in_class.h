#ifndef ENUM_IN_CLASS_H
#define ENUM_IN_CLASS_H
/*
Can you have an enum class of the same name in multiple classes?
*/

namespace enum_in_class
{

    class Foo
    {
    public:
        enum class Values
        {
            First,
            Second
        };
    };


    class Bar
    {
    public:
        enum class Values
        {
            First,
            Second
        };
    };

    /*
    Duh, of course you can, they're distinct types. So you could have this:
    */
    template <typename T>
    class Anything
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

    void test()
    {
        auto a = Foo::Values::First;
        auto b = Bar::Values::First;

        auto c = Anything<int>::Values::First;
    }
    

} // namespace enum_in_class



#endif // ENUM_IN_CLASS_H