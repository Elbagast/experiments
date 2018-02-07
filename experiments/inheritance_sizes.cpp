#include "inheritance_sizes.hpp"

#include <iostream>

// inheritance without virtual functions
class Base
{
public:
	Base() = default;
	~Base() = default;

	void func() {}
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
	void a() {}
};
class Base2 :
	protected Base1
{
public:
	using Base1::a;
	void b() {}
};
class Base3 :
	protected Base2
{
public:
	using Base2::a;
	using Base2::b;
	void c() {}
};
class Base4 :
	protected Base3
{
public:
	using Base3::a;
	using Base3::b;
	using Base3::c;
	void d() {}
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

	virtual void func() = 0;
};

class VDerived :
	public VBase
{
public:
	VDerived() : VBase() {}
	~VDerived() = default;

	void func() override {}
};



// chained inheritance with virtual functions
class VBase1
{
public:
	virtual ~VBase1() = default;

	virtual void a() = 0;
};
class VBase2 :
	protected VBase1
{
public:
	~VBase2() override = default;

	virtual void b() = 0;
};
class VBase3 :
	protected VBase2
{
public:
	~VBase3() override = default;

	virtual void c() = 0;
};
class VBase4 :
	protected VBase3
{
public:
	~VBase4() override = default;

	virtual void d() = 0;
};
class VDerived4 :
	public VBase4
{
public:
	~VDerived4() override = default;

	void a() override {}
	void b() override {}
	void c() override {}
	void d() override {}
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
	protected MBase1,
	protected MBase2
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
	virtual void a() = 0;
};
class VMBase2
{
public:
	virtual ~VMBase2() = default;
	virtual void b() = 0;
};
class VMDerived :
	protected VMBase1,
	protected VMBase2
{
public:
	~VMDerived() override = default;

	void a() override {}
	void b() override {}
};


// multiple virtual inheritance
class MBaseV
{
public:
	void a() {}
};
class MBaseV1 :
	public virtual MBaseV
{
public:
	void b() {}
};
class MBaseV2 :
	public virtual MBaseV
{
public:
	void c() {}
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
	virtual void a() = 0;
};
class VMBaseV1 :
	public virtual VMBaseV
{
public:
	~VMBaseV1() override = default;
	virtual void b() = 0;
};
class VMBaseV2 :
	public virtual VMBaseV
{
public:
	~VMBaseV2() override = default;
	virtual void c() = 0;
};
class VMDerivedV :
	protected VMBaseV1,
	protected VMBaseV2
{
public:
	~VMDerivedV() override = default;

	void a() override {}
	void b() override {}
	void c() override {}
};

class VMBaseV3 :
	public virtual VMBaseV
{
public:
	~VMBaseV3() override = default;
	virtual void d() = 0;
};
class VMDerivedV2 :
	protected VMBaseV1,
	protected VMBaseV2,
	protected VMBaseV3
{
public:
	~VMDerivedV2() override = default;

	void a() override {}
	void b() override {}
	void c() override {}
	void d() override {}
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


	std::cout << std::endl << "inheritance" << std::endl;
	std::cout << "sizeof(Base) = " << sizeof(Base) << std::endl;
	std::cout << "sizeof(Derived) = " << sizeof(Derived) << std::endl;


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

	std::cout << std::endl << "multiple inheritance with virtual functions" << std::endl;
	std::cout << "sizeof(VMBase1) = " << sizeof(VMBase1) << std::endl;
	std::cout << "sizeof(VMBase2) = " << sizeof(VMBase2) << std::endl;
	std::cout << "sizeof(VMDerived) = " << sizeof(VMDerived) << std::endl;
	// results in parallel vtables

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

	std::cout << "with 3 base classes" << std::endl;
	std::cout << "sizeof(VMBaseV3) = " << sizeof(VMBaseV3) << std::endl;
	std::cout << "sizeof(VMDerivedV2) = " << sizeof(VMDerivedV2) << std::endl;

	std::cout << "----------------------------------------" << std::endl;
}
