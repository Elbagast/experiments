#ifndef BIT_RADIANS_H
#define BIT_RADIANS_H

#include <cstdint>

namespace bit_radians
{
    /*
    An alternative implementation of radians that doesn't use floating point.
    Why?

    - We have an object with a given starting orientation.
    - That orientation is being changed for whatever reason
        e.g. In a given frame of animation it rotates a given amount
    - If the rotation data is stored in floats a lot of the possible values are meaningless to this operation
      since very large or very small values can be stored but not really interact.
    */

    template <typename T>
    class Underlying_Value
    {
    protected:
        using UVT = Underlying_Value < T > ;
        using underlying_type = T;

        explicit Underlying_Value(underlying_type a_value):
            m_value(a_value)
        {}
    
        ~Underlying_Value() = default;

        underlying_type get_value() const
        {
            return m_value;
        }

        void set_value(underlying_type a_value)
        {
            m_value = a_value;
        }

    private:
        underlying_type m_value;
    };


    // Class wrappers for degree and radian angles
    class Radians_Single;
    class Radians_Double;

    class Degrees_Single;
    class Degrees_Double;

    class Radians_Single :
        protected Underlying_Value<float>
    {
    public:
        Radians_Single(float a_value) : UVT(a_value) {}
        using UVT::get_value;
    };

    class Radians_Double :
        protected Underlying_Value<double>
    {
    public:
        Radians_Double(double a_value) : UVT(a_value) {}
        using UVT::get_value;
    };


    class Degrees_Single :
        protected Underlying_Value<float>
    {
    public:
        Degrees_Single(float a_value) : UVT(a_value) {}
        using UVT::get_value;
    };

    class Degrees_Double :
        protected Underlying_Value<double>
    {
    public:
        Degrees_Double(double a_value) : UVT(a_value) {}
        using UVT::get_value;
    };

    // Class that stores an angle in the range (-pi..pi) as a signed integer of the given size.
    // An integer value of 0 is equivalent to a values of 0 and pi radians or 0 and 360 degrees.
    // An integer value of 1 is equivalent to a value of pi/2^bits radians or 360/2^bits degrees.
    // An integer value of N is equivalent to a value of N*pi/2^bits radians or N*360/2^bits degrees.
    class Bit_Degrees_8;
    class Bit_Degrees_16;
    class Bit_Degrees_32;

    class Bit_Degrees;

    // Class that stroes an angle as a signed integer of the given size where the least significant half is
    // 
    class Bit_Angle_16;
    class Bit_Angle_32;
    class Bit_Angle_64;

    class Bit_Angle;

    class Bit_Degrees
    {
    public:
        using underlying_type = std::int16_t;

        explicit Bit_Degrees(Degrees_Single);
        explicit Bit_Degrees(Degrees_Double);
        explicit Bit_Degrees(Radians_Single);
        explicit Bit_Degrees(Radians_Double);

        underlying_type to_underlying_type() const;
        
        Bit_Angle to_bit_angle() const;

        Radians_Single to_radians_single() const;
        Radians_Double to_radians_double() const;

        Degrees_Single to_degrees_single() const;
        Degrees_Double to_degrees_double() const;

    private:
        underlying_type m_value;
    };

    class Bit_Angle
    {
    public:
        using underlying_type = std::int32_t;

        explicit Bit_Angle(Degrees_Single);
        explicit Bit_Angle(Degrees_Double);
        explicit Bit_Angle(Radians_Single);
        explicit Bit_Angle(Radians_Double);

        explicit Bit_Angle(Bit_Degrees);

        underlying_type to_underlying_type() const;

        Bit_Degrees to_bit_degrees() const;

        Radians_Single to_radians_single() const;
        Radians_Double to_radians_double() const;

        Degrees_Single to_degrees_single() const;
        Degrees_Double to_degrees_double() const;

    private:
        underlying_type m_value;
    };


    void test();
}

/*
template <typename T>
bit_radians::Underlying_Value<T>::Underlying_Value(underlying_type a_value)
    :
    m_value(a_value)
{}

template <typename T>
bit_radians::Underlying_Value<T>::~Underlying_Value() = default;

template <typename T>
bit_radians::Underlying_Value<T>::underlying_type bit_radians::Underlying_Value<T>::get_value() const
{
    return m_value;
}
*/

#endif // BIT_RADIANS_H