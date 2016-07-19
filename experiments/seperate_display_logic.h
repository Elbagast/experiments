#ifndef SEPERATE_DISPLAY_LOGIC_H
#define SEPERATE_DISPLAY_LOGIC_H

#include <string>
#include <vector>

namespace seperate_display_logic
{
    /*
    Determine a programmatic way of displaying a c++ class members in the same
    format as it is written.

    e.g.

    class Foo
    {
    public:
        Foo();
        f();
        f2() const;
    private:
        int m_int;
        float m_float
    };
    
    class Bar
    {
    public:
        Bar();
        f();
        f2() const;
    private:
        bool m_bool;
        int m_int;
        Foo m_foo;
    };

    as

    Bar XXX
    {
        bool m_bool = "false";
        int m_int = "123";
        Foo m_foo
        {
            int m_int = "456";
            float m_float = "1.234";
        }
    }

    */
    class Object;

    class Ostream
    {
    public:
        void serialise(Object const& a_object);
    private:
        std::size_t m_indent;
    };

    class Object
    {
    public:
        std::string type() const;
    };


    class Displayer
    {
    public:
        std::string type() const;
        std::size_t child_count() const;
        Displayer const* child_at(std::size_t a_index) const;
        std::vector<Displayer const*> const& children() const;


    protected:
        void add_child(Displayer const* a_child);
    private:
        std::vector<Displayer const*> m_children;
    };

    void test();
} // namespace seperate_display_logic

#endif 