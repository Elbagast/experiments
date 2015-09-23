#ifndef INTERFACE_INHERITANCE_H
#define INTERFACE_INHERITANCE_H
/*
This is a test of virtual inheritance to determine how to set up a class that has a 
large interface composed of sections that are independent of each other but are designed 
to be used together.
*/
#include <string>

namespace interface_inheritance
{
    namespace part1
    {
        /*
        Sectioned off interface classes

        */

        class IBase
        {
        public:
            virtual ~IBase() = default;

            virtual std::string base_func() const = 0;
        };

        class IPart1
        {
        public:
            virtual ~IPart1() = default;

            virtual std::string part1_func() const = 0;
        };

        class IPart2
        {
        public:
            virtual ~IPart2() = default;

            virtual std::string part2_func() const = 0;
        };


        /*
        The full interface

        */

        class IFinal :
            public virtual IBase,
            public virtual IPart1,
            public virtual IPart2
        {
        public:
            ~IFinal() override = default;
        };


        /*
        Sectioned off implementation classes

        */

        class Base :
            public virtual IBase
        {
        public:
            ~Base() override = default;

            std::string base_func() const override { return std::string("Base::base_func"); }
        };

        class Part1 :
            public virtual IPart1
        {
        public:
            ~Part1() override = default;

            std::string part1_func() const override { return std::string("Part1::part1_func"); }
        };

        class Part2 :
            public virtual IPart2
        {
        public:
            ~Part2() override = default;

            std::string part2_func() const override { return std::string("Part2::part2_func"); }
        };

        /*
        Everything together

        */

        class Final :
            public IFinal,
            public Base,
            public Part1,
            public Part2
        {
        public:
            ~Final() override = default;
        };

        void test();
    } // namespace part1








    namespace part2
    {
        /*
        This time with templates

        Sectioned off interface classes

        */

        class IBase
        {
        public:
            virtual ~IBase() = default;

            virtual std::string base_func() const = 0;
        };

        template <typename T>
        class IPart1
        {
        public:
            virtual ~IPart1() = default;

            virtual std::string part1_func() const = 0;
        };

        // Specialisation test
        template <>
        class IPart1 < int >
        {
        public:
            virtual ~IPart1() = default;

            virtual std::string part1_func() const = 0;
            virtual int part1_int_func() const = 0;
        };


        template <typename T>
        class IPart2
        {
        public:
            virtual ~IPart2() = default;

            virtual std::string part2_func() const = 0;
        };

        // Specialisation test
        template <>
        class IPart2 < int >
        {
        public:
            virtual ~IPart2() = default;

            virtual std::string part2_func() const = 0;
            virtual int part2_int_func() const = 0;
        };

        /*
        The full interface

        */
        template <typename T>
        class IFinal :
            public virtual IBase,
            public virtual IPart1<T>,
            public virtual IPart2<T>
        {
        public:
            ~IFinal() override = default;
        };


        /*
        Sectioned off implementation classes

        */
        template <typename T>
        class Base :
            public virtual IBase
        {
        public:
            ~Base() override = default;

            std::string base_func() const override { return std::string("Base<T>::base_func"); }
        };

        template <typename T>
        class Part1 :
            public virtual IPart1<T>
        {
        public:
            ~Part1() override = default;

            std::string part1_func() const override { return std::string("Part1<T>::part1_func"); }
        };

        // Specialisation test
        template <>
        class Part1 < int > :
            public virtual IPart1<int>
        {
        public:
            ~Part1() override = default;

            std::string part1_func() const override { return std::string("Part1<int>::part1_func"); }
            int part1_int_func() const override { return 5; }
        };

        template <typename T>
        class Part2 :
            public virtual IPart2<T>
        {
        public:
            ~Part2() override = default;

            std::string part2_func() const override { return std::string("Part2<T>::part2_func"); }
        };

        // Specialisation test
        template <>
        class Part2 < int > :
            public virtual IPart2<int>
        {
        public:
            ~Part2() override = default;

            std::string part2_func() const override { return std::string("Part2<int>::part2_func"); }
            int part2_int_func() const override { return 10; }
        };

        /*
        Everything together

        */
        template <typename T>
        class Final :
            public IFinal<T>,
            public Base<T>,
            public Part1<T>,
            public Part2<T>
        {
        public:
            ~Final() override = default;
        };

        void test();
    } // namespace part2
    
} // namespace interface_inheritance

#endif // INTERFACE_INHERITANCE_H