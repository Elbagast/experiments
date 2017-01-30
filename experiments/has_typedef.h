#ifndef HAS_TYPEDEF_H
#define HAS_TYPEDEF_H

#include <type_traits>

#include <string>

namespace has_typedef
{
	namespace sinfae
	{
		template <typename T>
		struct has_const_iterator
		{
		private:
			template <typename T1>
			static constexpr typename T1::const_iterator test(int) {};
			template <typename>
			static constexpr void test(...) {};
		public:
			static constexpr bool value{ !std::is_void<decltype(test<T>(0))>::value };
		};

		struct blah {};
		struct test1 {};
		struct test2 { using const_iterator = blah; };

		static_assert(!has_const_iterator<test1>::value, "metafunction has_const_iterator failed.");
		static_assert(has_const_iterator<test2>::value, "metafunction has_const_iterator failed.");
	}

	namespace sinfae2
	{
		namespace internal
		{
			template <typename T>
			struct has_const_iterator
			{
			private:
				template <typename T1>
				static constexpr typename T1::const_iterator test(int) {};
				template <typename>
				static constexpr void test(...) {};
			public:
				using type = typename std::conditional<!std::is_void<decltype(test<T>(0))>::value, std::true_type, std::false_type>::type;
			};

			template <typename T>
			using has_const_iterator_t = typename has_const_iterator<T>::type;
		}

		template <typename T>
		struct has_const_iterator : public internal::has_const_iterator_t<T> {};

		struct blah {};
		struct test1 {};
		struct test2 { using const_iterator = blah; };

		static_assert(!has_const_iterator<test1>::value, "metafunction has_const_iterator failed.");
		static_assert(has_const_iterator<test2>::value, "metafunction has_const_iterator failed.");
	}

	// Neither of these work because they involve a real call to a typedef that might not exist.
	/*
	namespace templated
	{
		namespace internal
		{
			template <typename T1>
			struct to_void { using type = void; };

			template <typename T1, typename = typename internal::to_void<typename T::const_iterator>::type>
			struct has_const_iterator_test;

			template <typename T1>
			struct has_const_iterator_test<T1,void> : public std::false_type {};

			template <typename T1>
			struct has_const_iterator_test < T1, typename to_void<typename T1::const_iterator>::type > : public std::true_type {};


		}
		template <typename T>
		struct has_const_iterator : public internal::has_const_iterator_test<T, typename internal::to_void<typename T::const_iterator>::type> {};

		struct blah {};
		struct test1 {};
		struct test2 { using const_iterator = blah; };

		static_assert(!has_const_iterator<test1>::value, "metafunction has_const_iterator failed.");
		static_assert(has_const_iterator<test2>::value, "metafunction has_const_iterator failed.");
	}

	namespace combo
	{
		template <typename T>
		struct typedef_fetch
		{
			using type = typename T::some_typedef;
		};


		template <typename T, typename TDF>
		struct has_typedef
		{
		private:
			template <typename T1>
			static constexpr typename TDF::type test(int) {};
			template <typename>
			static constexpr void test(...) {};
		public:
			static constexpr bool value{ !std::is_void<decltype(test<T>(0))>::value };
		};


		template <typename T>
		struct const_iterator_typedef_fetch
		{
			using type = typename T::const_iterator;
		};

		template <typename T>
		using has_const_iterator = has_typedef<T, const_iterator_typedef_fetch<T>>;

		struct blah {};
		struct test1 {};
		struct test2 { using const_iterator = blah; };

		static_assert(!has_const_iterator<test1>::value, "metafunction has_const_iterator failed.");
		static_assert(has_const_iterator<test2>::value, "metafunction has_const_iterator failed.");
	}

	*/
}

// requires <type_traits>
#define MACRO_GENERATE_HAS_TYPEDEF(_td)\
namespace internal \
{ \
	template <typename T> \
	struct has_typedef_##_td \
	{ \
	private: \
		template <typename T1> \
		static constexpr typename T1:: _td test(int) {}; \
		template <typename> \
		static constexpr void test(...) {}; \
	public: \
		using type = typename std::conditional<!std::is_void<decltype(test<T>(0))>::value, std::true_type, std::false_type>::type; \
	}; \
	template <typename T> using t_has_typedef##_td = typename has_typedef_##_td <T>::type; \
} \
template <typename T> struct has_typedef_##_td : public internal::t_has_typedef##_td<T> {};


namespace test_space
{
	MACRO_GENERATE_HAS_TYPEDEF(iterator)
	MACRO_GENERATE_HAS_TYPEDEF(value_type)
	MACRO_GENERATE_HAS_TYPEDEF(thing)

	static_assert(has_typedef_iterator<std::string>::value, "");
	static_assert(has_typedef_value_type<std::wstring>::value, "");
	static_assert(!has_typedef_thing<std::wstring>::value, "");
}

#endif // !HAS_TYPEDEF_H
