#include "data_pool_value.h"

#include <string>
#include <iostream>


void data_pool_value::test()
{
    std::cout << "Data Pool Values" << std::endl << std::endl;

    using Data_Pool_String = Data_Pool_Value < std::string>;

    Data_Pool_String dps1{ "moooo" };
    std::cout << "Data_Pool_String dps1{ Data_Pool_String{\"moooo\"} };" << std::endl;
    std::cout << "dps1: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
    Data_Pool_String dps2{ std::string("baaa") };
    std::cout << "Data_Pool_String dps2{ \"baaa\" };" << std::endl;
    std::cout << "dps2: \"" << dps2.cget() << "\" RC: " << dps2.refCount() << std::endl;
    std::cout << "{" << std::endl;
    {
        Data_Pool_String dps3{ dps1 };
        std::cout << "Data_Pool_String dps3{ dps1 };" << std::endl;
        std::cout << "dps3: \"" << dps3.cget() << "\" RC: " << dps3.refCount() << std::endl;
        Data_Pool_String dps4{ dps3 };
        std::cout << "Data_Pool_String dps4{ dps3 };" << std::endl;
        std::cout << "dps4: \"" << dps4.cget() << "\" RC: " << dps4.refCount() << std::endl;
        dps4 = dps2;
        std::cout << "dps4 = dps2;" << std::endl;
        std::cout << "dps4: \"" << dps4.cget() << "\" RC: " << dps4.refCount() << std::endl;
        Data_Pool_String dps5{ Data_Pool_String{ "moooo" } };
        std::cout << "Data_Pool_String dps5{ Data_Pool_String{\"moooo\"} };" << std::endl;
        std::cout << "dps5: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
        dps5.set("weeeee");
        std::cout << "dps5.setValue(\"weeeee\");" << std::endl;
        std::cout << "dps5: \"" << dps5.cget() << "\" RC: " << dps5.refCount() << std::endl;
        std::cout << "dps1: \"" << dps1.cget() << "\" RC: " << dps1.refCount() << std::endl;
        Data_Pool_String dps6{ std::move(dps3) };
        std::cout << "Data_Pool_String dps6{ std::move(dps3) };" << std::endl;
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

    std::cout << "----------------------------------------" << std::endl;
}