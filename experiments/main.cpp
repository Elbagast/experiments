#include <iostream>
#include "enum_stuff.h"
#include "integer_id.h"
#include "enum_data_manager.h"
#include "datapoolvalue.h"

#include "grid.h"

template <char C>
struct Foo
{
    char m_char{ C };
};

class Bar
{
public:
    explicit Bar(int b) :
        a{ b }
    {}
private:
    int a;
};

int main(int argc, char* argv[])
{
    //DEBUG_TestID();

    Foo<'A'> a;
    Foo<'b'> b;
    std::cout << a.m_char << std::endl;
    std::cout << b.m_char << std::endl;
    
    DataType<DataEnum::Int> i{5};
    std::cout << i << std::endl;
    auto e(getEnum<decltype(i)>());
    std::cout << (e == DataEnum::Int ? "i is an int" : "is is not an int") << std::endl;

    MultiDataManager mdm{};
    mdm.setValue<DataEnum::Int>(1, 5);
    std::cout << mdm.getValue<DataEnum::Int>(1) << std::endl;
    std::cout << mdm.getValue<int>(1) << std::endl;

    mdm.setValue<bool>(2, false);
    std::cout << mdm.getValue<DataEnum::Bool>(2) << std::endl;
    std::cout << mdm.getValue<bool>(2) << std::endl;
    std::cout << std::endl;


    using DataPoolString = DataPoolValue < DataType<DataEnum::String> > ;

    DataPoolString dps1{"moooo"};
    std::cout << "DataPoolString dps1{ DataPoolString{\"moooo\"} };" << std::endl;
    std::cout << "dps1: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
    DataPoolString dps2{ std::string("baaa") };
    std::cout << "DataPoolString dps2{ \"baaa\" };" << std::endl;
    std::cout << "dps2: \"" << dps2.cget() << "\" RC: " << dps2.refCount() << std::endl;
    std::cout << "{" << std::endl;
    {
        DataPoolString dps3{ dps1 };
        std::cout << "DataPoolString dps3{ dps1 };" << std::endl;
        std::cout << "dps3: \"" << dps3.cget() << "\" RC: " << dps3.refCount() << std::endl;
        DataPoolString dps4{ dps3 };
        std::cout << "DataPoolString dps4{ dps3 };" << std::endl;
        std::cout << "dps4: \"" << dps4.cget() << "\" RC: " << dps4.refCount() << std::endl;
        dps4 = dps2;
        std::cout << "dps4 = dps2;" << std::endl;
        std::cout << "dps4: \"" << dps4.cget() << "\" RC: " << dps4.refCount() << std::endl;
        DataPoolString dps5{ DataPoolString{"moooo"} };
        std::cout << "DataPoolString dps5{ DataPoolString{\"moooo\"} };" << std::endl;
        std::cout << "dps5: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
        dps5.set("weeeee");
        std::cout << "dps5.setValue(\"weeeee\");" << std::endl;
        std::cout << "dps5: \"" << dps5.cget() << "\" RC: " << dps5.refCount() << std::endl;
        std::cout << "dps1: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
        DataPoolString dps6{ std::move(dps3) };
        std::cout << "DataPoolString dps6{ std::move(dps3) };" << std::endl;
        std::cout << "dps6: \"" << dps6.cget() << "\" RC: " << dps6.refCount() << std::endl;
        std::cout << "dps1: \"" << dps1 << "\" RC: " << dps1.refCount() << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "dps1: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
    std::cout << "dps2: \"" << dps2.cget() << "\" RC: " << dps2.refCount() << std::endl;

    std::string thing{ "moooo" };

    std::cout << (dps1 == dps2) << std::endl;

    std::cout << (dps1 == thing) << std::endl;

    thing = static_cast<std::string>(dps2);

    std::cout << (thing == dps2) << std::endl;
    std::cout << (dps1 == thing) << std::endl;

    Grid<int, 3, 3> g;
    g.at(1,1) = 5;
    std::cout << g.at(4) << std::endl;

    return 0;
}