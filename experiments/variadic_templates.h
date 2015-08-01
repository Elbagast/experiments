#ifndef VARIADIC_TEMPLATES_H
#define VARIADIC_TEMPLATES_H

/*
Playing around with variadic templates

http://en.cppreference.com/w/cpp/language/parameter_pack

Ok this turned into the old Element-Attribute problem again with the 
Element classes knowing the Attribute types at compile time, but it 
runs into problems accessing parts of the tuple at runtime...


UNFINISHED
*/

#include <tuple>
#include <array>
#include <string>
#include <utility>
#include <typeinfo>

namespace variadic_templates
{
    /*
    Attribtes
    */
    class IAttribute
    {
    public:
        virtual ~IAttribute() = default;

        virtual std::string const& name() const = 0;
        virtual std::type_info const& type() const = 0;
    };

    template <typename T>
    class IAttribute_Type :
        public IAttribute
    {
    public:
        ~IAttribute_Type() override = default;

        std::string const& name() const override  = 0;
        std::type_info const& type() const override = 0;

        virtual T const& get_value() const = 0;
        virtual void set_value(T const& value) = 0;

    protected:
        static std::type_info const& internal_type() { return typeid(T); }
    };

    template <typename T>
    class Attribute :
        public IAttribute_Type<T>
    {
    public:
        // Needed if going in a std::tuple
        Attribute() = default;
        explicit Attribute(std::string const& name):
            IAttribute_Type<T>(),
            m_name(name),
            m_value()
        {}

        ~Attribute() override = default;

        std::string const& name() const override        { return m_name; }
        std::type_info const& type() const override     { return internal_type(); }

        T const& get_value() const override             { return m_value; }
        void set_value(T const& value) override         { m_value = value; }

    private:
        std::string m_name;
        T m_value;
    };

    
    /*
    Elements
    */

    class IElement
    {
    public:
        virtual ~IElement() = default;

        //virtual std::string const& type() const = 0;
        virtual std::size_t attribute_count() const = 0;

        virtual IAttribute& iattribute(std::size_t index) = 0;
        virtual IAttribute const& ciattribute(std::size_t index) const = 0;
    };

    template <typename... Ts>
    class Element_Implementation :
        public IElement
    {
    public:
        Element_Implementation():
            IElement(),
            m_tuple(),
            m_array(make_pointer_array(m_tuple))
        {
        }

        ~Element_Implementation() override = default;

        //std::string const& type() const override = 0;
        std::size_t attribute_count() const override
        { 
            return tuple_size();
        }
        
        IAttribute& iattribute(std::size_t index) override
        {
            return *(m_array.at(index));
        }
        IAttribute const& ciattribute(std::size_t index) const override
        {
            return *(m_array.at(index));
        }

        
    private:
        using tuple_type = std::tuple < Attribute<Ts>... >;
        using array_type = std::array < IAttribute*, std::tuple_size<tuple_type>::value > ;

        // can't make a static function virtual so it's here instead
        static std::size_t tuple_size()
        { 
            return std::tuple_size<tuple_type>::value;
        }

        template <std::size_t Index>
        IAttribute& get_iattribute()
        {
            auto attribute_reference = std::get<Index>(m_tuple);
            return attribute_reference;
        }

        template <std::size_t Index>
        IAttribute const& get_iattribute() const
        {
            auto attribute_reference = std::get<Index>(m_tuple);
            return attribute_reference;
        }

        static array_type make_pointer_array(tuple_type& tuple)
        {
            array_type result_array{};
            for (std::size_t index = 0, end = std::tuple_size<tuple_type>::value; index != end; ++index)
            {

            }
            return result_array;
        }

        tuple_type m_tuple;
        array_type m_array;
    };


    class Concrete_Element :
        public Element_Implementation < bool, int, double >
    {
    public:
        Concrete_Element() :
            Element_Implementation < bool, int, double >()
        {}
        ~Concrete_Element() override = default;

        //std::string const& type() const override { return s_type_string; }
    //private:
        //static std::string const s_type_string;
    };

    //std::string const Concrete_Element::s_type_string = std::string("Concrete_Type");

    void test();

} // variadic_templates

#endif // VARIADIC_TEMPLATES_H