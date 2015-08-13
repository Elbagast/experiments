#ifndef REFERENCE_COUNTING_H
#define REFERENCE_COUNTING_H

/*
Experiments into separating out reference counting logic so that
it only needs to be debugged once.

What do we need:
- An ID class
    - a way of making a new and unique one whenever needed
    - a way of making an invalid one whenever needed
    - comparison operators
- A Manager class
- An Index class
    - contains an id and a pointer to the manager it is related to

Turns out trying to make this operation generic is a total pain in the ass,
mostly because of recursion in the templates...
*/

#include <map>
#include <cassert>
#include <type_traits>
#include <numeric>

namespace reference_counting
{
    // forward declarations
    template <typename T, typename ID, typename ID_Factory, typename Count>
    class Reference_Counting_Manager;

    template <typename Manager>
    class Reference_Counted_Index;

    
    /*
    The thing that will provide ref counted objects.
    */
    template <typename T, typename ID, typename ID_Factory, typename Count = std::size_t>
    class Reference_Counting_Manager
    {
        // Stop compiling if Count is not an unsigned integer
        static_assert((std::is_integral<Count>::value && std::is_unsigned<Count>::value), "Templated type must be an unsigned integral type");
    public:
        // Typedefs
        //============================================================
        using value_type = T;
        using id_type = ID;
        using id_factory_type = ID_Factory;
        using reference_count_type = Count;

        using index_type = typename Reference_Counted_Index < Reference_Counting_Manager >;

        index_type make_null_index()
        {
            return index_type( this, m_id_factory.make_null_id() );
        }

        index_type emplace_data(value_type&& data)
        {
            id_type new_id = m_id_factory.make_new_id();
            m_map.emplace(new_id, Wrapper(std::forward<value_type>(data)));
            return index_type(this, new_id);
        }

        bool has_data(id_type const& id) const
        {
            return !id.is_null() && m_map.find(id) != m_map.cend();
        }

        value_type* data(id_type const& id)
        {
            if (!id.is_null())
            {
                auto found_iterator = m_map.find(id);
                if (found_iterator != m_map.end())
                {
                    return &(found_iterator->second.m_data);
                }
            }
            return nullptr;
        }
        value_type const* cdata(id_type const& id) const
        {
            if (!id.is_null())
            {
                auto found_iterator = m_map.find(id);
                if (found_iterator != m_map.end())
                {
                    return &(found_iterator->second.m_data);
                }
            }
            return nullptr;
        }

        reference_count_type reference_count(id_type const& id) const
        {
            if (!id.is_null())
            {
                auto found_iterator = m_map.find(id);
                if (found_iterator != m_map.end())
                {
                    return found_iterator->second.m_reference_count;
                }
            }
            return std::numeric_limits<reference_count_type>::min();
        }

        bool is_null(id_type const& id) const
        {
            return id.is_null();
        }
        bool is_valid(id_type const& id) const
        {
            return has_data(id);
        }

        void increment_reference_count(id_type const& id)
        {
            if (is_valid(id))
            {
                auto found_iterator = m_map.find(id);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    assert(found_iterator->second.m_reference_count != std::numeric_limits<reference_count_type>::max()); // must not be max when we get here...
                    found_iterator->second.m_reference_count += 1;
                }
            }
        }
        void decrement_reference_count(id_type const& id)
        {
            if (is_valid(id))
            {
                auto found_iterator = m_map.find(id);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    assert(found_iterator->second.m_reference_count != std::numeric_limits<reference_count_type>::min()); // must not be zero when we get here...
                    found_iterator->second.m_reference_count -= 1;
                    if (found_iterator->second.m_reference_count == std::numeric_limits<reference_count_type>::min())
                    {
                        m_map.erase(id);
                        m_id_factory.revoke_id(id);
                    }
                }
            }
        }

    private:
        // this could just be done with a std::pair...
        class Wrapper
        {
        public:
            Wrapper() : 
                m_data(), 
                m_reference_count(0)
            {}
            explicit Wrapper(value_type&& data) :
                m_data(std::move(data)),
                m_reference_count(0)
            {}

            value_type m_data;
            reference_count_type m_reference_count;
        };

        using map_type = std::map < id_type, Wrapper >;

        id_factory_type m_id_factory;
        map_type m_map;
    };



    /*
    The thing that will we ref counted. This object needs to be freely copyable and assignable for flexibility.
    */
    template <typename Manager>
    class Reference_Counted_Index
    {
        //friend typename Manager;
    public:
        // Typedefs
        //============================================================
        using manager_type = typename Manager;

        using value_type = typename manager_type::value_type;
        using id_type = typename manager_type::id_type;
        using reference_count_type = typename manager_type::reference_count_type;

        // Special 6
        //============================================================
        Reference_Counted_Index(manager_type* manager, id_type const& id) :
            mp_manager{ manager },
            m_id{ id }
        {
            mp_manager->increment_reference_count(m_id);
        }

        ~Reference_Counted_Index()
        {
            mp_manager->decrement_reference_count(m_id);
        }
    
        Reference_Counted_Index(Reference_Counted_Index const& other) :
            mp_manager{ other.mp_manager },
            m_id{ other.m_id }
        {
            mp_manager->increment_reference_count(m_id);
        }
        Reference_Counted_Index& operator=(Reference_Counted_Index const& other)
        {
            // check for equivalence rather than self assignment
            if (m_id != other.m_id)
            {
                id_type old_id{ m_id };
                m_id = other.m_id;
                mp_manager->increment_reference_count(m_id); // this is a new holder of this value so increment
                mp_manager->decrement_reference_count(old_id); // decrement after as this may trigger destruction
            }
            return *this;
        }

        Reference_Counted_Index(Reference_Counted_Index && other) :
            mp_manager{ std::move(other.mp_manager) },
            m_id{ std::move(other.m_id) }
        {
        }
        Reference_Counted_Index& operator=(Reference_Counted_Index && other)
        {
            id_type old_id{ m_id };
            m_id = std::move(other.m_id);
            mp_manager->decrement_reference_count(old_id); // decrement after as this may trigger destruction
            return *this;
        }


        // Interface
        //============================================================
        value_type* data()                                  { return mp_manager->data(m_id); }
        value_type const* cdata() const                     { return mp_manager->cdata(m_id); }

        bool is_null() const                                { return mp_manager->is_null(m_id); }
        bool is_valid() const                               { return mp_manager->is_valid(m_id); }
        id_type const& id() const                           { return m_id; }
        reference_count_type reference_count() const        { return mp_manager->reference_count(m_id); }

        manager_type* manager()                             { return mp_manager; }
        manager_type const* cmanager() const                { return mp_manager; }
    private:
        manager_type* mp_manager; // must be pointer to enable assignment
        id_type m_id;
    };




    void test();

} // namespace reference_counting

//==================================================================================================================
/*
An alternative setup...
*/

namespace reference_counting_2
{
    // forward declarations
    template <typename T, typename ID, typename Count>
    class Reference_Counting_Storage;

    template <typename T, typename ID, typename Count, typename ID_Factory>
    class Reference_Counting_Manager;

    //template <typename T, typename ID, typename Count>
    //class Reference_Counted_Index;

    template <typename Manager>
    class Reference_Counted_Index;


    /*
    The thing that will store ref counted objects.
    */


    template <typename T, typename ID, typename Count = std::size_t>
    class Reference_Counting_Storage
    {
    public:
        // Typedefs
        //============================================================
        using value_type = T;
        using id_type = ID;
        using reference_count_type = Count;

        id_type emplace_data(id_type const& id, value_type&& data)
        {
            m_map.emplace(id, Wrapper(std::forward<value_type>(data)));
            return id_type(id);
        }

        bool is_null(id_type const& id) const
        {
            return id.is_null();
        }

        bool is_valid(id_type const& id) const
        {
            return has_data(id);
        }

        bool has_data(id_type const& id) const
        {
            return !id.is_null() && m_map.find(id) != m_map.cend();
        }

        value_type* data(id_type const& id)
        {
            if (!id.is_null())
            {
                auto found_iterator = m_map.find(id);
                if (found_iterator != m_map.end())
                {
                    return &(found_iterator->second.m_data);
                }
            }
            return nullptr;
        }
        value_type const* cdata(id_type const& id) const
        {
            if (!id.is_null())
            {
                auto found_iterator = m_map.find(id);
                if (found_iterator != m_map.end())
                {
                    return &(found_iterator->second.m_data);
                }
            }
            return nullptr;
        }

        reference_count_type reference_count(id_type const& id) const
        {
            if (!id.is_null())
            {
                auto found_iterator = m_map.find(id);
                if (found_iterator != m_map.end())
                {
                    return found_iterator->second.m_reference_count;
                }
            }
            return 0;
        }

        void increment_reference_count(id_type const& id)
        {
            if (is_valid(id))
            {
                auto found_iterator = m_map.find(id);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    
                    found_iterator->second.m_reference_count += 1;
                }
            }
        }
        bool decrement_reference_count(id_type const& id)
        {
            if (is_valid(id))
            {
                auto found_iterator = m_map.find(id);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    assert(found_iterator->second.m_reference_count != 0); // must not be zero when we get here...
                    found_iterator->second.m_reference_count -= 1;
                    if (found_iterator->second.m_reference_count == 0)
                    {
                        m_map.erase(id);
                        return true;
                    }
                }
            }
            return false;
        }

    private:
        // this could just be done with a std::pair...
        class Wrapper
        {
        public:
            Wrapper() :
                m_data(),
                m_reference_count(0)
            {}
            explicit Wrapper(value_type&& data) :
                m_data(std::move(data)),
                m_reference_count(0)
            {}

            value_type m_data;
            reference_count_type m_reference_count;
        };

        using map_type = std::map < id_type, Wrapper >;

        map_type m_map;
    };




    /*
    The thing that will provide ref counted objects.
    */
    template <typename T, typename ID, typename ID_Factory, typename Count = std::size_t>
    class Reference_Counting_Manager
    {
    public:
        // Typedefs
        //============================================================
        using value_type = T;
        using id_type = ID;
        using id_factory_type = ID_Factory;
        using reference_count_type = Count;

        using storage_type = typename Reference_Counting_Storage < value_type, id_type, reference_count_type >;
        using index_type = typename Reference_Counted_Index < Reference_Counting_Manager >;


        index_type make_null_index()
        {
            return index_type(this, m_id_factory.make_null_id());
        }

        index_type emplace_data(value_type&& data)
        {
            id_type new_id = m_id_factory.make_new_id();
            m_storage.emplace_data(new_id, std::forward<value_type>(data));
            return index_type(this, new_id);
        }

        bool has_data(id_type const& id) const
        {
            return m_storage.has_data(id);
        }

        value_type* data(id_type const& id)
        {
            return m_storage.data(id);
        }
        value_type const* cdata(id_type const& id) const
        {
            return m_storage.cdata(id);
        }

        reference_count_type reference_count(id_type const& id) const
        {
            return m_storage.reference_count(id);
        }

        bool is_null(id_type const& id) const
        {
            return m_storage.is_null(id);
        }
        bool is_valid(id_type const& id) const
        {
            return m_storage.has_data(id);
        }

        void increment_reference_count(id_type const& id)
        {
            m_storage.increment_reference_count(id);
        }
        void decrement_reference_count(id_type const& id)
        {
            if (m_storage.decrement_reference_count(id))
            {
                m_id_factory.revoke_id(id);
            }
        }

    private:
        id_factory_type m_id_factory;
        storage_type m_storage;
    };


    /*
    The thing that will we ref counted. This object needs to be freely copyable and assignable for flexibility.
    */
    template <typename Manager>
    class Reference_Counted_Index
    {
    public:
        // Typedefs
        //============================================================
        using manager_type = typename Manager;

        using value_type = typename manager_type::value_type;
        using id_type = typename manager_type::id_type;
        using reference_count_type = typename manager_type::reference_count_type;


        // Special 6
        //============================================================
    private:
        Reference_Counted_Index(manager_type* manager, id_type const& id) :
            mp_manager{ manager },
            m_id{ id }
        {
            mp_manager->increment_reference_count(m_id);
        }
    public:
        ~Reference_Counted_Index()
        {
            mp_manager->decrement_reference_count(m_id);
        }

        Reference_Counted_Index(Reference_Counted_Index const& other) :
            mp_manager{ other.mp_manager },
            m_id{ other.m_id }
        {
            mp_manager->increment_reference_count(m_id);
        }
        Reference_Counted_Index& operator=(Reference_Counted_Index const& other)
        {
            // check for equivalence rather than self assignment
            if (m_id != other.m_id)
            {
                id_type old_id{ m_id };
                m_id = other.m_id;
                mp_manager->increment_reference_count(m_id); // this is a new holder of this value so increment
                mp_manager->decrement_reference_count(old_id); // decrement after as this may trigger destruction
            }
            return *this;
        }

        Reference_Counted_Index(Reference_Counted_Index && other) :
            mp_manager{ std::move(other.mp_manager) },
            m_id{ std::move(other.m_id) }
        {
        }
        Reference_Counted_Index& operator=(Reference_Counted_Index && other)
        {
            id_type old_id{ m_id };
            m_id = std::move(other.m_id);
            mp_manager->decrement_reference_count(old_id); // decrement after as this may trigger destruction
            return *this;
        }


        // Interface
        //============================================================
        value_type* data()                                  { return mp_manager->data(m_id); }
        value_type const* cdata() const                     { return mp_manager->cdata(m_id); }

        bool is_null() const                                { return mp_manager->is_null(m_id); }
        bool is_valid() const                               { return mp_manager->is_valid(m_id); }
        id_type const& id() const                           { return m_id; }
        reference_count_type reference_count() const        { return mp_manager->reference_count(m_id); }
    private:
        manager_type* mp_manager; // must be pointer to enable assignment
        id_type m_id;
    };




    void test();

} // namespace reference_counting_2



#endif // REFERENCE_COUNTING_H