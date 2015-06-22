#ifndef DATA_POLICIES_H
#define DATA_POLICIES_H

/*
A test run of data encapsulation based on policy classes
*/
#include <type_traits>
#include <limits>
#include <cassert>

namespace data_policies
{
    namespace policies
    {
        // Useful at all?
        template <typename T>
        struct Type_Definitions
        {
            using value_type = T;
            using reference_type = T&;
            using const_reference_type = T const&;

            using pointer_type = T*;
            using pointer_const_type = T *const;
            using const_pointer_type = T const*;
            using const_pointer_const_type = T const*const;
        };

        // This is probably completely useless since you can just do protected inheritance
        template <typename Policy_Class>
        class Protector :
            protected Policy_Class
        {
        public:
            using Policy_Class::Policy_Class;
        protected:
            ~Protector() = default;
        };



        namespace storage
        { 
            // Class to enforce the required specification for storage policies
            template <typename Policy_Class>
            struct Enforcer
            {
                static bool const value { false };
            };


            template <typename T, bool Is_Fundamental_Type = std::is_fundamental<T>::value>
            class Local_Value
            {
            public:
                using value_type = T;
                using reference_type = T&;
                using const_reference_type = T const&;

                Local_Value() = default;
                Local_Value(const_reference_type value) : m_value(value) {}
            protected:
                ~Local_Value() = default;
            public:
                const_reference_type get() const        { return m_value; }
                void set(const_reference_type value)    { m_value = value; }

                static bool is_fundamental()            { return false; }
            private:
                value_type m_value;
            };

            template <typename T>
            class Local_Value<T, true>
            {
            public:
                using value_type = T;
                using reference_type = T&;
                using const_reference_type = T const&;

                Local_Value() = default;
                Local_Value(value_type value) : m_value(value) {}
            protected:
                ~Local_Value() = default;
            public:
                value_type get() const                    { return m_value; }
                void set(value_type value)                { m_value = value; }

                static bool is_fundamental()             { return true; }
            private:
                value_type m_value;
            };

        }



        namespace constraints
        {
            template <typename T>
            class Unconstrained
            {
            public:
                using const_reference_type = T const&;

            protected:
                ~Unconstrained() = default;

            public:
                static bool is_constrained()  { return false; }
            };


            template <typename T>
            class Number_Range
            {
                static_assert(std::is_arithmetic<T>::value, "Cannot instantiate Number_Range<T> with a non-arithmatic type.");
            public:
                using value_type = T;
                using reference_type = T&;
                using const_reference_type = T const&;

                Number_Range():
                    m_min{ std::numeric_limits<value_type>::min() },
                    m_max{ std::numeric_limits<value_type>::max() }
                {}
                Number_Range(value_type minimum, value_type maximum) :
                    Number_Range()
                {
                    assert(minimum < maximum);
                    set_minimum(minimum);
                    set_maximum(maximum);
                }
            protected:
                ~Number_Range() = default;

            public:
                static bool is_constrained()                     { return true; }

                bool is_within_range(value_type value) const    { return value >= m_min && value >= m_max; }

                value_type get_min() const                        { return m_min; }
                value_type get_max() const                        { return m_max; }

                void set_min(value_type value)                    { if (value < m_max) m_min = value; }
                void set_max(value_type value)                    { if (value > m_min) m_max = value; }

            private:
                value_type m_min; // These could be policies...
                value_type m_max;
            };
        }
    }
    

    // this will be the final user accessed class
    template <typename T, typename Storage_Policy, typename Constraint_Policy>
    class Data :
        public Storage_Policy,
        public Constraint_Policy
    {

    };



    void test();


} // namespace data_policies

#endif // DATA_POLICIES_H