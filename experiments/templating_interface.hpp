#ifndef TEMPLATING_INTERFACE_HPP
#define TEMPLATING_INTERFACE_HPP

#include <tuple>

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


	void test();
}


#endif // TEMPLATING_INTERFACE_HPP
