#include "integer_id.h"

#include <iostream>

// Test all of TestID in this function.
void integer_id::test()
{
    std::cout << "Integer ID test" << std::endl << std::endl;
    

    std::cout << "Older stuff:" << std::endl;
    {
        using old::TestID;

        std::cout << "TestID a{5}" << std::endl;
        TestID a{ 5 };

        // Can access the function that was defined as private because it has been made public
        std::cout << "a.getValue(): " << a.getValue() << std::endl;
        std::cout << "a.isValid(): " << a.isValid() << std::endl;

        // Can't do this as inheritence is private (want this)
        //Integer_ID<unsigned long>* b = &a;  

        std::cout << "TestID b{7}" << std::endl;
        TestID b{ 7 };
        std::cout << "TestID b.getValue(): " << b.getValue() << std::endl;
        std::cout << "b.isValid(): " << b.isValid() << std::endl;

        std::cout << "a < b: " << (a < b) << std::endl;
        std::cout << "a == b: " << (a == b) << std::endl;
        std::cout << "a.setValue(9)" << std::endl;
        a.setValue(9);
        std::cout << "a < b: " << (a < b) << std::endl;

        std::cout << "TestID c{ a }" << std::endl;
        TestID c{ a };
        std::cout << "c.getValue(): " << c.getValue() << std::endl;
        std::cout << "c.isValid(): " << c.isValid() << std::endl;
        std::cout << "a < c: " << (a < c) << std::endl;
        std::cout << "a == c: " << (a == c) << std::endl;

        std::cout << "TestID d{}" << std::endl;
        TestID d{};
        std::cout << "d.getValue(): " << d.getValue() << std::endl;
        std::cout << "d.isValid(): " << d.isValid() << std::endl;

        // This isn't meaningful...
        // If a value of 0 is considered invalid
        std::cout << "a < d: " << (a < d) << std::endl;
        std::cout << "a == d: " << (a == d) << std::endl;
    }

    std::cout << "Newer stuff:" << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}