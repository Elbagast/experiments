#include "fake_virtual_functions.h"
#include <iostream>
#include <memory>
#include <chrono>


void fake_virtual_functions::test()
{
    std::unique_ptr<Interface> ptr{ new Derived1("blah blah blah Mr Freeman") };

    std::cout << std::endl;
    std::cout << "Fake Virtual Functions" << std::endl;
    std::cout << "sizeof(Interface) = " << sizeof(Interface) << std::endl;
    std::cout << "sizeof(Derived1) = " << sizeof(Derived1) << std::endl;
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << std::endl;
    std::cout << ptr->fake_virtual_do_something() << std::endl;

    int count = 100000;


    Derived1* true_ptr = static_cast<Derived1*>(ptr.get());
    std::chrono::high_resolution_clock::time_point dt1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i != count; ++i)
    {
        //true_ptr->Derived1::v_do_something();
        true_ptr->virtual_do_something();
    }
    std::chrono::high_resolution_clock::time_point dt2 = std::chrono::high_resolution_clock::now();
    auto d_duration = std::chrono::duration_cast<std::chrono::microseconds>(dt2 - dt1).count();

    std::cout << std::endl << "Time for " << count << " direct calls: " << d_duration << "ms" << std::endl;

    std::chrono::high_resolution_clock::time_point vt1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i != count; ++i)
    {
        ptr->virtual_do_something();
    }
    std::chrono::high_resolution_clock::time_point vt2 = std::chrono::high_resolution_clock::now();
    auto v_duration = std::chrono::duration_cast<std::chrono::microseconds>(vt2 - vt1).count();

    std::cout << std::endl << "Time for " << count << " virtual calls: " << v_duration << "ms" << std::endl;

    std::chrono::high_resolution_clock::time_point fvt1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i != count; ++i)
    {
        ptr->fake_virtual_do_something();
    }
    std::chrono::high_resolution_clock::time_point fvt2 = std::chrono::high_resolution_clock::now();
    auto fv_duration = std::chrono::duration_cast<std::chrono::microseconds>(fvt2 - fvt1).count();

    std::cout << std::endl << "Time for " << count << " fake virtual calls: " << fv_duration << "ms" << std::endl;


}