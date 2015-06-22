#ifndef INTERFACE_OPERATORS_H
#define INTERFACE_OPERATORS_H

/*
Ok this is dumb :\
*/

namespace interface_operators
{
	class Interface
	{
	protected:
		virtual ~Interface() = default;

	public:
		virtual int get_value() const = 0;
		virtual void set_value(int value) = 0;
	};

	class Derived :
		protected Interface
	{
	public:
		explicit Derived(int value):
			m_value{ value }
		{}
		~Derived() override = default;

		int get_value() const override		{ return m_value; }
		void set_value(int value) override	{ m_value = value;  }

		operator Interface&()				{ return *this; }
		operator Interface const&()			{ return *this; }
	private:
		int m_value;
	};

	int external_get_something(Interface const& object);
	void external_set_something(Interface& object, int value);

	void test();

} // namespace interface_operators

#endif // INTERFACE_OPERATORS_H