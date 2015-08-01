#include "object_manager.h"

#include <iostream>

object_manager::Object_Manager::Object_Manager() :
m_map{},
m_next_id_number{ 0 }
{}
object_manager::Object_Manager::~Object_Manager() = default;

object_manager::Object_Manager* object_manager::Object_Manager::getInstance()
{
    initialise();
    return m_instance.get();
}

object_manager::Object* object_manager::Object_Manager::getObject(id_number_type id) const
{
    if (id != 0)
    {
        auto foundIterator = m_map.find(id);
        if (foundIterator != m_map.end())
            return foundIterator->second.m_object.get();
    }
    return nullptr;
}

object_manager::ObjectID object_manager::Object_Manager::makeObject()
{
    id_number_type new_id_number = ++m_next_id_number;
    //m_map.emplace(new_id_number, );
    m_map[new_id_number];
    return ObjectID(new_id_number); // increments ref count on construction
}

void object_manager::Object_Manager::incrementRefCount(id_number_type id) // these have to be just the number, or a reference to an ObjectID...
{
    if (id != 0)
    {
        auto foundIterator = m_map.find(id);
        if (foundIterator != m_map.end())
        {
            foundIterator->second.m_ref_count += 1;
        }
    }
    //else the id is invalid...uh oh
}
void object_manager::Object_Manager::decrementRefCount(id_number_type id)
{
    if (id != 0)
    {
        auto foundIterator = m_map.find(id);
        if (foundIterator != m_map.end())
        {
            foundIterator->second.m_ref_count -= 1;
            if (foundIterator->second.m_ref_count == 0)
                m_map.erase(id);
        }
    }
}

void object_manager::Object_Manager::initialise()
{
    if (!m_instance)
        m_instance.reset(new Object_Manager);
}

std::unique_ptr<object_manager::Object_Manager> object_manager::Object_Manager::m_instance{ nullptr };


void object_manager::test()
{
    std::cout << "Object Manager" << std::endl << std::endl;

    ObjectID oid2 = ObjectID();
    Object* p = nullptr;
    {
        ObjectID oid1 = Object_Manager::getInstance()->makeObject();

        std::cout << oid1.get()->x << std::endl;
        std::cout << oid1.get()->y << std::endl;
        p = oid1.get();
        oid2 = oid1;
    }
    // this value is now nonsense as p is dangling
    std::cout << p->x << std::endl;
    std::cout << oid2.get()->x << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}
