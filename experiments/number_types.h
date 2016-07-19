#ifndef NUMBER_TYPES_H
#define NUMBER_TYPES_H

#include <cstdint>

namespace number_types
{
	/*
	Hard types for different number types.

	Logical number types:
	Any integer
	Any decimal
	Ranged integer
	Ranged decimal
	Fixed accuracy decimal

	Int <min, max, default>
	Decimal <min, max, exponent>

	Fixed <min, max, exponent>

	Starting with fixed point types:
	Stores a number as an integer with a fixed exponent, such that

	*/
	namespace internal
	{
		template <typename T_Int, int T_Exponent>
		class Fixed
		{
		public:
			using underlying_type = T_Int;

		private:
		};
	}


	template <int Exponent>
	class Fixed8;
	template <int Exponent>
	class Fixed16;
	template <int Exponent>
	class Fixed32;
	template <int Exponent>
	class Fixed64;

	template <int Exponent>
	class UFixed8;
	template <int Exponent>
	class UFixed16;
	template <int Exponent>
	class UFixed32;
	template <int Exponent>
	class UFixed64;




	void test();
}

#endif  // NUMBER_TYPES_H