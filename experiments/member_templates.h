#ifndef MEMBER_TEMPLATES_H
#define MEMBER_TEMPLATES_H

#include <iostream>

/*
A test of how the specialisation of templated member functions have to be declared
and implemented.
*/

namespace member_templates
{

    class MajorID
    {
    };

    class MinorID
    {
    };

    class MajorID_Manager
    {
    public:
        template <typename T>
        void minorid_operation_1(MinorID minorid);

        template <typename T>
        void minorid_operation_2(MinorID minorid, T const& value);

        template <typename T>
        void minorid_operation_3(MinorID minorid, int index, T const& value);

        template <typename T>
        void minorid_operation_4(MinorID minorid, T const& value, int index);
    };

    template <>
    void MajorID_Manager::minorid_operation_1<MajorID>(MinorID minorid);
    template <>
    void MajorID_Manager::minorid_operation_2<MajorID>(MinorID minorid, MajorID const& value);
    template <>
    void MajorID_Manager::minorid_operation_3<MajorID>(MinorID minorid, int index, MajorID const& value);
    template <>
    void MajorID_Manager::minorid_operation_4<MajorID>(MinorID minorid, MajorID const& value, int index);

    // Test this code section
    void test();

} // namespace member_templates

template <typename T>
void member_templates::MajorID_Manager::minorid_operation_1(MinorID minorid)
{
    std::cout << "minorid_operation_1<T>(MinorID)" << std::endl;
}
template <typename T>
void member_templates::MajorID_Manager::minorid_operation_2(MinorID minorid, T const& value)
{
    std::cout << "minorid_operation_2<T>(MinorID, T const&)" << std::endl;
}
template <typename T>
void member_templates::MajorID_Manager::minorid_operation_3(MinorID minorid, int index, T const& value)
{
    std::cout << "minorid_operation_3<T>(MinorID, int, T const&)" << std::endl;
}
template <typename T>
void member_templates::MajorID_Manager::minorid_operation_4(MinorID minorid, T const& value, int index)
{
    std::cout << "minorid_operation_4<T>(MinorID, T const&, int)" << std::endl;
}

#endif