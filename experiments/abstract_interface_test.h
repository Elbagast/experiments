#ifndef ABSTRACT_INTERFACE_TEST_H
#define ABSTRACT_INTERFACE_TEST_H

namespace abstract_interface_test
{
	class Base_Class
	{
	public:
		Base_Class() = default;
		virtual ~Base_Class() = 0;
	};

	class Interface_Class :
		public Base_Class
	{
	public:
		Interface_Class() = default;
		~Interface_Class() override = 0;

		virtual bool func() = 0;
	};

	class Derived_Class :
		public Interface_Class
	{
	public:
		Derived_Class() = default;
		~Derived_Class() override = default;

		bool func() override;
	};

	void test();

} // abstract_interface_test


#endif // ABSTRACT_INTERFACE_TEST_H