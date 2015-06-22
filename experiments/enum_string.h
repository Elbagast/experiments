#ifndef ENUM_STRING_H
#define ENUM_STRING_H

/*
Generating, storing and accessing enum values via a string identifier
*/

#include <map>
#include <string>
#include <type_traits>

namespace enum_string
{
    template <typename I, typename S>
    class Enum_String
    {
    public:
        using integer_type = I;
        using string_type = S;

        static_assert(std::is_integral_type<>::value(integer_type), "Cannot build with a type that is not an integer type");

        static bool has_enum_string(string_type const& value)
        {
            return s_enum_map.find(value) != s_enum_map.end();
        }
        static void register_enum_string(string_type const& value)
        {

        }
    private:
        using map_type = std::map < string_type, integer_type >;
        static map_type s_enum_map;
        static integer_type s_next_enum_value;
    };


} // namespace enum_string

#endif // ENUM_STRING_H