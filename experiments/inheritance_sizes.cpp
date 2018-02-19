#include "inheritance_sizes.hpp"

#include <iostream>
#include <chrono>
#include <memory>
#include <string>

// inheritance without virtual functions
class Base
{
public:
	Base() = default;
	~Base() = default;

	std::string func() { return m_data; }

	std::string m_data;
};

class Derived :
	private Base
{
public:
	Derived() : Base() {}
	~Derived() = default;

	using Base::func;
};


// chained inheritance without virtual functions
class Base1
{
public:
	std::string a() { return m_data; }
	std::string m_data;
};
class Base2 :
	protected Base1
{
public:
	using Base1::a;
	std::string b() { return m_data; }
};
class Base3 :
	protected Base2
{
public:
	using Base2::a;
	using Base2::b;
	std::string c() { return m_data; }
};
class Base4 :
	protected Base3
{
public:
	using Base3::a;
	using Base3::b;
	using Base3::c;
	std::string d() { return m_data; }
};




// template chained inheritance
template <typename...Args>
class TBase;

template <typename T>
class TBase<T>
{
public:
	TBase() = default;
	~TBase() = default;

	void func(T&) {}
};

template <typename T, typename R, typename...Args>
class TBase<T,R,Args...> :
	protected TBase<T>,
	protected TBase<R,Args...>
{
public:
	TBase() = default;
	~TBase() = default;

	using TBase<T>::func;
	using TBase<R, Args...>::func;
};

template <typename T,typename...Args>
class TDerived :
	protected TBase<T, Args...>
{
public:
	TDerived() = default;
	~TDerived() = default;

	using TBase<T, Args...>::func;
};



// inheritance with virtual functions
class VBase
{
public:
	VBase() = default;
	virtual ~VBase() = default;

	virtual std::string func() = 0;
};

class VDerived :
	public VBase
{
public:
	VDerived() : VBase() {}
	~VDerived() = default;

	std::string func() override { return m_data; }
private:
	std::string m_data;
};

class VDerived2 :
	public VDerived
{
public:
	VDerived2() : VDerived() {}
	~VDerived2() = default;

	std::string func() override { return m_data; }
private:
	std::string m_data;
};


// chained inheritance with virtual functions
class VBase1
{
public:
	virtual ~VBase1() = default;

	virtual std::string a() = 0;
};
class VBase2 :
	protected VBase1
{
public:
	~VBase2() override = default;

	virtual std::string b() = 0;
};
class VBase3 :
	protected VBase2
{
public:
	~VBase3() override = default;

	virtual std::string c() = 0;
};
class VBase4 :
	protected VBase3
{
public:
	~VBase4() override = default;

	virtual std::string d() = 0;
};
class VDerived4 :
	public VBase4
{
public:
	~VDerived4() override = default;

	std::string a() override { return m_data; }
	std::string b() override { return m_data; }
	std::string c() override { return m_data; }
	std::string d() override { return m_data; }

	std::string m_data;
};



// multiple inheritance
class MBase1
{
public:
	void a() {}
};
class MBase2
{
public:
	void b() {}
};
class MDerived  :
	public MBase1,
	public MBase2
{
public:
	using MBase1::a;
	using MBase2::b;
};


// multiple inheritance with virtual functions
class VMBase1
{
public:
	virtual ~VMBase1() = default;
	virtual std::string a() = 0;
};
class VMBase2
{
public:
	virtual ~VMBase2() = default;
	virtual std::string b() = 0;
};
class VMDerived :
	public VMBase1,
	public VMBase2
{
public:
	~VMDerived() override = default;

	std::string a() override { return m_data; }
	std::string b() override { return m_data; }
private:
	std::string m_data;
};


// multiple virtual inheritance
class MBaseV
{
public:
	std::string a() { return m_data; }
private:
	std::string m_data;
};
class MBaseV1 :
	public virtual MBaseV
{
public:
	std::string b() { return m_data; }
private:
	std::string m_data;
};
class MBaseV2 :
	public virtual MBaseV
{
public:
	std::string c() { return m_data; }
private:
	std::string m_data;
};
class MDerivedV :
	protected MBaseV1,
	protected MBaseV2
{
public:
	using MBaseV::a;
	using MBaseV1::b;
	using MBaseV2::c;
};


// multiple virtual inheritance with virtual functions
class VMBaseV
{
public:
	virtual ~VMBaseV() = default;
	virtual std::string a() = 0;
};
class VMBaseV1 :
	public virtual VMBaseV
{
public:
	~VMBaseV1() override = default;
	virtual std::string b() = 0;
};
class VMBaseV2 :
	public virtual VMBaseV
{
public:
	~VMBaseV2() override = default;
	virtual std::string c() = 0;
};
class VMDerivedV :
	public VMBaseV1,
	public VMBaseV2
{
public:
	~VMDerivedV() override = default;

	std::string a() override { return m_data; }
	std::string b() override { return m_data; }
	std::string c() override { return m_data; }
private:
	std::string m_data;
};

class VMBaseV3 :
	public virtual VMBaseV
{
public:
	~VMBaseV3() override = default;
	virtual std::string d() = 0;
};
class VMDerivedV2 :
	protected VMBaseV1,
	protected VMBaseV2,
	protected VMBaseV3
{
public:
	~VMDerivedV2() override = default;

	std::string a() override { return m_data; }
	std::string b() override { return m_data; }
	std::string c() override { return m_data; }
	std::string d() override { return m_data; }
private:
	std::string m_data;
};


class A {};
class B {};
class C {};
class D {};
class E {};

void inheritance_sizes::test()
{
	std::cout << "Inhertiance Sizes Test" << std::endl << std::endl;

	std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;
	std::cout << "sizeof(A) = " << sizeof(A) << std::endl;

	int count = 100000;

	std::cout << std::endl << "(private) inheritance" << std::endl;
	std::cout << "sizeof(Base) = " << sizeof(Base) << std::endl;
	std::cout << "sizeof(Derived) = " << sizeof(Derived) << std::endl;
	{
		auto l_d = std::make_unique<Derived>();

		Derived* l_ptr = l_d.get();
		std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i != count; ++i)
		{
			l_ptr->func();
		}
		std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
		auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

		std::cout << std::endl << "Time for " << count << " Base::func calls " << l_duration << "ms" << std::endl;
	}
	
	std::cout << std::endl << "chained inheritance" << std::endl;
	std::cout << "sizeof(Base1) = " << sizeof(Base1) << std::endl;
	std::cout << "sizeof(Base2) = " << sizeof(Base2) << std::endl;
	std::cout << "sizeof(Base3) = " << sizeof(Base3) << std::endl;
	std::cout << "sizeof(Base4) = " << sizeof(Base4) << std::endl;


	std::cout << std::endl << "template chained inheritance (with multiple inheritance)" << std::endl;
	std::cout << "sizeof(TBase<A>) = " << sizeof(TBase<A>) << std::endl;
	std::cout << "sizeof(TDerived<A>) = " << sizeof(TDerived<A>) << std::endl;

	std::cout << "sizeof(TBase<A,B>) = " << sizeof(TBase<A, B>) << std::endl;
	std::cout << "sizeof(TDerived<A,B>) = " << sizeof(TDerived<A, B>) << std::endl;

	std::cout << "sizeof(TBase<A,B,C>) = " << sizeof(TBase<A, B, C>) << std::endl;
	std::cout << "sizeof(TDerived<A,B,C>) = " << sizeof(TDerived<A, B, C>) << std::endl;

	std::cout << "sizeof(TBase<A,B,C,D>) = " << sizeof(TBase<A, B, C, D>) << std::endl;
	std::cout << "sizeof(TDerived<A,B,C,D>) = " << sizeof(TDerived<A, B, C, D>) << std::endl;


	std::cout << std::endl << "inheritance with virtual functions" << std::endl;
	std::cout << "sizeof(VBase) = " << sizeof(VBase) << std::endl;
	std::cout << "sizeof(VDerived) = " << sizeof(VDerived) << std::endl;
	{
		auto l_d = std::make_unique<VDerived>();
		{
			VBase* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->func();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << std::endl << "Time for " << count << " VBase::func calls " << l_duration << "ms" << std::endl;
		}
		{
			VDerived* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->func();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << std::endl << "Time for " << count << " VDerived::func calls " << l_duration << "ms" << std::endl;
		}
	}

	{
		auto l_d = std::make_unique<VDerived2>();
		{
			VBase* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->func();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << std::endl << "Time for " << count << " VBase::func virtual ccalls " << l_duration << "ms" << std::endl;
		}
		{
			VDerived* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->func();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << std::endl << "Time for " << count << " VDerived::func virtual ccalls " << l_duration << "ms" << std::endl;
		}
		{
			VDerived2* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->func();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << std::endl << "Time for " << count << " VDerived2::func virtual calls " << l_duration << "ms" << std::endl;
		}
		{
			VDerived2* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->VDerived2::func();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << std::endl << "Time for " << count << " VDerived2::func direct calls " << l_duration << "ms" << std::endl;
		}
	}

	std::cout << std::endl << "chained inheritance with virtual functions" << std::endl;
	std::cout << "sizeof(VBase1) = " << sizeof(VBase1) << std::endl;
	std::cout << "sizeof(VBase2) = " << sizeof(VBase2) << std::endl;
	std::cout << "sizeof(VBase3) = " << sizeof(VBase3) << std::endl;
	std::cout << "sizeof(VBase4) = " << sizeof(VBase4) << std::endl;
	std::cout << "sizeof(VDerived4) = " << sizeof(VDerived4) << std::endl;


	std::cout << std::endl << "multiple inheritance" << std::endl;
	std::cout << "sizeof(MBase1) = " << sizeof(MBase1) << std::endl;
	std::cout << "sizeof(MBase2) = " << sizeof(MBase2) << std::endl;
	std::cout << "sizeof(MDerived) = " << sizeof(MDerived) << std::endl;

	{
		auto l_d = std::make_unique<MDerived>();
		{
			MDerived* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->a();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " MDerived::a calls " << l_duration << "ms" << std::endl;
		}
		{
			MDerived* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->b();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " MDerived::b calls " << l_duration << "ms" << std::endl;
		}
	}
	

	std::cout << std::endl << "multiple inheritance with virtual functions" << std::endl;
	std::cout << "sizeof(VMBase1) = " << sizeof(VMBase1) << std::endl;
	std::cout << "sizeof(VMBase2) = " << sizeof(VMBase2) << std::endl;
	std::cout << "sizeof(VMDerived) = " << sizeof(VMDerived) << std::endl;
	// results in parallel vtables

	{
		auto l_d = std::make_unique<VMDerived>();
		{
			VMBase1* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->a();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMBase1::a calls " << l_duration << "ms" << std::endl;
		}
		{
			VMBase2* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->b();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMBase2::b calls " << l_duration << "ms" << std::endl;
		}
		{
			VMDerived* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->VMDerived::a();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMDerived::a calls " << l_duration << "ms" << std::endl;
		}
		{
			VMDerived* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->VMDerived::b();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMDerived::b calls " << l_duration << "ms" << std::endl;
		}
	}
	

	std::cout << std::endl << "multiple virtual inheritance" << std::endl;
	std::cout << "sizeof(MBaseV) = " << sizeof(MBaseV) << std::endl;
	std::cout << "sizeof(MBaseV1) = " << sizeof(MBaseV1) << std::endl;
	std::cout << "sizeof(MBaseV2) = " << sizeof(MBaseV2) << std::endl;
	std::cout << "sizeof(MDerivedV) = " << sizeof(MDerivedV) << std::endl;

	std::cout << std::endl << "multiple virtual inheritance with virtual functions" << std::endl;
	std::cout << "sizeof(VMBaseV) = " << sizeof(VMBaseV) << std::endl;
	std::cout << "sizeof(VMBaseV1) = " << sizeof(VMBaseV1) << std::endl;
	std::cout << "sizeof(VMBaseV2) = " << sizeof(VMBaseV2) << std::endl;
	std::cout << "sizeof(VMDerivedV) = " << sizeof(VMDerivedV) << std::endl;
	{
		auto l_d = std::make_unique<VMDerivedV>();
		{
			VMBaseV* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->a();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMBaseV::a virtual calls " << l_duration << "ms" << std::endl;
		}
		{
			VMBaseV1* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->b();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMBaseV1::b virtual calls " << l_duration << "ms" << std::endl;
		}
		{
			VMBaseV2* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->a();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMBaseV2::a virtual calls " << l_duration << "ms" << std::endl;
		}
		{
			VMDerivedV* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->VMDerivedV::a();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMDerivedV::a calls " << l_duration << "ms" << std::endl;
		}
		{
			VMDerivedV* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->VMDerivedV::b();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMDerivedV::b calls " << l_duration << "ms" << std::endl;
		}
		{
			VMDerivedV* l_ptr = l_d.get();
			std::chrono::high_resolution_clock::time_point l_dt1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i != count; ++i)
			{
				l_ptr->VMDerivedV::c();
			}
			std::chrono::high_resolution_clock::time_point l_dt2 = std::chrono::high_resolution_clock::now();
			auto l_duration = std::chrono::duration_cast<std::chrono::microseconds>(l_dt2 - l_dt1).count();

			std::cout << "Time for " << count << " VMDerivedV::c calls " << l_duration << "ms" << std::endl;
		}
	}
	std::cout << "with 3 base classes" << std::endl;
	std::cout << "sizeof(VMBaseV3) = " << sizeof(VMBaseV3) << std::endl;
	std::cout << "sizeof(VMDerivedV2) = " << sizeof(VMDerivedV2) << std::endl;

	std::cout << "----------------------------------------" << std::endl;
}
