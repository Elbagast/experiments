#ifndef TWO_KEY_MAP_h
#define TWO_KEY_MAP_h

/*
Adapter class for std::map to make an associated container where values have
two distinct key types that can be used. 

UNFINISHED
*/

#include <map>

namespace two_key_map
{

    template <typename T_Short_Key, typename T_Long_Key, typename T>
    class Two_Key_Map
    {
    public:
        using short_key_type = T_Short_Key;
        using long_key_type = T_Long_Key;
    private:
        using internal_key_type = std::pair < short_key_type, long_key_type >;
        using internal_map_type = std::map < internal_key_type, T > ;
        using internal_value_type = typename internal_map_type::value_type;
    public:
        using mapped_type = typename internal_map_type::mapped_type;


    private:
        internal_map_type m_map;
    };

} // namespace two_key_map

#endif //TWO_KEY_MAP_h