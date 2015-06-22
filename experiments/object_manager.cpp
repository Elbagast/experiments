#include "object_manager.h"


Object_Manager::Object_Manager() :
m_map{},
m_next_id_number{ 0 }
{}
Object_Manager::~Object_Manager() = default;

Object_Manager* Object_Manager::getInstance()
{
    initialise();
    return m_instance.get();
}

Object* Object_Manager::getObject(id_number_type id) const
{
    if (id != 0)
    {
        auto foundIterator = m_map.find(id);
        if (foundIterator != m_map.end())
            return foundIterator->second.m_object.get();
    }
    return nullptr;
}

ObjectID Object_Manager::makeObject()
{
    id_number_type new_id_number = ++m_next_id_number;
    //m_map.emplace(new_id_number, );
    m_map[new_id_number];
    return ObjectID(new_id_number); // increments ref count on construction
}

void Object_Manager::incrementRefCount(id_number_type id) // these have to be just the number, or a reference to an ObjectID...
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
void Object_Manager::decrementRefCount(id_number_type id)
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

void Object_Manager::initialise()
{
    if (!m_instance)
        m_instance.reset(new Object_Manager);
}

std::unique_ptr<Object_Manager> Object_Manager::m_instance{ nullptr };