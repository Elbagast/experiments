#ifndef FAKE_VIRTUAL_FUNCTIONS_H
#define FAKE_VIRTUAL_FUNCTIONS_H

#include <string>
#include <cassert>

/*
Investigation into a different method of attaining the functionality of virtual functions by
storing function pointers in the base class.

Execution timing shows that while this method works, the duration is around 1.5x that of a 
plain virtual call.
*/

namespace fake_virtual_functions
{
    class Interface;

    class Interface
    {
    public:
        using function_type = std::string(void const*);
        //using function_type = std::string(*)(Interface const*);

        explicit Interface(function_type function) :
            mp_function(function)
        {}
        virtual ~Interface() = default;

        virtual std::string virtual_do_something() const = 0;

        std::string fake_virtual_do_something() const
        { 
            return (*mp_function)(this);
            //return (*mp_function)(static_cast<void const*>(this));
        }

    private:
        function_type* mp_function;
    };

    class Derived1 :
        public Interface
    {
    public:
        static std::string external_do_something(void const* object)
        //static std::string external_do_something(Interface const* object)
        {
            return static_cast<Derived1 const*>(object)->actual_do_something();
        }

        Derived1(std::string const& data) :
            Interface(external_do_something),
            m_data(data)
        {
        }

        ~Derived1() override = default;

        std::string virtual_do_something() const override
        { 
            return actual_do_something();
        }

        inline
        std::string actual_do_something() const
        {
            return m_data;
        }

    private:
        std::string m_data;
    };


    void test();

} // namespace fake_virtual_functions

#endif // FAKE_VIRTUAL_FUNCTIONS_H