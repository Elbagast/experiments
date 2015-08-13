#include "indexable_tuple.h"

#include <string>
#include <iostream>

void indexable_tuple::test()
{
    std::cout << "Indexable Tuple Test" << std::endl << std::endl;

    std::cout << "Indexable_Tuple<bool, int, std::string>" << std::endl;

    Indexable_Tuple<bool, int, std::string> some_tuple{true, 153435, "moooo"};
    //Indexable_Tuple<bool, int, std::string> some_tuple{ };

    auto tpb0 = some_tuple.get_base_at(0);
    auto tpb1 = some_tuple.get_base_at<1>();
    auto tpb2 = some_tuple.get_base_at(2);

    auto tpt0 = dynamic_cast<indexable_tuple::Derived<bool>*>(tpb0);
    auto tpt1 = some_tuple.get_derived_at<1>();
    auto tpt2 = dynamic_cast<indexable_tuple::Derived<std::string>*>(tpb2);
    
    std::cout << "tpt0: ";
    if (tpt0 == nullptr)
        std::cout << "Bad type cast.";
    else
        std::cout << tpt0->m_held;
    std::cout << std::endl;

    std::cout << "tpt1: ";
    if (tpt1 == nullptr)
        std::cout << "Bad type cast.";
    else
        std::cout << tpt1->m_held;
    std::cout << std::endl;

    std::cout << "tpt2: ";
    if (tpt2 == nullptr)
        std::cout << "Bad type cast.";
    else
        std::cout << tpt2->m_held;
    std::cout << std::endl;

    std::cout << std::endl;

    tpt0->m_held = false;
    tpt1->m_held = 5;
    tpt2->m_held = "moo";



    std::cout << "tpt0: ";
    if (tpt0 == nullptr)
        std::cout << "Bad type cast.";
    else
        std::cout << tpt0->m_held;
    std::cout << std::endl;

    std::cout << "tpt1: ";
    if (tpt1 == nullptr)
        std::cout << "Bad type cast.";
    else
        std::cout << tpt1->m_held;
    std::cout << std::endl;

    std::cout << "tpt2: ";
    if (tpt2 == nullptr)
        std::cout << "Bad type cast.";
    else
        std::cout << tpt2->m_held;
    std::cout << std::endl;


    std::cout << "----------------------------------------" << std::endl;
}