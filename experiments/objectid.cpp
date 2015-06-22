#include "objectid.h"
#include "object_manager.h"

ObjectID::ObjectID(id_number_type value) :
m_value{ value }
{
    Object_Manager::getInstance()->incrementRefCount(m_value);
}
ObjectID::~ObjectID()
{
    Object_Manager::getInstance()->decrementRefCount(m_value);
}

ObjectID::ObjectID(ObjectID const& other) :
m_value{ other.m_value }
{
    Object_Manager::getInstance()->incrementRefCount(m_value);
}
ObjectID& ObjectID::operator=(ObjectID const& other)
{
    // check for equivalence rather than self assignment
    if (m_value != other.m_value)
    {
        id_number_type old_value = m_value;
        m_value = other.m_value;
        Object_Manager::getInstance()->incrementRefCount(m_value); // this is a new holder of this value so increment
        Object_Manager::getInstance()->decrementRefCount(old_value); // decrement after as this may trigger destruction
    }
    return *this;
}
ObjectID::ObjectID(ObjectID && other) :
m_value{ std::move(other.m_value) }
{
    // no ref count change
}
ObjectID& ObjectID::operator=(ObjectID && other)
{
    id_number_type old_value = m_value;
    m_value = std::move(other.m_value);
    //Object_Manager::getInstance()->incrementRefCount(m_value); // the number of objects referencing this id has not change, no increment
    Object_Manager::getInstance()->decrementRefCount(old_value); // decrement after as this may trigger destruction
    return *this;
}

id_number_type ObjectID::value() const
{
    return m_value;
}
Object* ObjectID::get() const
{
    if (m_value != 0)
        return Object_Manager::getInstance()->getObject(m_value);
    else
        return nullptr;
}