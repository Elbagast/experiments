#ifndef TEMPLATED_OBSERVER_H
#define TEMPLATED_OBSERVER_H

/*
Investigating compile-time linking of objects where one captures the signals of another
*/

#include <map>
#include <type_traits>
#include <functional>
#include <string>
#include <vector>

namespace templated_observer
{
    template 
        <
        typename Key, 
        typename Value, 
        class Observer,
        void(Observer::*T_slot_value_created)(Key const&),// = &Observer::slot_value_created, // compiler hates these default arguments...
        void(Observer::*T_slot_value_changed)(Key const&),// = &Observer::slot_value_changed,
        void(Observer::*T_slot_value_destroyed)(Key const&)// = &Observer::slot_value_destroyed
        >
    class Internal_Manager
    {
    public:
        using key_type = Key;
        using value_type = Value;
        using observer_type = Observer;

        explicit Internal_Manager(observer_type& ar_observer) :
            m_map(),
            mr_observer(ar_observer)
        {}

        bool create_value(key_type const& a_key, value_type const& a_value)
        {
            auto l_found = m_map.find(a_key);
            if (l_found == m_map.end())
            {
                m_map.emplace(a_key, a_value);
                signal_value_created(a_key);
                return true;
            }
            else
            {
                return false;
            }
        }

        bool has_value(key_type const& a_key) const
        {
            return m_map.find(a_key) != m_map.end();
        }
        
        value_type const& get_value(key_type const& a_key) const
        {
            auto l_found = m_map.find(a_key);
            if (l_found != m_map.end())
            {
                return l_found->second;
            }
            else
            {
                static value_type const fail_value{};
                return fail_value;
            }
        }

        bool change_value(key_type const& a_key, value_type const& a_value)
        {
            auto l_found = m_map.find(a_key);
            if (l_found != m_map.end() && l_found->second != a_value)
            {
                l_found->second = a_value;
                signal_value_changed(a_key);
                return true;
            }
            else
            {
                return false;
            }
        }

        bool destroy_value(key_type const& a_key)
        {
            auto l_found = m_map.find(a_key);
            if (l_found != m_map.end())
            {
                m_map.erase(l_found);
                signal_value_destroyed(a_key);
                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<key_type> get_keys() const
        {
            std::vector<key_type> l_result{};
            l_result.reserve(m_map.size());
            for (auto const& l_pair : m_map)
            {
                l_result.push_back(l_pair.first);
            }
            return l_result;
        }
   
    private:
        void signal_value_created(key_type const& a_key)
        {
            (mr_observer.*T_slot_value_created)(a_key);
        }
        void signal_value_changed(key_type const& a_key)
        {
            (mr_observer.*T_slot_value_changed)(a_key);
        }
        void signal_value_destroyed(key_type const& a_key)
        {
            (mr_observer.*T_slot_value_destroyed)(a_key);
        }

        
        using map_type = std::map < key_type, value_type >;
        map_type m_map;
        observer_type& mr_observer;
    };

    template <typename Key, typename Value, class Observer >
    using Default_Internal_Manager = Internal_Manager < Key, Value, Observer, &Observer::slot_value_created, &Observer::slot_value_changed, &Observer::slot_value_destroyed > ;

    class External_Manager
    {
    public:
        using key_type = int;
        using value_type = std::string;
        
        
        External_Manager();

        bool create_value(key_type const& a_key, value_type const& a_value);
        bool has_value(key_type const& a_key) const;
        value_type const& get_value(key_type const& a_key) const;
        bool change_value(key_type const& a_key, value_type const& a_value);
        bool destroy_value(key_type const& a_key);

        std::vector<key_type> get_keys() const;

    protected:
        void slot_value_created(key_type const& a_key);
        void slot_value_changed(key_type const& a_key);
        void slot_value_destroyed(key_type const& a_key);
        
    private:
        /*
        using internal_manager_type = Internal_Manager 
            < 
            key_type, 
            value_type, 
            External_Manager, 
            &External_Manager::slot_value_created,
            &External_Manager::slot_value_changed,
            &External_Manager::slot_value_destroyed
            >;
        */
        using internal_manager_type = Default_Internal_Manager < key_type, value_type, External_Manager >;

        // So that it can access the slots while they're hidden from everything else
        friend class internal_manager_type;

        internal_manager_type m_manager;
    };
    // This class cannot compile because the required member functions to not exist
    /*
    class Failure_Manager
    {
    public:
        using key_type = int;
        using value_type = std::string;
        using internal_manager_type = Default_Internal_Manager < key_type, value_type, Failure_Manager >; // now it hates this
        
        Failure_Manager();

        bool create_value(key_type const& a_key, value_type const& a_value);
        bool has_value(key_type const& a_key) const;
        value_type const& get_value(key_type const& a_key) const;
        bool change_value(key_type const& a_key, value_type const& a_value);
        bool destroy_value(key_type const& a_key);

        std::vector<key_type> get_keys() const;
        
    private:
        internal_manager_type m_manager;
    };
    */

    /*
    Want:
    - A class that references another and uses a supplied member function of it.
    - A class that has identical functionality but does not.
    - A template that is either(?) so that the implementation is shared and not duplicated.
    */

    class No_Signals
    {
    public:
        void f()
        {
            
        }
    };

    class A_Signals
    {
    public:
        void f()
        {
            //stuff happens...
        }
    };


    template <typename Signal_Box = No_Signals>
    class Signal_Origin
    {
    public:
        Signal_Origin(Signal_Box const& a_signal_box):
            m_signal_box(a_signal_box)
        {}

        void f()
        {
            m_signal_box.f();
        }

    private:
        Signal_Box m_signal_box;
    };


    void test();
} // namespace templated_observer

#endif TEMPLATED_OBSERVER_H