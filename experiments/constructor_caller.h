#ifndef CONSTRUCTOR_CALLER_H
#define CONSTRUCTOR_CALLER_H

#include <type_traits>

namespace constructor_caller
{
	template <typename T>
	struct Default_Constructor
	{
		static_assert(std::is_default_constructible_v<T>, "Supplied type is not default constructible.");

		T operator()()
		{
			return T();
		}
	};

	template <typename T>
	struct Copy_Constructor
	{
		static_assert(std::is_copy_constructible_v<T>, "Supplied type is not copy constructible.");

		T operator()(T const& a_arg)
		{
			return T(a_arg);
		}
	};

	template <typename T>
	struct Move_Constructor
	{
		static_assert(std::is_move_constructible_v<T>, "Supplied type is not move constructible.");

		T operator()(T && a_arg)
		{
			return T(std::forward<T>(a_arg));
		}
	};

	template <typename... Args>
	struct Constructor;

	template <typename T>
	struct Constructor<T> : public Default_Constructor<T>{};

	template <typename T>
	struct Constructor<T, T const&> : public Copy_Constructor<T> {};

	template <typename T>
	struct Constructor<T, T &&> : public Move_Constructor<T> {};

	template <typename T, typename... Args>
	struct Constructor<T, Args...>
	{
		static_assert(std::is_constructible_v<T, Args...>, "Supplied type has no constructor that can use the supplied argument types.");

		T operator()(Args... a_args)
		{
			return T(std::forward<Args>(a_args)...);
		}
	};

	void test();
} // namespace macro_class

#endif // CONSTRUCTOR_CALLER_H