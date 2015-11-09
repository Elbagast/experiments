#ifndef MACRO_CLASS_H
#define MACRO_CLASS_H

#include <string>

namespace macro_class
{
    template <typename T>
    struct Macro_Generated_Name
    {
        static bool const is_specialised{false};
        static char const* name() { return "T";  }
    };

#define MACRO_GENERATED_NAME(type) \
    template <> struct Macro_Generated_Name<type> \
    { \
        static bool const is_specialised{ true }; \
        static char const* name() { return #type; } \
    };

    MACRO_GENERATED_NAME(bool)
    MACRO_GENERATED_NAME(int)
    MACRO_GENERATED_NAME(float)
    MACRO_GENERATED_NAME(std::string)

    void test();
} // namespace macro_class

#endif // MACRO_CLASS_H