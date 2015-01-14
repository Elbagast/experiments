#ifndef INTEGER_ID_H
#define INTEGER_ID_H
/*
Integer_ID
============================================================
Let's say you have decided that there is some functionality you want to reuse and thus only code and maintain in one place,
but you have multiple uses for it, and you don't want those uses to overlap intentionally or accidentally. In this case,
deciding I want to access two different and unrelated classes via a system of ID numbers, but I don't want the IDs to be
type compatible. 

e.g.
class ElementID;
class AttributeID;
Where both are the same, but using them interchangabley would be madness.

This turned into an investigation into private inheritance.


The annoying part? I'm now pondering whether this is even necessary for what I want to do...
*/
#include <cassert>
#include <type_traits>

template <typename UInt>
class Integer_ID
{
protected:
    // Everything is protected so that only derived classes can use them. 
    // You must reveal what you need with using declarations
    using value_type = UInt;

    // Stop compiling if the value_type is not an unsigned integer
    static_assert((std::is_integral<value_type>::value && std::is_unsigned<value_type>::value), "Templated type must be an unsigned integral type");

    // Special 6
    //============================================================
    Integer_ID() :
        m_value(s_invalidValue)
    {}
    explicit Integer_ID(value_type value) :
        m_value(value)
    {}
    // Destructor is not virtual. Use private inheritance.
    ~Integer_ID() = default;

    Integer_ID(Integer_ID const& other) = default;
    Integer_ID& operator=(Integer_ID const& other) = default;

    // God. Dammit. Visual Studio.
    // These should work.
    //Integer_ID(Integer_ID&& other) = default;
    //Integer_ID& operator=(Integer_ID&& other) = default;

    // Interface
    //============================================================
    value_type getValue() const                     { return m_value;  }
    void setValue(value_type value)                 { m_value = value; }
    bool isValid() const                            { return m_value != s_invalidValue; }

    // provide < and == functionality without defining the member operators
    bool less(Integer_ID const& rhs) const          { return m_value < rhs.m_value; }
    bool equal(Integer_ID const& rhs) const         { return m_value == rhs.m_value; }
private:
    value_type m_value;

    static value_type const s_invalidValue{ 0 };
};

// I don't know why Visual Studio is complaining about this inheritence, it compiles and works as intended?
class TestID :
    private Integer_ID<unsigned long>
{
private:
    // So that we don't have to use this form in declarations
    using base_type = Integer_ID<unsigned long>;
public:
    // Reveal this typedef
    using base_type::value_type;

    // Special 6
    //============================================================
    TestID():
        base_type()
    {}
    explicit TestID(value_type value) :
        base_type(value)
    {}
    ~TestID() = default;

    TestID(TestID const& other) = default;
    TestID& operator=(TestID const& other) = default;

    //TestID(TestID&& other) = default;
    //TestID& operator=(TestID && other) = default;

    // Interface
    //============================================================
    // Make all of the existing interface public
    using base_type::getValue;
    using base_type::setValue;
    using base_type::isValid;

    bool less(TestID const& rhs) const        { return base_type::less(rhs); }
    bool equal(TestID const& rhs) const       { return base_type::equal(rhs); }
};

inline bool operator<(TestID const& lhs, TestID const& rhs)
{
    return lhs.less(rhs);
}
inline bool operator==(TestID const& lhs, TestID const& rhs)
{
    return lhs.equal(rhs);
}

// Test all of TestID in this function.
void DEBUG_TestID();


#endif // INTEGER_ID_H