#ifndef OBJECTID_H
#define OBJECTID_H

/*
The id class references an object using an id_number_type
*/

namespace object_manager
{
    class Object;

    using id_number_type = unsigned int;
    class ObjectID
    {
    public:
        explicit ObjectID(id_number_type value = 0);
        ~ObjectID();

        ObjectID(ObjectID const& other);
        ObjectID& operator=(ObjectID const& other);
        ObjectID(ObjectID && other);
        ObjectID& operator=(ObjectID && other);

        id_number_type value() const;
        Object* get() const;

    private:
        id_number_type m_value;
    };
} // object_manager

#endif // OBJECTID_H