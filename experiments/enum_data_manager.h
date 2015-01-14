#ifndef ENUM_DATA_MANAGER_H
#define ENUM_DATA_MANAGER_H
/*
Following the enum testing, can a type templated using the enum then be bolted together?
*/
#include "enum_stuff.h"
#include <map>

using DataID = unsigned int;

template <DataEnum DE>
class DataManager
{
protected:
    using key_type = DataID;
    using value_type = DataType < DE > ;
    using DataMap = std::map < key_type, value_type >;

    // implicit default constructor etc.

    value_type const& getValue(key_type key) const { return m_dataMap.at(key); }
    void setValue(key_type key, value_type const& value) { m_dataMap[key] = value; }

    typename DataMap::iterator begin() { return m_dataMap.begin(); }
    typename DataMap::iterator end() { return m_dataMap.end(); }
private:
    DataMap m_dataMap;
};

// You could do this with types rather than enum values. Do you actually gain anything by doing it this way?
class MultiDataManager :
    private DataManager<DataEnum::Bool>,
    private DataManager<DataEnum::Int>,
    private DataManager<DataEnum::Float>,
    private DataManager<DataEnum::String>
{
public:
    using key_type = DataID;

    // implicit default constructor etc.

    // access data by the enum type
    template <DataEnum DE>
    DataType<DE> const& getValue(key_type key) const { return DataManager<DE>::getValue(key); }
    template <DataEnum DE>
    void setValue(key_type key, DataType<DE> const& value) { DataManager<DE>::setValue(key,value); }

    // access by the actual type
    template <typename T>
    T const& getValue(key_type key) const { return DataManager<DataEnumHolder<T>::enumValue>::getValue(key); }
    template <typename T>
    void setValue(key_type key, T const& value) { DataManager<DataEnumHolder<T>::enumValue>::setValue(key, value); }
    
};

#endif // ENUM_DATA_MANAGER_H