#include "reference_counting.h"

#include "integer_id.h"

#include <string>
#include <iostream>


namespace
{
    class Thing
    {
    public:
        explicit Thing(std::string const& value) : m_value( value ) {}
        std::string const& get_value() const        { return m_value; }
        void set_value(std::string const& value)    { m_value = value; }
        void do_stuff() const                       { std::cout << "Thing::do_stuff()" << std::endl; }
    private:
        std::string m_value;
    };

    

    using Counter = std::size_t;
    using ThingID = integer_id::Bound_Integer_ID < Thing >;
    using ThingID_Factory = integer_id::Bound_Integer_ID_Factory < Thing >;

    using Thing_Manager = reference_counting::Reference_Counting_Manager < Thing, ThingID, ThingID_Factory, Counter >;
    using Thing_Index = Thing_Manager::index_type;


    std::ostream& operator<<(std::ostream& os, Thing const& thing)
    {
        os << "Something{ value=\"" << thing.get_value() << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, ThingID const& id)
    {
        os << id.value();
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, Thing_Index const& index)
    {
        os  << "Index{ is_null=" << std::boolalpha << index.is_null() << std::noboolalpha 
            << " ID=" << index.id() 
            << " RC=" << index.reference_count()
            << " Data=" << (index.cdata() ? index.cdata()->get_value() : "") << "}";
        return os;
    }
}



void reference_counting::test()
{
    std::cout << "Reference Counting Test" << std::endl << std::endl;

    

    Thing_Manager manager{};

    Thing_Index index0{ manager.make_null_index() };

    Thing_Index index1{ manager.emplace_data(Thing("first")) };  // ID = 1
    Thing_Index index2{ manager.emplace_data(Thing("second")) }; // ID = 2
    Thing_Index index3{ index1 }; // ID = 1
    Thing_Index index4{ index1 }; // ID = 1

    std::cout << "index0: " << index0 << std::endl;
    std::cout << "index1: " << index1 << std::endl;
    std::cout << "index2: " << index2 << std::endl;
    std::cout << "index3: " << index3 << std::endl;
    std::cout << "index4: " << index4 << std::endl;
    std::cout << std::endl;
    {
        Thing_Index index5{ manager.emplace_data(Thing("third")) }; // ID = 3
        Thing_Index index6{ index1 }; // ID = 1
        Thing_Index index7{ index1 }; // ID = 1
        Thing_Index index8{ std::move(index2) }; // ID = 2

        std::cout << "index2: " << index2 << std::endl; // now ID = 0
        std::cout << "index5: " << index5 << std::endl;
        std::cout << "index6: " << index6 << std::endl;
        std::cout << "index7: " << index7 << std::endl;
        std::cout << "index8: " << index8 << std::endl;

        index4 = index5;
        std::cout << "index4: " << index4 << std::endl; // now ID = 3, rc = 2

        std::cout << std::endl;
    }
    std::cout << "index0: " << index0 << std::endl; // ID = 0
    std::cout << "index1: " << index1 << std::endl; // ID = 1
    std::cout << "index2: " << index2 << std::endl; // ID = 0
    std::cout << "index3: " << index3 << std::endl; // ID = 1
    std::cout << "index4: " << index4 << std::endl; // ID = 3, rc = 1

    Thing_Index index9{ manager.emplace_data(Thing("forth")) }; // this should get id = 2 when ids are tracked

    std::cout << "index9: " << index9 << std::endl; // ID = 2
    
    // Going to want a way of debugging the manager...

    std::cout << "----------------------------------------" << std::endl;
}