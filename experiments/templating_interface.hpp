#ifndef TEMPLATING_INTERFACE_HPP
#define TEMPLATING_INTERFACE_HPP

#include <tuple>
#include <vector>

namespace templating_interface
{
	using Foo = std::tuple<bool, int, float>;
	using Bar = std::tuple<int, int, int, int>;

	namespace starting_with
	{		
		// a thing all sections need to use
		class Shared
		{
		private:
			int m_data;
		public:
			explicit Shared(int arg) : m_data{ arg } {}

			int shared() { return m_data; }
		};

		// A section looks like a more complicated version of this.
		template <typename T>
		class Section
		{
		private:
			Shared& m_shared;
			T m_data;
		public:
			Section(T const& a_data, Shared& a_shared) : 
				m_shared{ a_shared },
				m_data{ a_data }
			{}

			T make()			{ return a_data; }
			void use(T const&)	{ /*do a thing with T*/}
			template <std::size_t I>
			decltype(auto) use_index(T const& arg)
			{
				return std::get<I>(arg);
			}
		};
		
		// Uses a load of sections
		class Big_Thing
		{
		public:
			Big_Thing() :
				m_shared{5},
				m_section_foo{ Foo{true,5,.1}, m_shared },
				m_section_bar{ Bar{1,2,3,4},  m_shared }
			{}

			// interface not related to sections...
			int func() { return 5; }

			template <typename T>
			Section<T>& get_section();
			// only works with Foo and Bar

			Section<Foo>& get_section_foo() { return m_section_foo; }
			Section<Bar>& get_section_bar() { return m_section_bar; }

		private:
			Shared m_shared;
			Section<Foo> m_section_foo;
			Section<Bar> m_section_bar;
		};

	}

	namespace changed_to
	{
		template <typename T>
		class Section_Tag
		{
		};

		template <std::size_t I>
		class Index_Tag
		{
		};

		class Abstract_Shared
		{
		public:
			virtual ~Abstract_Shared() = default;
			virtual int shared() = 0;
		};



		// split up the indexing function
		template <typename T, std::size_t Index, std::size_t Last = std::tuple_size_v<T> - 1>
		class Abstract_Section_Indexing :
			public virtual Abstract_Section_Indexing<T,Index + 1, Last>
		{
			static_assert(std::tuple_size_v<T> != 0, "cannot use empty tuple");
			static_assert(Index < std::tuple_size_v<T>, "bad tuple index");
		public:
			~Abstract_Section_Indexing() override = default;
			virtual std::tuple_element_t<Index, T> const& use_index(Index_Tag<Index>&&, T const& arg) = 0;

			// reveal the next indexing function
			using Abstract_Section_Indexing<T, Index + 1, Last>::use_index;
		};
		
		template <typename T, std::size_t Last>
		class Abstract_Section_Indexing<T, Last, Last>
		{
			static_assert(std::tuple_size_v<T> != 0, "cannot use empty tuple");
			static_assert(Last +1 == std::tuple_size_v<T>, "bad tuple end");
		public:
			virtual ~Abstract_Section_Indexing() = default;

			virtual std::tuple_element_t<Last, T> const& use_index(Index_Tag<Last>&&, T const& arg) = 0;
		};

		template <typename...Args>
		class Abstract_Section;

		template <typename T, typename R, typename...Args>
		class Abstract_Section<T,R,Args...> :
			public virtual Abstract_Section<R,Args...>,
			public virtual Abstract_Section_Indexing<T, 0>
		{
		public:
			static_assert(std::tuple_size_v<T> != 0, "cannot use empty tuple");

			~Abstract_Section() override = default;

			virtual T make(Section_Tag<T>&&) = 0;
			virtual void use(T const&) = 0;
			// reveal the indexing functions
			using Abstract_Section_Indexing<T, 0>::use_index;

			// reveal the next section's functions
			using Abstract_Section<R, Args...>::make;
			using Abstract_Section<R, Args...>::use;
			using Abstract_Section<R, Args...>::use_index;
		};


		template <typename T>
		class Abstract_Section<T> :
			public virtual Abstract_Section_Indexing<T,0>
		{
		public:
			~Abstract_Section() override = default;

			virtual T make(Section_Tag<T>&&) = 0;
			virtual void use(T const&) = 0;
			// reveal the indexing functions
			using Abstract_Section_Indexing<T, 0>::use_index;

		};
		
		// Inherit the chain making the full interface
		template <>
		class Abstract_Section<>
		{
		public:
			virtual ~Abstract_Section() = default;
		};


		template <typename...Args>
		class Abstract_Big_Thing;

		// Must have at least one section
		template <typename T, typename...Args>
		class Abstract_Big_Thing<T,Args...> :
			public virtual Abstract_Shared,
			public virtual Abstract_Section<T,Args...>
		{
		public:
			~Abstract_Big_Thing() override = default;

			// interface not related to sections...
			virtual int func() = 0;

			using Abstract_Shared::shared;

			using Abstract_Section<T, Args...>::make;
			using Abstract_Section<T, Args...>::use;
			using Abstract_Section<T, Args...>::use_index;

			// now has disambiguous funtions of both sections.
		};
		

		// now try and build it...

		class Shared :
			public virtual Abstract_Shared
		{
		private:
			int m_data;
		public:
			explicit Shared(int arg) : 
				Abstract_Shared(),
				m_data{ arg } {}
			~Shared() override = default;

			int shared() override { return m_data; }
		protected:
			int shared_data() const { return m_data; }
		};



		// split up the indexing function
		template <typename T, std::size_t Index, std::size_t Last = std::tuple_size_v<T> - 1>
		class Section_Indexing :
			//public virtual Abstract_Section_Indexing<T, Index, End>, // the virtual func we need
			public Section_Indexing<T, Index+1, Last> // the rest of them
		{
		public:
			Section_Indexing() = default;
			~Section_Indexing() override = default;
			
			std::tuple_element_t<Index, T> const& use_index(Index_Tag<Index>&&, T const& arg) override final
			{
				return std::get<Index>(arg);
			}

			using Section_Indexing<T, Index + 1, Last>::use_index;
		protected:
			using Section_Indexing<T, Index + 1, Last>::section_data;
		};

		// section has to have a layer that holds the data at the bottom of the inheritance chain

		template <typename T, std::size_t Last>
		class Section_Indexing<T, Last, Last> :
			public virtual Abstract_Section_Indexing<T,0, Last>, // inherit all the interfaces here
			public virtual Abstract_Shared
		{
		private:
			T m_data;
		public:
			Section_Indexing() :
				m_data{}
			{}
			~Section_Indexing() override = default;

			std::tuple_element_t<Last, T> const& use_index(Index_Tag<Last>&&, T const& arg) override final
			{
				return std::get<Last>(arg);
			}
		protected:
			T const& section_data(Section_Tag<T>&&) const { return m_data; }
		};

		template <typename... Args>
		class Section;


		template <typename T, typename R, typename... Args>
		class Section<T,R,Args...> :
			public virtual Abstract_Section<T, R, Args...>,
			public Section_Indexing<T,0>,
			public Section<R,Args...>
		{
		public:
			~Section() override = default;

			T make(Section_Tag<T>&&) override final { return section_data(Section_Tag<T>()); }
			void use(T const&) override final { }
			using Section_Indexing<T, 0>::use_index;

			using Abstract_Section<R, Args...>::make;
			using Abstract_Section<R, Args...>::use;
			using Abstract_Section<R, Args...>::use_index;

		protected:
			using Section_Indexing<T,0>::section_data;
		};

		template <typename T>
		class Section<T> :
			public virtual Abstract_Section<T>,
			public Section_Indexing<T, 0>
		{
		public:
			Section() = default;
			~Section() override = default;

			T make(Section_Tag<T>&&) override final { return section_data(Section_Tag<T>()); }
			void use(T const&) override final { }
			using Section_Indexing<T, 0>::use_index;

		protected:
			using Section_Indexing<T, 0>::section_data;
		};
		

		template <typename...Args>
		class Big_Thing;

		// Must have at least one section
		template <typename T, typename...Args>
		class Big_Thing<T, Args...> :
			public Abstract_Big_Thing<T, Args...>,
			public Shared,
			public Section<T, Args...>
		{
		public:
			Big_Thing() :
				Abstract_Big_Thing<T,Args...>(),
				Shared(5),
				Section<T,Args...>()
			{}
			~Big_Thing() override = default;

			// interface not related to sections...
			int func() override { return 5; }

			// the shared part. Although it's not actually used here...
			using Shared::shared;

			using Section<T, Args...>::make;
			using Section<T, Args...>::use;
			using Section<T, Args...>::use_index;

			// now has disambiguous funtions of all sections.
		};

		// Now we don't even need the interface...




		class AThing
		{
		public:
			virtual ~AThing() = default;
			virtual void f() = 0;
		};
		class Thing :
			public virtual AThing
		{
		public:
			~Thing() override = default;
			void f() override {}
		};

		class Thing_User :
			public virtual AThing,
			public Thing
		{
		public:
			~Thing_User() override = default;
		};
	}

	namespace again
	{
		template <typename T>
		class Tag {};

		template <std::size_t I>
		class Index_Tag {};



		// start with stuff that doesn't need anything else
		class A_Base
		{
		public:
			virtual ~A_Base() = default;
			virtual void base_func() = 0;
		};

		template <typename T, typename...Args>
		class A_Shared_Thing;

		// Next is stuff that is shared but implementation of will be available to the rest
		template <typename T, typename...Args>
		class A_Shared
		{
		public:
			virtual ~A_Shared() = default;
			virtual void shared_func(A_Shared_Thing<T,Args...>*) = 0;
		};

		// Interface per member
		template <std::size_t I, typename T>
		class A_Member
		{
		public:
			virtual ~A_Member() = default;

			virtual void member_func(Index_Tag<I>&&, T const&) = 0;
		};

		// Member interface gathering
		template <std::size_t I, std::size_t Last, typename T>
		class A_All_Members :
			public A_All_Members<I+1,Last,T>,
			public virtual A_Member<I,T>
		{
		public:
			~A_All_Members() override = default;

			using A_All_Members<I + 1, Last, T>::member_func;
			using A_Member<I,T>::member_func;
		};

		// On the last one don't continue the chain
		template <std::size_t Last, typename T>
		class A_All_Members<Last,Last,T> :
			public virtual A_Member<Last, T>
		{
		public:
			~A_All_Members() override = default;

			using A_Member<Last, T>::member_func;
		};

		// Interface for a type
		template <typename T>
		class A_Data_Part
		{
		public:
			virtual ~A_Data_Part() = default;

			virtual void data_func(Tag<T>&&) = 0;
		};


		// Interface for a type
		template <typename T>
		class A_Data :
			public virtual A_Data_Part<T>,
			public A_All_Members<0, (std::tuple_size_v<T> - 1), T>
		{
			using Inherited_Type = A_All_Members<0, (std::tuple_size_v<T> - 1), T>;
		public:
			~A_Data() override = default;

			using A_Data_Part<T>::data_func;
			using Inherited_Type::member_func; // now has all the overloads.
		};

		// Gathering all the sections
		template <typename...Args>
		class A_All_Data;

		// For one use the data
		template <typename T>
		class A_All_Data<T> :
			public virtual A_Data<T>
		{
			using Inh1 = A_Data<T>;
		public:
			~A_All_Data() override = default;

			using Inh1::data_func;
			using Inh1::member_func;
		};

		// For more than one stitch together
		template <typename T, typename R, typename...Args>
		class A_All_Data<T, R, Args...> :
			public virtual A_Data<T>,
			public A_All_Data<R,Args...>
		{
			using Inh1 = A_Data<T>;
			using Inh2 = A_All_Data<R, Args...>;
		public:
			~A_All_Data() override = default;

			using Inh1::data_func;
			using Inh1::member_func;

			using Inh2::data_func;
			using Inh2::member_func;
		};

		// the final uses all
		template <typename T, typename...Args>
		class A_Final :
			public virtual A_Base,
			public virtual A_Shared<T,Args...>,
			public A_All_Data<T,Args...>
		{
			using Inh1 = A_Base;
			using Inh2 = A_Shared<T, Args...>;
			using Inh3 = A_All_Data<T, Args...>;
		public:
			~A_Final() override = default;


			using Inh1::base_func;

			using Inh2::shared_func;

			using Inh3::data_func;
			using Inh3::member_func;
		};

		// Implementing this part is easy.
		class Base :
			public virtual A_Base
		{
		public:
			~Base() override = default;

			void base_func() override {}
		};

		// As is this, but figuring out how to get to it isn't.
		template <typename T, typename...Args>
		class Shared :
			public virtual A_Shared<T, Args...>
		{
		public:
			Shared() = default;
			~Shared() override = default;

			// final public part
			void shared_func(A_Shared_Thing<T, Args...>* a_ptr) override { m_data.push_back(a_ptr); }

			// final private / hidden part
			std::vector<A_Shared_Thing<T, Args...>*>& use_shared() { return m_data; } // Things will need this...
		private:
			std::vector<A_Shared_Thing<T, Args...>*> m_data;
		};

		// Chaining data together
		/*
		template <typename T_Shared, typename...Args>
		class Data;


		template <typename T_Shared, typename...Args>
		class Data;





		// The top class of data chains members together
		template <typename T_Shared, typename T>
		class Data<T_Shared,T> :
			private Member<0, std::tuple_size_v<T>-1, T> 
		{
			using Inh = Member<0, std::tuple_size_v<T>-1, T>;
		public:
			~Data() override = default;

			using Inh::member_func;
			using Inh::data_func;
			using Inh::data_func;
			using Inh::shared_func;
		};


		template <std::size_t I, std::size_t Last, typename T_Shared, typename...Args>
		class Member;
		
		template <std::size_t I, std::size_t Last, typename T_Shared, typename T, typename...Args>
		class Member :
			public virtual A_Member<I,T>,
			public Member<I+1,Last, T_Shared,T,Args...>
		{
			using Inh = Member<I + 1, Last, T_Shared, T, Args...>;
		public:
			~Member() override = default;

			void member_func(Index_Tag<I>&&, T const& arg) override { this->use_member<I>(arg); }

			using Inh::member_func;
			using Inh::data_func;
			using Inh::shared_func;
		};

		template <std::size_t Last, typename T_Shared, typename T, typename R, typename...Args>
		class Member<Last, Last, T_Shared, T> :
			public virtual A_Member<Last, T>,
			public Data_Bottom<T_Shared, T>
		{
			using Inh = Data_Imp<T>;
		public:
			~Member() override = default;

			void member_func(Index_Tag<I>&&, T const&) override { this->use_member<I>(arg); }

			using Inh::data_func;
			using Inh::shared_func;
		};

		template <std::size_t Last, typename T_Shared, typename T>
		class Member<Last,Last, T_Shared,T> :
			public virtual A_Member<Last, T>,
			public Data_Bottom<T_Shared,T>
		{
			using Inh = Data_Imp<T>;
		public:
			~Member() override = default;

			void member_func(Index_Tag<I>&&, T const&) override { this->use_member<I>(arg); }

			using Inh::data_func;
			using Inh::shared_func;
		};


		template <typename T_Shared, typename...Args>
		class Data_Bottom;


		template <typename T_Shared, typename T, typename R, typename...Args>
		class Data_Bottom<T_Shared, T, R, Args...> :
			public virtual A_Data<T>,
			public Data<T_Shared,R,Args...>
		{
		public:
			Data_Bottom() = default;
			~Data_Bottom() override = default;
			
			// final public part
			using Data<T_Shared, R, Args...>::shared_func;
			using Data<T_Shared, R, Args...>::data_func;
			using Data<T_Shared, R, Args...>::member_func;

			void data_func(Tag<T>&&) override { m_data.imp_data_func(this); }

			// Forwarding layer for members
		protected:
			template <std::size_t I>
			void use_member_func(T const& arg) { m_data.imp_member_func(this, arg); }
		private:
			Data_Imp<T_Shared, T> m_data;
		};
		
		template <typename T_Shared, typename T>
		class Data_Bottom :
			public virtual A_Data<T>,
			public T_Shared
		{
		public:
			Data_Bottom() = default;
			~Data_Bottom() override = default;

			// final public part
			using T_Shared::shared_func;

			void data_func(Tag<T>&&) override { m_data.imp_data_func(this); }

			// Forwarding layer for members
		protected:
			template <std::size_t I>
			void use_member_func(T const& arg) { m_data.imp_member_func(this, arg); }
		private:
			Data_Imp<T_Shared, T> m_data;
		};
		*/

		// This implements the data and access to it in terms of supplied objects
		template <typename T_Shared, typename T>
		class Data_Imp
		{
			static_assert(std::tuple_size_v<T> != 0, "bad tuple");
		public:
			Data_Imp() = default;
			
			void imp_data_func(T_Shared* a_shared) { a_shared->use_shared(); }

			template <std::size_t I>
			void imp_member_func(T_Shared* a_shared, T const&) { a_shared->use_shared(); auto& a = m_data; }
		private:
			std::vector<T> m_data;
		};

		// Chain together data that ends in inheriting T_Shared
		template <typename T_Shared, std::size_t I, std::size_t L, typename...Args>
		class Data;

		// The end is the last data section and inherits shared
		template <typename T_Shared, std::size_t L, typename T>
		class Data<T_Shared, L, L, T> :
			public virtual A_Member<L,T>,
			public virtual A_Data_Part<T>, // interface for this section
			public virtual T_Shared
		{
		public:
			~Data() override = default;

			using T_Shared::shared_func;

			void member_func(Index_Tag<L>&&, T const& arg) override { use_member_func<L>(arg);  } // the last member function
			void data_func(Tag<T>&&) override { m_data.imp_data_func(this); }

			// Access for member implementers
		protected:
			template <std::size_t I>
			void use_member_func(T const& arg) { m_data.imp_member_func<I>(this, arg); }

		private:
			Data_Imp<T_Shared, T> m_data;
		};

		// the end of a mid-chain data section
		template <typename T_Shared, std::size_t L, typename T, typename R, typename...Args>
		class Data<T_Shared, L, L, T,R,Args...> :
			public Data<T_Shared,L,L,T>, // inherit the end stuff here. virtual inheritance means there should only be one T_Shared...
			public Data<T_Shared, 0, std::tuple_size_v<R> - 1 , R,Args...>
		{
		public:
			~Data() override = default;

			using T_Shared::shared_func;

			using Data<T_Shared, L, L, T>::member_func;
			using Data<T_Shared, L, L, T>::data_func;
			
			using Data<T_Shared, 0, std::tuple_size_v<R> -1, R, Args...>::member_func;
			using Data<T_Shared, 0, std::tuple_size_v<R> -1, R, Args...>::data_func;

		protected:
			using Data<T_Shared, L, L, T>::use_member_func;
		};


		// when inside any data
		template <typename T_Shared, std::size_t I, std::size_t L, typename T, typename...Args>
		class Data<T_Shared, I, L, T, Args...> :
			public virtual A_Member<I, T>,
			public Data<T_Shared, I+1, L, T, Args...>
		{
		public:
			~Data() override = default;

			using T_Shared::shared_func;

			using Data<T_Shared, I + 1, L, T, Args...>::member_func;
			using Data<T_Shared, I + 1, L, T, Args...>::data_func;
			
			void member_func(Index_Tag<I>&&, T const& arg) override { use_member_func<I>(arg); } // the last member function

		protected:
			using Data<T_Shared, I + 1, L, T, Args...>::use_member_func;
		};



		template <typename T, typename...Args>
		class Final :
			public A_Final<T, Args...>,
			private Data<Shared<T, Args...>, 0, std::tuple_size_v<T>-1, T, Args...>,
			private Base
		{
			using Inh = Data<Shared<T, Args...>, 0, std::tuple_size_v<T>-1, T, Args...>;
		public:
			~Final() override = default;

			using Base::base_func;

			using Inh::shared_func;
			using Inh::data_func;
			using Inh::member_func;
		};

	}

	void test();
}


#endif // TEMPLATING_INTERFACE_HPP
