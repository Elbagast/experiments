#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
/*
Test of a flat object manager structure and using ids to access objects
*/
#include <map>
#include <memory>
#include <algorithm>

#include "objectid.h"

// forward declarations
class Object
{
public:
    int x{1};
    int y{2};
};
class ObjectID;
class Object_Manager;

/*
Singleton class that owns all the Objects
*/
class Object_Manager
{
private:
    Object_Manager();
public:
    ~Object_Manager();
    Object_Manager(Object_Manager const& other) = delete;
    Object_Manager& operator=(Object_Manager const& other) = delete;
    Object_Manager(Object_Manager && other) = delete;
    Object_Manager& operator=(Object_Manager && other) = delete;

    static Object_Manager* getInstance();

    Object* getObject(id_number_type id) const;

    ObjectID makeObject();

    void incrementRefCount(id_number_type id);
    void decrementRefCount(id_number_type id);

private:
    static void initialise();

    struct Object_Listing
    {
        Object_Listing() :
            m_object{ new Object },
            m_ref_count{ 0 }
        {}
        Object_Listing(Object_Listing const& other) = delete;
        Object_Listing& operator=(Object_Listing const& other) = delete;

        std::unique_ptr<Object> m_object;
        id_number_type m_ref_count;
    };
    std::map<id_number_type, Object_Listing> m_map;
    mutable id_number_type m_next_id_number;

    static std::unique_ptr<Object_Manager> m_instance;
};


#endif // OBJECT_MANAGER_H