#ifndef QUESTION_BASED_TEMPLATE_h
#define QUESTION_BASED_TEMPLATE_h

/*
Experiment into a template that partially specialises based on type traits or 
some other factor

e.g. want a template to have a certain interface if T is an integer type vs
a string type
*/
#include <limits>
#include <string>

namespace question_based_template
{
    enum class Extension_Enum
    {
        None,
        Integer,
        Float,
        StdString,
        Something,
        Else
    };

    template <typename T>
    struct Simple_Extension_Selector
    {
        static Extension_Enum const value{ Extension_Enum::None };
    };
    /*
    template <typename... Args>
    struct Simple_Extension_Selector
    {
        static Extension_Enum const value{ Extension_Enum::None };
    };
    */
    template <>
    struct Simple_Extension_Selector<int>
    {
        static Extension_Enum const value{ Extension_Enum::Integer };
    };

    template <>
    struct Simple_Extension_Selector<float>
    {
        static Extension_Enum const value{ Extension_Enum::Float };
    };

    
    // how could we do this in a way that this does this for all std::basic_string<C, CT, A> types?
    /*
    template <>
    struct Simple_Extension_Selector<std::string>
    {
        static Extension_Enum const value{ Extension_Enum::StdString };
    };

    template <>
    template <typename C, typename CT, typename A>
    struct Simple_Extension_Selector < std::basic_string<C, CT, A> >
    {
        static Extension_Enum const value{ Extension_Enum::StdString };
    };
    
    template <typename... Args>
    struct Simple_Extension_Selector < std::basic_string<Args...> >
    {
        static Extension_Enum const value{ Extension_Enum::StdString };
    };
    */

    // So it turns out you can do this to a template that has variadic args?
    template <typename C, typename CT, typename A>
    struct Simple_Extension_Selector < std::basic_string<C, CT, A> >
    {
        static Extension_Enum const value{ Extension_Enum::StdString };
    };




    /*
    So we have templates...how can we specialise something for all of a given template?..

    It seems this works, but only if the template can instantiated with one argument. hmmm
    */

    template <typename A, typename B = A>
    class Something
    {

    };

    template <typename A, typename B>
    struct Simple_Extension_Selector < Something<A, B> >
    {
        static Extension_Enum const value{ Extension_Enum::Something };
    };



    template <typename A, typename B>
    class Else
    {

    };

    template <typename A, typename B>
    struct Simple_Extension_Selector < Else<A, B> >
    {
        static Extension_Enum const value{ Extension_Enum::Else };
    };

    
    

    template <typename T, Extension_Enum IEE = Simple_Extension_Selector<T>::value>
    class Constraint
    {
    public:
        using constrained_type = T;

        Constraint() = default;

        bool is_valid(constrained_type const& value) { return true; }
    };

    template <typename T>
    class Constraint<T, Extension_Enum::Integer>
    {
    public:
        using constrained_type = T;

        Constraint():
            m_min(std::numeric_limits<constrained_type>::lowest()),
            m_max(std::numeric_limits<constrained_type>::max()),
            m_default(0)
        {}
        Constraint(constrained_type min, constrained_type max, constrained_type initial = 0) :
            m_min(min),
            m_max(max),
            m_initial(initial)
        {
            fix_values();
        }

        bool is_valid(constrained_type const& value)    { return value >= min() && value <= max(); }

        constrained_type min_value() const              { return m_min; }
        constrained_type max_value() const              { return m_max; }
        constrained_type initial_value() const          { return m_initial; }

    private:
        void fix_values()
        {
            if (m_max < m_min) m_max = m_min;
            if (m_min > m_max) m_min = m_max;
            if (m_initial < m_min) m_initial = m_min;
            if (m_initial > m_max) m_initial = m_max;
        }

        constrained_type m_min;
        constrained_type m_max;
        constrained_type m_initial;
    };

    void test();

} // namespace question_based_template

#endif // QUESTION_BASED_TEMPLATE_h