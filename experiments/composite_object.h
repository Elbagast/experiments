#ifndef COMPOSITE_OBJECT_H
#define COMPOSITE_OBJECT_H

#include <string>

namespace composite_object
{
	// a class stores data.
	template <typename T>
	class Data
	{
	public:
		Data(T const& a_value) : m_value{ a_value } {}
		~Data() = default;
		
		void set(T const& a_value)	{ m_value = a_value; }
		T const& get() const		{ return m_value;  }

	private:
		T m_value;
	};
		
	// another class uses data.
	template <typename T>
	class Data_User
	{
	public:
		static std::string use_data(Data<T> const& a_data) { return std::to_string(a_data.get());  }
	};

	// we have a job we need done.
	class IData_Accessor
	{
	public:
		virtual ~IData_Accessor() = default;

		virtual std::string access_data() const = 0;
	};

	// The job is done by a concrete class that implements the link.
	template <typename T>
	class Data_Accessor : public IData_Accessor
	{
	public:
		Data_Accessor(Data<T> const& a_data, Data_User<T> const& a_user) : IData_Accessor(), m_data{ a_data }, m_user{ a_user } {}
		~Data_Accessor() override = default;

		std::string access_data() const override { return m_user.use_data(m_data); }

	private:
		Data<T> m_data;
		Data_User<T> m_user;
	};


	void test();
}

#endif COMPOSITE_OBJECT_H
