#include "templated_observer.h"
#include <iostream>

templated_observer::External_Manager::External_Manager():
    m_manager(*this)
{
}

bool templated_observer::External_Manager::create_value(key_type const& a_key, value_type const& a_value)
{
    return m_manager.create_value(a_key, a_value);
}

bool templated_observer::External_Manager::has_value(key_type const& a_key) const
{
    return m_manager.has_value(a_key);
}

templated_observer::External_Manager::value_type const& templated_observer::External_Manager::get_value(key_type const& a_key) const
{
    return m_manager.get_value(a_key);
}

bool templated_observer::External_Manager::change_value(key_type const& a_key, value_type const& a_value)
{
    return m_manager.change_value(a_key, a_value);
}

bool templated_observer::External_Manager::destroy_value(key_type const& a_key)
{
    return m_manager.destroy_value(a_key);
}

std::vector<templated_observer::External_Manager::key_type> templated_observer::External_Manager::get_keys() const
{
    return m_manager.get_keys();
}

void templated_observer::External_Manager::slot_value_created(key_type const& a_key)
{
    std::cout << "External_Manager @ " << this << " value with key " << a_key << " created." << std::endl;
}

void templated_observer::External_Manager::slot_value_changed(key_type const& a_key)
{
    std::cout << "External_Manager @ " << this << " value with key " << a_key << " changed." << std::endl;
}

void templated_observer::External_Manager::slot_value_destroyed(key_type const& a_key)
{
    std::cout << "External_Manager @ " << this << " value with key " << a_key << " destroyed." << std::endl;
}


/*
templated_observer::Failure_Manager::Failure_Manager() :
    m_manager(*this)
{
}

bool templated_observer::Failure_Manager::create_value(key_type const& a_key, value_type const& a_value)
{
    return m_manager.create_value(a_key, a_value);
}

bool templated_observer::Failure_Manager::has_value(key_type const& a_key) const
{
    return m_manager.has_value(a_key);
}

templated_observer::Failure_Manager::value_type const& templated_observer::Failure_Manager::get_value(key_type const& a_key) const
{
    return m_manager.get_value(a_key);
}

bool templated_observer::Failure_Manager::change_value(key_type const& a_key, value_type const& a_value)
{
    return m_manager.change_value(a_key, a_value);
}

bool templated_observer::Failure_Manager::destroy_value(key_type const& a_key)
{
    return m_manager.destroy_value(a_key);
}

std::vector<templated_observer::Failure_Manager::key_type> templated_observer::Failure_Manager::get_keys() const
{
    return m_manager.get_keys();
}
*/




void templated_observer::test()
{
    std::cout << "Templated Observer Test" << std::endl << std::endl;

    //Failure_Manager l_im_failtest{}; // should fail to compile
    // which it does, but only on the first function not found

    External_Manager l_em{};

    l_em.create_value(0, "Blah blah blah");
    l_em.create_value(1, "mooooo");
    l_em.create_value(2, "bleeeeeeed");

    std::cout << std::endl;
    std::cout << "External_Manager l_em contents:" << std::endl;
    for (auto key : l_em.get_keys())
    {
        std::cout << key << " : " << l_em.get_value(key) << std::endl;
    }
    std::cout << std::endl;
 
    l_em.change_value(2, "poop");
    l_em.destroy_value(0);

    std::cout << std::endl;
    std::cout << "External_Manager l_em contents:" << std::endl;
    for (auto key : l_em.get_keys())
    {
        std::cout << key << " : " << l_em.get_value(key) << std::endl;
    }
    std::cout << std::endl;

    //Observed_Class<void, void> test_null{};

    std::cout << "----------------------------------------" << std::endl;
}