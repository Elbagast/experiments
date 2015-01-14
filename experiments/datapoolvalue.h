#ifndef DATAPOOLVALUE_H
#define DATAPOOLVALUE_H
/*
Following on from the enum stuff, what about sharing data values...
*/
#include <map>
#include <iosfwd>
#include <type_traits>

template <typename T>
class DataPoolValue
{
public:
    using value_type = T;
    using number_type = std::size_t;

    // Special 6
    //============================================================
    // There must be a value for this class to make any sense
    // implicit converison??????
    explicit DataPoolValue(value_type const& value) :
        m_iterator{ addToPool(value) }
    {}
    explicit DataPoolValue(value_type && value) :
        m_iterator{ addToPool(std::forward<value_type>(value)) }
    {}
    // Destructor adjusts the ref count of the value
    ~DataPoolValue()
    {
        // Decrement ref count and destroy the value if necessary.
        removeFromPool(m_iterator);
    }

    // Copying adds to the reference count of the shared value
    DataPoolValue(DataPoolValue const& other) :
        m_iterator{ incrementIterator(other.m_iterator) }
    {}
    // Copy-assignment does nothing if there is self assignment, or the underlying values are the same
    DataPoolValue& operator=(DataPoolValue const& other)
    {
        // check for self assignment, and assignment of the same underlying value (there would be no change either way)
        if (this != &other)
        {
            auto oldIterator = m_iterator;
            m_iterator = incrementIterator(other.m_iterator);
            removeFromPool(oldIterator);
        }
        return *this;
    }

    // God damn you msvc
    //DataPoolValue(DataPoolValue && other) = default;
    //DataPoolValue& operator=(DataPoolValue && other) = default;

    // Interface
    //============================================================
    void set(value_type const& value)
    {
        // if the iterator isn't already pointing at something that stores this value
        if (m_iterator->first != value)
        {
            auto oldIterator = m_iterator;
            m_iterator = addToPool(value);
            removeFromPool(oldIterator);
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
    static iterator incrementIterator(iterator valueIterator)
    {
        valueIterator->second += 1;
        return valueIterator;
    }

    // Get a pointer to the item in the pool that contains this value
    static iterator addToPool(value_type && value)
    {
        // Is there an item with this value?
        auto findValue = s_dataPool.find(value);
        // if there is
        if (findValue != s_dataPool.end())
        {
            // increment the ref count
            findValue->second += 1;
            // return it
            return findValue;
        }
        // there isn't
        else
        {
            // make an entry in the static map with a ref count of 1
            auto insertResultPair = s_dataPool.insert(std::make_pair(std::forward<value_type>(value), 1)); // pair<iterator, bool>
            // return it
            return insertResultPair.first;

            // Does all the above but is a bit hard to read
            //return &*(s_dataPool.insert(std::make_pair(value, 1)).first);
        }
    }
    static iterator addToPool(value_type const& value)
    {
        // Is there an item with this value?
        auto findValue = s_dataPool.find(value);
        // if there is
        if (findValue != s_dataPool.end())
        {
            // increment the ref count
            findValue->second += 1;
            // return it
            return findValue;
        }
        // there isn't
        else
        {
            // make an entry in the static map with a ref count of 1
            auto insertResultPair = s_dataPool.insert(std::make_pair(value, 1)); // pair<iterator, bool>
            // return it
            return insertResultPair.first;

            // Does all the above but is a bit hard to read
            //return &*(s_dataPool.insert(std::make_pair(value, 1)).first);
        }
    }
    
    // Decrement ref count and destroy the value if necessary.
    static void removeFromPool(iterator item)
    {
        // decrement the ref count of the item
        item->second -= 1;
        // if this was the last one, remove it from the pool
        if (item->second == 0)
            s_dataPool.erase(item->first);
    }
    
    // Data
    //============================================================
    iterator m_iterator;
    
    // Static Data
    //============================================================
    static DataPool s_dataPool;
};

template <typename T>
typename DataPoolValue<T>::DataPool DataPoolValue<T>::s_dataPool = DataPoolValue<T>::DataPool{};

// Comparison operators
//============================================================

template <typename T> bool operator==(DataPoolValue<T> const& lhs, DataPoolValue<T> const& rhs) { return lhs.cget() == rhs.cget(); }
template <typename T> bool operator!=(DataPoolValue<T> const& lhs, DataPoolValue<T> const& rhs) { return !operator==(lhs, rhs); }
template <typename T> bool operator< (DataPoolValue<T> const& lhs, DataPoolValue<T> const& rhs) { return lhs.cget() < rhs.cget(); }
template <typename T> bool operator> (DataPoolValue<T> const& lhs, DataPoolValue<T> const& rhs) { return operator<(rhs, lhs); }
template <typename T> bool operator<=(DataPoolValue<T> const& lhs, DataPoolValue<T> const& rhs) { return !operator>(lhs, rhs); }
template <typename T> bool operator>=(DataPoolValue<T> const& lhs, DataPoolValue<T> const& rhs) { return !operator<(lhs, rhs); }

// These other overloads seem to make things simpler than worrying about conversion operators...

template <typename T> bool operator==(DataPoolValue<T> const& lhs, T const& rhs) { return lhs.cget() == rhs; }
template <typename T> bool operator!=(DataPoolValue<T> const& lhs, T const& rhs) { return !operator==(lhs, rhs); }
template <typename T> bool operator< (DataPoolValue<T> const& lhs, T const& rhs) { return lhs.cget() < rhs; }
template <typename T> bool operator> (DataPoolValue<T> const& lhs, T const& rhs) { return operator<(rhs, lhs); }
template <typename T> bool operator<=(DataPoolValue<T> const& lhs, T const& rhs) { return !operator>(lhs, rhs); }
template <typename T> bool operator>=(DataPoolValue<T> const& lhs, T const& rhs) { return !operator<(lhs, rhs); }

template <typename T> bool operator==(T const& lhs, DataPoolValue<T> const& rhs) { return lhs == rhs.cget(); }
template <typename T> bool operator!=(T const& lhs, DataPoolValue<T> const& rhs) { return !operator==(lhs, rhs); }
template <typename T> bool operator< (T const& lhs, DataPoolValue<T> const& rhs) { return lhs < rhs.cget(); }
template <typename T> bool operator> (T const& lhs, DataPoolValue<T> const& rhs) { return operator<(rhs, lhs); }
template <typename T> bool operator<=(T const& lhs, DataPoolValue<T> const& rhs) { return !operator>(lhs, rhs); }
template <typename T> bool operator>=(T const& lhs, DataPoolValue<T> const& rhs) { return !operator<(lhs, rhs); }

// Stream operators
//============================================================
// The underlying type must have an equivalent operator for these to work

template <typename C, typename CTraits, typename T> 
std::basic_ostream<C, CTraits>& operator<<(std::basic_ostream<C, CTraits>& stream, DataPoolValue<T> const& value) { return operator<<(stream, value.cget()); }

template <typename C, typename CTraits, typename T>
std::basic_istream<C, CTraits>& operator>>(std::basic_istream<C, CTraits>& stream, DataPoolValue<T>& value) { return operator>>(stream, value.get()); }

#endif // DATAPOOLITEM_H