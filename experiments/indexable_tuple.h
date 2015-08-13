#ifndef INDEXABLE_TUPLE_h
#define INDEXABLE_TUPLE_h

/*

*/

#include <array>
#include <tuple>
#include <typeindex>

namespace indexable_tuple
{
    class Base
    {
    public:
        virtual ~Base() = default;
        virtual std::type_index held_type_index() const = 0;
    };

    template <typename T>
    class Derived :
        public Base
    {
    public:
        // need to explicitly call the held type's constructor to make it default construct simple types
        Derived() : m_held{} {}
        ~Derived() override = default;
        std::type_index held_type_index() const override { return std::type_index(typeid(T)); }

        Base* self_base() { return this; }
        Base const* self_base() const { return this; }

        T m_held;
    };

    template <typename... Types>
    class Indexable_Tuple
    {
    public:
        using contruction_tuple_type = std::tuple<Types...> ;
        using tuple_type = std::tuple < Derived<Types>... > ;
        using array_type = std::array < Base*, std::tuple_size<tuple_type>::value > ;

        template <typename... Args>
        Indexable_Tuple(Args&&... args) :
            m_tuple(make_tuple(std::forward<Types>(args)...)),
            m_array(make_array(m_tuple))
        {}

        template <std::size_t I>
        typename std::tuple_element<I, tuple_type>::type* get_derived_at()
        {
            return &(std::get<I>(m_tuple));
        }

        template <std::size_t I>
        Base* get_base_at()
        {
            return &(std::get<I>(m_tuple));
        }


        Base* get_base_at(std::size_t index)
        {
            return m_array.at(index);
        }

        Base const* get_base_at(std::size_t index) const
        {
            return m_array.at(index);
        }

        std::size_t size() const
        {
            return m_array.size();
        }

    private:
        static
        tuple_type& fill_tuple(tuple_type& tuple_to_fill, contruction_tuple_type& args)
        {
            return fill_tuple(tuple_to_fill, args, std::integral_constant<std::size_t, std::tuple_size<tuple_type>::value>());
        }

        static
        tuple_type& fill_tuple(tuple_type& tuple_to_fill, contruction_tuple_type& args, std::integral_constant<std::size_t, 0>)
        {
            return tuple_to_fill;
        }

        template <std::size_t I>
        static
        tuple_type& fill_tuple(tuple_type& tuple_to_fill, contruction_tuple_type& args, std::integral_constant<std::size_t, I>)
        {
            fill_tuple(tuple_to_fill, args, std::integral_constant<std::size_t, I - 1>());
            std::tuple_element<I - 1, tuple_type>::type& derived = std::get<I - 1>(tuple_to_fill);
            derived.m_held = std::get<I - 1>(args);
            return tuple_to_fill;
        }

        template <typename... Args>
        static
        tuple_type make_tuple(Args&&... args)
        {
            tuple_type result;
            fill_tuple(result, contruction_tuple_type(std::forward<Args>(args)...));
            return result;
        }

        static
        array_type& fill_array(array_type& array_to_fill, tuple_type& tuple)
        {
            return fill_array(array_to_fill, tuple, std::integral_constant<std::size_t, std::tuple_size<tuple_type>::value>());
        }

        static
        array_type& fill_array(array_type& array_to_fill, tuple_type& tuple, std::integral_constant<std::size_t, 0>)
        {
            return array_to_fill;
        }

        template <std::size_t I>
        static
        array_type& fill_array(array_type& array_to_fill, tuple_type& tuple, std::integral_constant<std::size_t, I>)
        {
            fill_array(array_to_fill, tuple, std::integral_constant<std::size_t, I-1>());
            std::tuple_element<I - 1, tuple_type>::type& derived = std::get<I - 1>(tuple);
            std::get<I - 1>(array_to_fill) = derived.self_base();
            return array_to_fill;
        }

        static
        array_type make_array(tuple_type& tuple)
        {
            array_type result{};
            fill_array(result, tuple);
            return result;
        }

        tuple_type m_tuple;
        array_type m_array;
    };


    void test();
} // namespace indexable_tuple

#endif // INDEXABLE_TUPLE_h