#ifndef EXPLICIT_TEMPLATE_INSTANTIATION_H
#define EXPLICIT_TEMPLATE_INSTANTIATION_H

#include <type_traits>

/*
Test of explicit instantiation of templates in a .cpp file so the template
implementation is both hidden and limited in use. Trying to use this template
on types not declared in the .cpp file leads to link errors with undefined
symbols since the implementation doesn't exist for them.
*/

namespace explicit_template_instantiation
{
    template <typename T>
    class Some_Template
    {
    public:
        using value_type = T;

        explicit Some_Template(value_type const& a_value);

        value_type get_value() const;
        void set_value(value_type const& a_value);

    private:
        value_type m_value;
    };

    /*
    A version that states its limitations publicly and provides better compile errors.
    This makes the usage obvious but exposes implementation details...
    */

    template <typename T>
    class Other_Template
    {
        static_assert(std::is_same<T, int>::value || std::is_same<T, double>::value, "Supplied type is not int or double." );
    public:
        using value_type = T;

        explicit Other_Template(value_type const& a_value);

        value_type get_value() const;
        void set_value(value_type const& a_value);

    private:
        value_type m_value;
    };

} // namespace explicit_template_instantiation

#endif // EXPLICIT_TEMPLATE_INSTANTIATION_H