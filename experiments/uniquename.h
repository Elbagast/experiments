#ifndef UNIQUENAME_H
#define UNIQUENAME_H

#include <set>
#include <string>
#include "datapoolvalue.h"

class UniqueNamePool
{
public:
    using string_type = std::string;
    using pool_type = std::set < DataPoolValue < string_type > > ;
    using iterator = pool_type::iterator;

private:
    pool_type m_poolValues;
};

class UniqueName
{
public:
    using string_type = std::string;

    // Special 6
    //============================================================
    explicit UniqueName(UniqueNamePool* pool, string_type const& value);
    ~UniqueName();

    // NOTE: copy behaviour is not a true copy...
    UniqueName(UniqueName const& other);
    UniqueName& operator=(UniqueName const& value);

    string_type& get();
    string_type const& cget() const;

    // Is this value available for use? i.e. is it not in the pool?
    bool canSetTo(string_type const& value) const;
    // Return true if the value was changed.
    bool set(string_type const& value);

    UniqueNamePool* getPool() const;
private:
    UniqueNamePool* m_pool;
    UniqueNamePool::iterator m_value;
};

#endif // UNIQUENAME_H