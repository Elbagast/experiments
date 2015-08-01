#ifndef DATA_POOL_VALUE_H
#define DATA_POOL_VALUE_H
/*
Following on from the enum stuff, what about sharing data values...
*/
#include <map>
#include <iosfwd>
#include <type_traits>

namespace data_pool_value
{
    template <typename T>
    class Data_Pool_Value
    {
    public:
        using value_type = T;
        using number_type = std::size_t;

        // Special 6
        //============================================================
        // There must be a value for this class to make any sense
        // implicit converison??????
        explicit Data_Pool_Value(value_type const& value) :
            m_iterator{ add_to_pool(value) }
        {}
        explicit Data_Pool_Value(value_type && value) :
            m_iterator{ add_to_pool(std::forward<value_type>(value)) }
        {}
        // Destructor adjusts the ref count of the value
        ~Data_Pool_Value()
        {
            // Decrement ref count and destroy the value if necessary.
            remove_from_pool(m_iterator);
        }

        // Copying adds to the reference count of the shared value
        Data_Pool_Value(Data_Pool_Value const& other) :
            m_iterator{ increment_iterator(other.m_iterator) }
        {}
        // Copy-assignment does nothing if there is self assignment, or the underlying values are the same
        Data_Pool_Value& operator=(Data_Pool_Value const& other)
        {
            // check for self assignment, and assignment of the same underlying value (there would be no change either way)
            if (this != &other)
            {
                auto old_iterator = m_iterator;
                m_iterator = increment_iterator(other.m_iterator);
                remove_from_pool(old_iterator);
            }
            return *this;
        }

        // God damn you msvc
        //Data_Pool_Value(Data_Pool_Value && other) = default;
        //Data_Pool_Value& operator=(Data_Pool_Value && other) = default;

        // Interface
        //============================================================
        void set(value_type const& value)
        {
            // if the iterator isn't already pointing at something that stores this value
            if (m_iterator->first != value)
            {
                auto old_iterator = m_iterator;
                m_iterator = add_to_pool(value);
                remove_from_pool(old_iterator);
            }
        }
        value_type& get() 
        {
            return m_iterator->first;
        }
        value_type const& cget() const
        {
            return m_iterator->first;
        }
        number_type refCount() const
        {
            return m_iterator->second;
        }
        explicit operator value_type() const
        {
            return value_type(cget());
        }
    private:
        using DataPool = std::map<value_type, number_type>;
        using iterator = typename DataPool::iterator;

        // Static Helpers
        //============================================================

        // Take an iterator and add a copy of its value to the pool, then return it.
        static iterator increment_iterator(iterator valueIterator)
        {
            valueIterator->second += 1;
            return valueIterator;
        }

        // Get a pointer to the item in the pool that contains this value
        static iterator add_to_pool(value_type && value)
        {
            // Is there an item with this value?
            auto found_iterator = s_data_pool.find(value);
            // if there is
            if (found_iterator != s_data_pool.end())
            {
                // increment the ref count
                found_iterator->second += 1;
                // return it
                return found_iterator;
            }
            // there isn't
            else
            {
                // make an entry in the static map with a ref count of 1
                auto insert_result_pair = s_data_pool.insert(std::make_pair(std::forward<value_type>(value), 1)); // pair<iterator, bool>
                // return it
                return insert_result_pair.first;

                // Does all the above but is a bit hard to read
                //return &*(s_data_pool.insert(std::make_pair(value, 1)).first);
            }
        }
        static iterator add_to_pool(value_type const& value)
        {
            // Is there an item with this value?
            auto found_iterator = s_data_pool.find(value);
            // if there is
            if (found_iterator != s_data_pool.end())
            {
                // increment the ref count
                found_iterator->second += 1;
                // return it
                return found_iterator;
            }
            // there isn't
            else
            {
                // make an entry in the static map with a ref count of 1
                auto insert_result_pair = s_data_pool.insert(std::make_pair(value, 1)); // pair<iterator, bool>
                // return it
                return insert_result_pair.first;

                // Does all the above but is a bit hard to read
                //return &*(s_data_pool.insert(std::make_pair(value, 1)).first);
            }
        }
    
        // Decrement ref count and destroy the value if necessary.
        static void remove_from_pool(iterator item)
        {
            // decrement the ref count of the item
            item->second -= 1;
            // if this was the last one, remove it from the pool
            if (item->second == 0)
                s_data_pool.erase(item->first);
        }
    
        // Data
        //============================================================
        iterator m_iterator;
    
        // Static Data
        //============================================================
        static DataPool s_data_pool;
    };

    template <typename T>
    typename Data_Pool_Value<T>::DataPool Data_Pool_Value<T>::s_data_pool = Data_Pool_Value<T>::DataPool{};

    // Comparison operators
    //============================================================

    template <typename T> bool operator==(Data_Pool_Value<T> const& lhs, Data_Pool_Value<T> const& rhs) { return lhs.cget() == rhs.cget(); }
    template <typename T> bool operator!=(Data_Pool_Value<T> const& lhs, Data_Pool_Value<T> const& rhs) { return !operator==(lhs, rhs); }
    template <typename T> bool operator< (Data_Pool_Value<T> const& lhs, Data_Pool_Value<T> const& rhs) { return lhs.cget() < rhs.cget(); }
    template <typename T> bool operator> (Data_Pool_Value<T> const& lhs, Data_Pool_Value<T> const& rhs) { return operator<(rhs, lhs); }
    template <typename T> bool operator<=(Data_Pool_Value<T> const& lhs, Data_Pool_Value<T> const& rhs) { return !operator>(lhs, rhs); }
    template <typename T> bool operator>=(Data_Pool_Value<T> const& lhs, Data_Pool_Value<T> const& rhs) { return !operator<(lhs, rhs); }

    // These other overloads seem to make things simpler than worrying about conversion operators...

    template <typename T> bool operator==(Data_Pool_Value<T> const& lhs, T const& rhs) { return lhs.cget() == rhs; }
    template <typename T> bool operator!=(Data_Pool_Value<T> const& lhs, T const& rhs) { return !operator==(lhs, rhs); }
    template <typename T> bool operator< (Data_Pool_Value<T> const& lhs, T const& rhs) { return lhs.cget() < rhs; }
    template <typename T> bool operator> (Data_Pool_Value<T> const& lhs, T const& rhs) { return operator<(rhs, lhs); }
    template <typename T> bool operator<=(Data_Pool_Value<T> const& lhs, T const& rhs) { return !operator>(lhs, rhs); }
    template <typename T> bool operator>=(Data_Pool_Value<T> const& lhs, T const& rhs) { return !operator<(lhs, rhs); }

    template <typename T> bool operator==(T const& lhs, Data_Pool_Value<T> const& rhs) { return lhs == rhs.cget(); }
    template <typename T> bool operator!=(T const& lhs, Data_Pool_Value<T> const& rhs) { return !operator==(lhs, rhs); }
    template <typename T> bool operator< (T const& lhs, Data_Pool_Value<T> const& rhs) { return lhs < rhs.cget(); }
    template <typename T> bool operator> (T const& lhs, Data_Pool_Value<T> const& rhs) { return operator<(rhs, lhs); }
    template <typename T> bool operator<=(T const& lhs, Data_Pool_Value<T> const& rhs) { return !operator>(lhs, rhs); }
    template <typename T> bool operator>=(T const& lhs, Data_Pool_Value<T> const& rhs) { return !operator<(lhs, rhs); }

    // Stream operators
    //============================================================
    // The underlying type must have an equivalent operator for these to work

    template <typename C, typename CTraits, typename T> 
    std::basic_ostream<C, CTraits>& operator<<(std::basic_ostream<C, CTraits>& stream, Data_Pool_Value<T> const& value) { return operator<<(stream, value.cget()); }

    template <typename C, typename CTraits, typename T>
    std::basic_istream<C, CTraits>& operator>>(std::basic_istream<C, CTraits>& stream, Data_Pool_Value<T>& value) { return operator>>(stream, value.get()); }



    void test();

} // namespace data_pool_value

#endif // DATA_POOL_VALUE_H