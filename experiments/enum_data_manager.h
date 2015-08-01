#ifndef ENUM_DATA_MANAGER_H
#define ENUM_DATA_MANAGER_H
/*
Following the enum testing, can a type templated using the enum then be bolted together?
*/
#include "enum_stuff.h"
#include <map>

namespace enum_data_manager
{
    using enum_stuff::DataEnum;
    using enum_stuff::DataType;
    using enum_stuff::DataEnumHolder;

    using DataID = unsigned int;

    template <DataEnum DE>
    class DataManager
    {
    protected:
        using key_type = DataID;
        using value_type = DataType < DE >;
        using DataMap = std::map < key_type, value_type >;

        // implicit default constructor etc.

        value_type const& get_value(key_type key) const { return m_dataMap.at(key); }
        void set_value(key_type key, value_type const& value) { m_dataMap[key] = value; }

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
        DataType<DE> const& get_value(key_type key) const { return DataManager<DE>::get_value(key); }
        template <DataEnum DE>
        void set_value(key_type key, DataType<DE> const& value) { DataManager<DE>::set_value(key, value); }

        // access by the actual type
        template <typename T>
        T const& get_value(key_type key) const { return DataManager<DataEnumHolder<T>::enum_value>::get_value(key); }
        template <typename T>
        void set_value(key_type key, T const& value) { DataManager<DataEnumHolder<T>::enum_value>::set_value(key, value); }

    };

    void test();
} // namespace enum_data_manager


#endif // ENUM_DATA_MANAGER_H