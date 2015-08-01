#ifndef ENUM_STUFF_H
#define ENUM_STUFF_H
/*
Playing with scoped enums and templates for potential typeswitching stuff...
*/
#include <string>
#include <type_traits>

namespace enum_stuff
{

    // 1 - Start with an enum of some types
    // ==================================================
    enum class DataEnum : int
    {
        Undefined = 0,
        Bool,
        Int,
        Float,
        String
    };
    // Must have a placeholder class for types we haven't setup
    // This should probably stop compiling if used
    class UndefinedType
    {
    public:
        // If this doesn't tell you not to use this class, nothing will.
        UndefinedType() = delete;
        ~UndefinedType() = delete;
        UndefinedType(UndefinedType const& other) = delete;
        UndefinedType& operator=(UndefinedType const& other) = delete;
        UndefinedType(UndefinedType&& other) = delete;
        UndefinedType& operator=(UndefinedType&& other) = delete;
    };


    // 2 - Convert the enum to types
    // ==================================================
    template <DataEnum DE>
    struct DataTypeHolder
    {
        static_assert(true, "Attempt to use a type not compatible with DataEnum");
        using type = UndefinedType;
    };

    // 3 - Alias the template
    // ==================================================
    template <DataEnum DE>
    using DataType = typename DataTypeHolder<DE>::type;


    // 4 - specialise the template for each type
    // ==================================================
    template <>
    struct DataTypeHolder < DataEnum::Bool >
    {
        using type = bool;
    };
    template <>
    struct DataTypeHolder < DataEnum::Int >
    {
        using type = int;
    };
    template <>
    struct DataTypeHolder < DataEnum::Float >
    {
        using type = float;
    };
    template <>
    struct DataTypeHolder < DataEnum::String >
    {
        using type = std::string;
    };

    // We can now move from enum to type: DataType<DataEnum::Bool> == bool
    // What about the other way around?

    // 5 - constexpr function to move from type to enum
    // ==================================================
    template <typename T = DataType<DataEnum::Undefined> >
    struct DataEnumHolder
    {
        static DataEnum const enum_value{ DataEnum::Undefined };
    };


    // 6 - specialise the template for each type, without using the type directly...
    // ==================================================
    template <>
    struct DataEnumHolder<DataType<DataEnum::Bool> >
    {
        static DataEnum const enum_value{ DataEnum::Bool };
    };
    template <>
    struct DataEnumHolder<DataType<DataEnum::Int> >
    {
        static DataEnum const enum_value{ DataEnum::Int };
    };
    template <>
    struct DataEnumHolder<DataType<DataEnum::Float> >
    {
        static DataEnum const enum_value{ DataEnum::Float };
    };

    template <>
    struct DataEnumHolder<DataType<DataEnum::String> >
    {
        static DataEnum const enum_value{ DataEnum::String };
    };

    // Now we can do: DataEnumHolder<bool>::enum_value == DataEnum::Bool

    // We could just specialise this instead?
    template <typename T>
    /*constexpr*/ DataEnum get_enum()
    {
        return DataEnumHolder<T>::enum_value;
    }

    void test();
} // namespace enum_stuff


#endif