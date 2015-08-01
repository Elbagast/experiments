#ifndef INTEGER_ID_H
#define INTEGER_ID_H
/*
Integer_ID
============================================================
Let's say you have decided that there is some functionality you want to reuse and thus only code and maintain in one place,
but you have multiple uses for it, and you don't want those uses to overlap intentionally or accidentally. In this case,
deciding I want to access two different and unrelated classes via a system of ID numbers, but I don't want the IDs to be
type compatible. 

e.g.
class ElementID;
class AttributeID;
Where both are the same, but using them interchangabley would be madness.

This turned into an investigation into private inheritance.


The annoying part? I'm now pondering whether this is even necessary for what I want to do...



Later Experimentation
----------------------------------
If you think of these as being pointer replacements (what they will be used as) then you need a class that defines the
overall behaviour and another that wraps that behaviour and binds it to a specific type. This results in:

template <typename Uint>
class Integer_ID;

and

template <typename T, typename Uint>
class Bound_Integer_ID;

where the former defines all the behaviour and the latter just creates explicit different types for that behaviour (i.e. now
have a fake void* and a fake T* where they are actually Uint values).

*/
#include <cassert>
#include <type_traits>
#include <queue>
#include <algorithm>

namespace integer_id
{
    namespace old
    {
        template <typename UInt>
        class Integer_ID
        {
        protected:
            // Everything is protected so that only derived classes can use them. 
            // You must reveal what you need with using declarations
            using value_type = UInt;

            // Stop compiling if the value_type is not an unsigned integer
            static_assert((std::is_integral<value_type>::value && std::is_unsigned<value_type>::value), "Templated type must be an unsigned integral type");

            // Special 6
            //============================================================
            Integer_ID() :
                m_value(s_invalidValue)
            {}
            explicit Integer_ID(value_type value) :
                m_value(value)
            {}
            // Destructor is not virtual. Use private inheritance.
            ~Integer_ID() = default;

            Integer_ID(Integer_ID const& other) = default;
            Integer_ID& operator=(Integer_ID const& other) = default;

            // God. Dammit. Visual Studio.
            // These should work.
            //Integer_ID(Integer_ID&& other) = default;
            //Integer_ID& operator=(Integer_ID&& other) = default;

            // Interface
            //============================================================
            value_type getValue() const                     { return m_value; }
            void setValue(value_type value)                 { m_value = value; }
            bool isValid() const                            { return m_value != s_invalidValue; }

            // provide < and == functionality without defining the member operators
            bool less(Integer_ID const& rhs) const          { return m_value < rhs.m_value; }
            bool equal(Integer_ID const& rhs) const         { return m_value == rhs.m_value; }
        private:
            value_type m_value;

            static value_type const s_invalidValue{ 0 };
        };

        // I don't know why Visual Studio is complaining about this inheritence, it compiles and works as intended?
        class TestID :
            private Integer_ID<unsigned long>
        {
        private:
            // So that we don't have to use this form in declarations
            using base_type = Integer_ID<unsigned long>;
        public:
            // Reveal this typedef
            using base_type::value_type;

            // Special 6
            //============================================================
            TestID() :
                base_type()
            {}
            explicit TestID(value_type value) :
                base_type(value)
            {}
            ~TestID() = default;

            TestID(TestID const& other) = default;
            TestID& operator=(TestID const& other) = default;

            //TestID(TestID&& other) = default;
            //TestID& operator=(TestID && other) = default;

            // Interface
            //============================================================
            // Make all of the existing interface public
            using base_type::getValue;
            using base_type::setValue;
            using base_type::isValid;

            bool less(TestID const& rhs) const        { return base_type::less(rhs); }
            bool equal(TestID const& rhs) const       { return base_type::equal(rhs); }
        };

        inline bool operator<(TestID const& lhs, TestID const& rhs)
        {
            return lhs.less(rhs);
        }
        inline bool operator==(TestID const& lhs, TestID const& rhs)
        {
            return lhs.equal(rhs);
        }
    } // namespace old
    



    template <typename Uint = std::size_t>
    class Integer_ID
    {
        static_assert((std::is_integral<Uint>::value), "Templated type must be an integral type");
        static_assert((std::is_unsigned<Uint>::value), "Templated type must be an unsigned type");
    public:
        using underlying_type = Uint;

        // Special 6
        //============================================================
        Integer_ID() :
            m_value(s_null_value)
        {}
        explicit Integer_ID(underlying_type const& value) :
            m_value(value)
        {}

        ~Integer_ID() = default;

        Integer_ID(Integer_ID const& other) = default;
        Integer_ID& operator=(Integer_ID const& other) = default;

        Integer_ID(Integer_ID&& other) :
            m_value(std::move(other.m_value))
        {
            // must make sure that which is moved from is nullified
            other.m_value = s_null_value;
        }
        Integer_ID& operator=(Integer_ID && other)
        {
            m_value = std::move(other.m_value);
            // must make sure that which is moved from is nullified
            other.m_value = s_null_value;
            return *this;
        }


        // Interface
        //============================================================
        underlying_type const& value() const    { return m_value; }
        bool is_null() const                    { return m_value == s_null_value; }

        static Integer_ID make_null_id()        { return Integer_ID(); }
    private:
        underlying_type m_value;

        static underlying_type const s_null_value{ 0 };
    };
    


    template <typename Uint>
    inline bool operator==(Integer_ID<Uint> const& lhs, Integer_ID<Uint> const& rhs)
    {
        return lhs.value() == rhs.value();
    }
    template <typename Uint>
    inline bool operator!=(Integer_ID<Uint> const& lhs, Integer_ID<Uint> const& rhs)
    {
        return !operator==(lhs, rhs);
    }
    template <typename Uint>
    inline bool operator<(Integer_ID<Uint> const& lhs, Integer_ID<Uint> const& rhs)
    {
        return lhs.value() < rhs.value();
    }
    template <typename Uint>
    inline bool operator>(Integer_ID<Uint> const& lhs, Integer_ID<Uint> const& rhs)
    {
        return operator==(rhs, lhs);
    }
    template <typename Uint>
    inline bool operator<=(Integer_ID<Uint> const& lhs, Integer_ID<Uint> const& rhs)
    {
        return !operator>(lhs, rhs);
    }
    template <typename Uint>
    inline bool operator>=(Integer_ID<Uint> const& lhs, Integer_ID<Uint> const& rhs)
    {
        return !operator<(lhs, rhs);
    }

    /*
    We want this to have all the functionality of Integer_ID, with just an extra level of
    type protection. This means that Typed_Integer_ID<A> cannot be converted to Typed_Integer_ID<B>
    since that makes no sense (it would be like casting unrelated pointers).
    */
    template <typename T, typename Uint = std::size_t>
    class Bound_Integer_ID
    {
    public:
        using bound_type = T;
        using underlying_type = typename Integer_ID < Uint >::underlying_type;

        // Special 6
        //============================================================
        Bound_Integer_ID() :
            m_value()
        {}

        // Is this constructor wanted? It definatley shouldn't be implicit
        explicit Bound_Integer_ID(Integer_ID < Uint > const& value) :
            m_value(value)
        {}
        explicit Bound_Integer_ID(underlying_type const& value) :
            m_value(value)
        {}
        
        ~Bound_Integer_ID() = default;

        Bound_Integer_ID(Bound_Integer_ID const& other) = default;
        Bound_Integer_ID& operator=(Bound_Integer_ID const& other) = default;

        // have to manually define move so that the manually defined move in Integer_ID is used
        Bound_Integer_ID(Bound_Integer_ID&& other) :
            m_value(std::move(other.m_value))
        {
        }
        Bound_Integer_ID& operator=(Bound_Integer_ID && other)
        {
            m_value = std::move(other.m_value);
        }

        // Interface
        //============================================================
        underlying_type const& value() const        { return m_value.value(); }
        bool is_null() const                        { return m_value.is_null(); }

        Integer_ID < Uint > unbound_id() const      { return m_value; }

        static Bound_Integer_ID make_null_id()      { return Bound_Integer_ID(); }
    private:
        Integer_ID < Uint > m_value;
    };


    template <typename T, typename Uint>
    inline bool operator==(Bound_Integer_ID<T, Uint> const& lhs, Bound_Integer_ID<T, Uint> const& rhs)
    {
        return lhs.value() == rhs.value();
    }
    template <typename T, typename Uint>
    inline bool operator!=(Bound_Integer_ID<T, Uint> const& lhs, Bound_Integer_ID<T, Uint> const& rhs)
    {
        return !operator==(lhs, rhs);
    }
    template <typename T, typename Uint>
    inline bool operator<(Bound_Integer_ID<T, Uint> const& lhs, Bound_Integer_ID<T, Uint> const& rhs)
    {
        return lhs.value() < rhs.value();
    }
    template <typename T, typename Uint>
    inline bool operator>(Bound_Integer_ID<T, Uint> const& lhs, Bound_Integer_ID<T, Uint> const& rhs)
    {
        return operator==(rhs, lhs);
    }
    template <typename T, typename Uint>
    inline bool operator<=(Bound_Integer_ID<T, Uint> const& lhs, Bound_Integer_ID<T, Uint> const& rhs)
    {
        return !operator>(lhs, rhs);
    }
    template <typename T, typename Uint>
    inline bool operator>=(Bound_Integer_ID<T, Uint> const& lhs, Bound_Integer_ID<T, Uint> const& rhs)
    {
        return !operator<(lhs, rhs);
    }




    template <typename Uint = std::size_t>
    class Integer_ID_Factory
    {
        static_assert((std::is_integral<Uint>::value), "Templated type must be an integral type");
        static_assert((std::is_unsigned<Uint>::value), "Templated type must be an unsigned type");
    public:
        // Typedefs
        //============================================================
        using id_type = Integer_ID < Uint >;
        using underlying_type = typename id_type::underlying_type;

        // Special 6
        //============================================================
        Integer_ID_Factory() :
            m_revoked_ids{},
            m_next_value(0)
        {}

        // Interface
        //============================================================
        id_type make_null_id() const
        { 
            return id_type::make_null_id(); 
        }
        id_type make_new_id()
        {
            id_type new_id{};
            if (m_revoked_ids.empty())
            {
                new_id = id_type{ ++m_next_value };
            }
            else
            {
                new_id = m_revoked_ids.front();
                m_revoked_ids.pop();
            }
            return new_id;
        }

        void revoke_id(id_type const& id)
        {
            if (!id.is_null())
            {
                m_revoked_ids.push(id);
            }
        }
    
    private:
        std::queue<id_type> m_revoked_ids;
        underlying_type m_next_value;
    };


    template <typename T, typename Uint = std::size_t>
    class Bound_Integer_ID_Factory
    {
    public:
        // Typedefs
        //============================================================
        using bound_type = T;
        using id_type = Bound_Integer_ID < bound_type, Uint >;
        using underlying_type = typename id_type::underlying_type;

        // Special 6
        //============================================================
        Bound_Integer_ID_Factory() = default;

        // Interface
        //============================================================
        id_type make_null_id() const        { return id_type::make_null_id(); }
        id_type make_new_id()               { return id_type(m_factory.make_new_id()); }
        void revoke_id(id_type const& id)   { m_factory.revoke_id(id.unbound_id()); }

    private:
        using underlying_factory = Integer_ID_Factory < Uint >;

        underlying_factory m_factory;
    };

    
    // Test all of TestID in this function.
    void test();

} // namespace integer_id



#endif // INTEGER_ID_H