#ifndef ID_AND_INDEX_TEST_H
#define ID_AND_INDEX_TEST_H

namespace id_and_index_test
{
    class Base_Class
    {
    public:
        Base_Class() = default;
        virtual ~Base_Class() = default;
    };

    class Derived_Class :
        public Base_Class
    {
    public:
        Derived_Class() = default;
        ~Derived_Class() override = default;
    };

    using id_number_type = unsigned int;

    template <typename T>
    class ID
    {
    public:
        using identified_type = T;

        ID(id_number_type id = 0) :
            m_id_number{ id }
        {}


        id_number_type id_number() const { return m_id_number; }
    private:
        id_number_type m_id_number;
    };

    template <typename T>
    class Manager;

    template <typename T>
    class Index
    {
    public:
        using identified_type = T;
        using id_type = ID < identified_type >;
        using manager_type = Manager < identified_type >;

    private:
        manager_type * mp_manager;
        id_type m_id;
    };

    template <typename T>
    class Manager
    {
    public:
        using managed_type = T;
        using id_type = ID < T > ;

    };

    

    using BaseID = ID < Base_Class > ;
    using DerivedID = ID < Derived_Class > ;

    void test();

} // abstract_interface_test


#endif // ID_AND_INDEX_TEST_H