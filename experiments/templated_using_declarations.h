#ifndef TEMPLATED_USING_DECLARATIONS_H
#define TEMPLATED_USING_DECLARATIONS_H

// Starting with an abstract base class:

class SomeBase
{
public:
    virtual ~SomeBase() = default;

    virtual int some_shared_function() const = 0;
};

// We have a templated derived class:

template <typename T>
class SomeDerived:
    public SomeBase
{
public:
    SomeDerived() = default;
    ~SomeDerived() override = default;

    int some_shared_function() const override { return sizeof(T); }

    void set(T const& value) { m_value = value; }
    T get() const { return T(); }

private:
    T m_value;
};

// But we want to experiment with added functionality:
template <typename T>
class SomeOtherDerived :
    public SomeBase
{
public:
    SomeOtherDerived() = default;
    ~SomeOtherDerived() override = default;

    int some_shared_function() const override { return sizeof(T); }

    bool can_set_to(T const& value) const
    { 
        return value < m_constraint; 
    }

    bool try_set(T const& value) 
    { 
        if (can_set_to(value))
        {
            m_value = value;
            return true;
        }
        else
            return false;
    }
    T get() const { return T(); }

private:
    T m_constraint;
    T m_value;
};

#endif // TEMPLATED_USING_DECLARATIONS_H 