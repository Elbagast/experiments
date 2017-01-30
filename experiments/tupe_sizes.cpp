#include "tuple_sizes.h"
#include <iostream>
#include <tuple>
#include <array>

namespace internal
{
	template <typename... Args>
	struct typelist {};

	namespace v1
	{
		// structure of a very simple tuple.
		template <typename... Args>
		class tuple;

		template <typename T, typename... Args>
		class tuple<T, Args...>
		{
		private:
			T m_data;
			tuple<Args...> m_rest;
		};

		template <>
		class tuple<>
		{
		};
	}

	namespace v2
	{
		// structure of a very simple tuple.
		template <typename... Args>
		class tuple;

		template <typename T, typename... Args>
		class tuple<T, Args...>
		{
		private:
			T m_data;
			tuple<Args...> m_rest;
		};

		// Needed so we don't have an empty tuple at the end tkaing up space
		template <typename T>
		class tuple<T>
		{
		private:
			T m_data;
		};

		template <>
		class tuple<>
		{
		};
	}

	namespace v3
	{
		template <typename T>
		struct index_of_second_type;
		
		template <typename T, typename... Args>
		struct index_of_second_type<typelist<T,T,Args...>> : public std::integral_constant<std::size_t, 1 + index_of_second_type<typelist<T,Args...>>::value> {};
		
		template <typename T, typename R, typename... Args>
		struct index_of_second_type<typelist<T,R,Args...>> : public std::integral_constant<std::size_t, 1> {};

		template <typename T>
		struct index_of_second_type<typelist<T>> : public std::integral_constant<std::size_t, 1> {};

		template <>
		struct index_of_second_type<typelist<>> : public std::integral_constant<std::size_t, 0> {};


		template <typename T>
		struct pop_front;

		template <typename T, typename... Args>
		struct pop_front<typelist<T, Args...>>
		{
			using type = typelist<Args...>;
		};

		template <>
		struct pop_front<typelist<>>
		{
			using type = typelist<>;
		};


		template <std::size_t N, typename T>
		struct pop_front_n;

		template <std::size_t N, typename T, typename...Args>
		struct pop_front_n < N, typelist<T, Args...> >
		{
			using type =
				typename pop_front_n
				<
				N - 1,
				typelist<Args...>
				>::type;
		};

		// If the typelist has at least 1 element and we only remove one, remove the front.
		template < typename T, typename...Args>
		struct pop_front_n<1, typelist<T, Args...>>
		{
			using type = typelist<Args...>;
		};

		// If the typelist has at least 1 element and we only remove none, type is the same as input.
		template < typename T, typename...Args>
		struct pop_front_n<0, typelist<T, Args...>>
		{
			using type = typelist<T, Args...>;
		};

		// If the typelist has no elements we don't care how many will be removed, as nothing happens
		template <std::size_t N>
		struct pop_front_n<N, typelist<>>
		{
			using type = typelist<>;
		};


		

		template <typename... Args>
		class tuple;


		template <typename T>
		struct to_tuple;

		template <typename...Args>
		struct to_tuple<typelist<Args...>>
		{
			using type = tuple<Args...>;
		};



		template <typename T, typename... Args>
		class tuple<T, Args...>
		{
		public:
			static constexpr std::size_t front_end{ index_of_second_type<typelist<T, Args...>>::value };
			using front_type = std::array<T, front_end>;
			using back_type = typename to_tuple<typename pop_front_n<front_end,typelist<T, Args...>>::type>::type;

			front_type m_front;
			back_type m_rest;
		};

		// Needed so we don't have an empty tuple at the end taking up space
		template <typename T>
		class tuple<T>
		{
		private:
			T m_data;
		};

		template <>
		class tuple<>
		{
		};
	}


	template <typename... Args>
	class my_tuple;
	
	template <>
	class my_tuple<>
	{
	public:
		my_tuple() = default;
	};

	template <typename T>
	class my_tuple<T>
	{
	public:
		my_tuple() = default;

	private:
		T m_data;
	};
	
	template <typename T, typename R, typename...Args>
	class my_tuple<T, R, Args...>
	{
	public:
		my_tuple() = default;

	private:
		// for <T,Args...>
		// find out how many Args are T
		// Then chop those off Args
		static constexpr std::size_t index_of_next_type{ 1 };

		using rest_type = 
			typename std::conditional
			<
				(sizeof...(Args) > 0), 
				typename std::conditional
				<
					std::is_same<T, R>::value, 
					my_tuple<Args...>, 
					my_tuple<R,Args...>
				>::type, 
				R
			>::type;

		T m_data[index_of_next_type];
		rest_type m_rest;
	};
	// so this doesn't really change anything.
	

	template <std::size_t N>
	struct aligned
	{
		struct alignas(N) data
		{
		};
		static_assert(sizeof(data) == N, "whoops");

		data a;
	};

	using aligned1 = aligned<1>;
	using aligned2 = aligned<2>;
	using aligned4 = aligned<4>;
	using aligned8 = aligned<8>;
	using aligned16 = aligned<16>;

	struct aligned_test
	{
		aligned1 a;
		aligned1 b;
		aligned1 c;
		aligned4 d;
	};


	using args1_std_tuple = std::tuple<bool, int, bool, int>;
	using args1_my_tuple = my_tuple<bool, int, bool, int>;

	struct args1_struct
	{
		bool a;
		int b;
		bool c;
		int d;
	};

	using args2_std_tuple = std::tuple<bool, bool, int, int>;
	using args2_my_tuple = std::tuple<bool, bool, int, int>;

	struct args2_struct
	{
		bool a;
		bool b;
		int c;
		int d;
	};


}

void tuple_sizes::test()
{
	using namespace internal;

	std::cout << "Tuple Sizes Test" << std::endl << std::endl;

	std::cout << "Sizes:" << std::endl;
	std::cout << "sizeof(bool) = " << sizeof(bool) << std::endl;
	std::cout << "sizeof(short) = " << sizeof(short) << std::endl;
	std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
	std::cout << "sizeof(long) = " << sizeof(long) << std::endl;
	std::cout << "sizeof(aligned1) = " << sizeof(internal::aligned1) << std::endl;
	std::cout << "sizeof(aligned5) = " << sizeof(internal::aligned2) << std::endl;
	std::cout << "sizeof(aligned4) = " << sizeof(internal::aligned4) << std::endl;
	std::cout << "sizeof(aligned8) = " << sizeof(internal::aligned8) << std::endl;
	std::cout << "sizeof(aligned16) = " << sizeof(internal::aligned16) << std::endl;
	std::cout << std::endl;

	std::cout << "Alignments:" << std::endl;
	std::cout << "alignof(bool) = " << alignof(bool) << std::endl;
	std::cout << "alignof(short) = " << alignof(short) << std::endl;
	std::cout << "alignof(int) = " << alignof(int) << std::endl;
	std::cout << "alignof(long) = " << alignof(long) << std::endl;
	std::cout << "alignof(aligned1) = " << alignof(internal::aligned1) << std::endl;
	std::cout << "alignof(aligned5) = " << alignof(internal::aligned2) << std::endl;
	std::cout << "alignof(aligned4) = " << alignof(internal::aligned4) << std::endl;
	std::cout << "alignof(aligned8) = " << alignof(internal::aligned8) << std::endl;
	std::cout << "alignof(aligned16) = " << alignof(internal::aligned16) << std::endl;
	std::cout << std::endl;
	
	std::cout << "Arglist <bool, int, bool, int>" << std::endl;
	std::cout << "std::tuple sizeof = " << sizeof(internal::args1_std_tuple) << std::endl;
	std::cout << "my_tuple sizeof = " << sizeof(internal::args1_my_tuple) << std::endl;
	std::cout << "struct sizeof = " << sizeof(internal::args1_struct) << std::endl;
	std::cout << std::endl;
	std::cout << "std::tuple alignof = " << alignof(internal::args1_std_tuple) << std::endl;
	std::cout << "my_tuple alignof = " << alignof(internal::args1_my_tuple) << std::endl;
	std::cout << "struct alignof = " << alignof(internal::args1_struct) << std::endl;
	std::cout << std::endl;

	std::cout << "Arglist <bool, bool, int, int>" << std::endl;
	std::cout << "std::tuple size = " << sizeof(internal::args2_std_tuple) << std::endl;
	std::cout << "my_tuple size = " << sizeof(internal::args2_my_tuple) << std::endl;
	std::cout << "struct size = " << sizeof(internal::args2_struct) << std::endl;
	std::cout << std::endl;
	std::cout << "std::tuple alignof = " << alignof(internal::args2_std_tuple) << std::endl;
	std::cout << "my_tuple alignof = " << alignof(internal::args2_my_tuple) << std::endl;
	std::cout << "struct alignof = " << alignof(internal::args2_struct) << std::endl;
	std::cout << std::endl;


	std::cout << "v1::tuple<aligned1,aligned1,aligned1,aligned4> sizeof = " << sizeof(v1::tuple<aligned1, aligned1, aligned1, aligned4>) << std::endl;
	std::cout << "v2::tuple<aligned1,aligned1,aligned1,aligned4> sizeof = " << sizeof(v2::tuple<aligned1, aligned1, aligned1, aligned4>) << std::endl;
	std::cout << "v3::tuple<aligned1,aligned1,aligned1,aligned4> sizeof = " << sizeof(v3::tuple<aligned1, aligned1, aligned1, aligned4>) << std::endl;
	std::cout << "struct aligned_test sizeof = " << sizeof(aligned_test) << std::endl;
	std::cout << "v3::tuple<aligned1,aligned1,aligned1,aligned4>::front_end = " << v3::tuple<aligned1, aligned1, aligned1, aligned4>::front_end << std::endl;
	std::cout << std::endl;


	std::cout << "----------------------------------------" << std::endl;
}