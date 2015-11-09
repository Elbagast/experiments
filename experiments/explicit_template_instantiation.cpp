#include "explicit_template_instantiation.h"

#include <string>

template <typename T>
explicit_template_instantiation::Some_Template<T>::Some_Template(value_type const& a_value) :
    m_value( a_value )
{}

template <typename T>
typename explicit_template_instantiation::Some_Template<T>::value_type explicit_template_instantiation::Some_Template<T>::get_value() const
{
    return m_value;
}

template <typename T>
void explicit_template_instantiation::Some_Template<T>::set_value(value_type const& a_value)
{
    m_value = a_value;
}

// tell the compiler to instantiate these here
template explicit_template_instantiation::Some_Template < int > ;
template explicit_template_instantiation::Some_Template < double >;
template explicit_template_instantiation::Some_Template < std::string >;




template <typename T>
explicit_template_instantiation::Other_Template<T>::Other_Template(value_type const& a_value) :
m_value(a_value)
{}

template <typename T>
typename explicit_template_instantiation::Other_Template<T>::value_type explicit_template_instantiation::Other_Template<T>::get_value() const
{
    return m_value;
}

template <typename T>
void explicit_template_instantiation::Other_Template<T>::set_value(value_type const& a_value)
{
    m_value = a_value;
}

// tell the compiler to instantiate these here
template explicit_template_instantiation::Other_Template < int >;
template explicit_template_instantiation::Other_Template < double >;

