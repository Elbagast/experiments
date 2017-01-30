#include "float_sigfigs.h"

#include <iostream>
#include <sstream>

namespace
{
	// For a given float value, return a float with only the supplied count of significant
	// figures. Do not round the values in the process.
	// e.g.
	// reduce_to_n_sigfigs(1.234567, 5) -> 1.2345
	// reduce_to_n_sigfigs(1.2345, 7) -> 1.234500

	float frexp10(float a_value, int * a_exponent)
	{
		// if supplied infinity or a nan or a 0 do nothing
		if (std::isinf(a_value) || std::isnan(a_value) || a_value == 0)
		{
			return a_value;
		}
		else
		{
			*a_exponent = static_cast<int>(1 + std::log10(std::fabs(a_value)));
			// raise the argument to the power of 10 x the negative of the extracted exponent.
			return a_value * static_cast<float>(std::pow(10, -(*a_exponent)));
		}
	}

	double frexp10(double a_value, int * a_exponent)
	{
		// if supplied infinity or a nan or a 0 do nothing
		if (std::isinf(a_value) || std::isnan(a_value) || a_value == 0)
		{
			return a_value;
		}
		else
		{
			*a_exponent = static_cast<int>(1 + std::log10(std::fabs(a_value)));
			// raise the argument to the power of 10 x the negative of the extracted exponent.
			return a_value * std::pow(10, -(*a_exponent));
		}
	}

	long double frexp10(long double a_value, int * a_exponent)
	{
		// if supplied infinity or a nan or a 0 do nothing
		if (std::isinf(a_value) || std::isnan(a_value) || a_value == 0)
		{
			return a_value;
		}
		else
		{
			*a_exponent = static_cast<int>(1 + std::log10(std::fabs(a_value)));
			// raise the argument to the power of 10 x the negative of the extracted exponent.
			return a_value * std::pow(10, -(*a_exponent));
		}
	}


	template <typename F>
	F imp_reduce_to_n_sigfigs(F a_value, int a_sigfigs)
	{
		// e.g. a_value = 1.23456789e-12, a_sigfigs = 5

		// copy the input
		F l_value{ a_value };

		// set the exponent to the number of figures - 1
		// value = 1.23456789e4 ->12345.6789
		int l_exponent{ 0 };
		l_value = frexp10(l_value, &l_exponent);
		int l_new_exponent{ (a_sigfigs < 1 ? 1 : a_sigfigs > std::numeric_limits<F>::digits10 ? std::numeric_limits<F>::digits10 : a_sigfigs) };
		l_value *= static_cast<F>(std::pow(10, l_new_exponent));

		// Truncate the value and set it
		// value = 12345 -> 1.2345e4
		l_value = std::trunc(l_value);

		// Go back to the old exponent
		// value = 1.2345e-12
		l_value *= static_cast<F>(std::pow(10, l_exponent - l_new_exponent));

		// finish
		return l_value;
	}

	float reduce_to_n_sigfigs(float a_value, int a_sigfigs)
	{
		return imp_reduce_to_n_sigfigs<float>(a_value, a_sigfigs);
	}
	double reduce_to_n_sigfigs(double a_value, int a_sigfigs)
	{
		return imp_reduce_to_n_sigfigs<double>(a_value, a_sigfigs);
	}
	long double reduce_to_n_sigfigs(long double a_value, int a_sigfigs)
	{
		return imp_reduce_to_n_sigfigs<long double>(a_value, a_sigfigs);
	}
}

// Determine a reliable way of limiting the number of significant figures in a floating point type

// e.g. 1.23456e5, 4 -> 1.234e5
float float_sigfigs::truncate_sigfigs_by_math(float a_value, int a_sigfigs)
{
	//return reduce_to_n_sigfigs(a_value, a_sigfigs);
	return reduce_to_n_sigfigs(a_value, a_sigfigs);
}

float float_sigfigs::truncate_sigfigs_by_string(float a_value, int a_sigfigs)
{
	return a_value;
}

double float_sigfigs::truncate_sigfigs_by_math(double a_value, int a_sigfigs)
{
	return reduce_to_n_sigfigs(a_value, a_sigfigs);
}

double float_sigfigs::truncate_sigfigs_by_string(double a_value, int a_sigfigs)
{
	return a_value;
}

long double float_sigfigs::truncate_sigfigs_by_math(long double a_value, int a_sigfigs)
{
	return reduce_to_n_sigfigs(a_value, a_sigfigs);
}

long double float_sigfigs::truncate_sigfigs_by_string(long double a_value, int a_sigfigs)
{
	return a_value;
}

// Output a float to a string with this many sigfigs
std::string float_sigfigs::to_string(float a_value)
{
	std::ostringstream l_ostream{};
	l_ostream.precision(std::numeric_limits<float>::digits10);
	l_ostream
		<< std::defaultfloat
		<< a_value;

	return l_ostream.str();
}

std::string float_sigfigs::to_string(double a_value)
{
	std::ostringstream l_ostream{};
	l_ostream.precision(std::numeric_limits<double>::digits10);
	l_ostream
		<< std::defaultfloat
		<< a_value;

	return l_ostream.str();
}

std::string float_sigfigs::to_string(long double a_value)
{
	std::ostringstream l_ostream{};
	l_ostream.precision(std::numeric_limits<long double>::digits10);
	l_ostream
		<< std::defaultfloat
		<< a_value;

	return l_ostream.str();
}

// Output a float to a string with this many sigfigs
std::string float_sigfigs::to_string(float a_value, int a_sigfigs)
{
	std::ostringstream l_ostream{};
	l_ostream.precision(a_sigfigs);
	l_ostream
		<< std::defaultfloat
		<< a_value;

	return l_ostream.str();
}

std::string float_sigfigs::to_string(double a_value, int a_sigfigs)
{
	std::ostringstream l_ostream{};
	l_ostream.precision(a_sigfigs);
	l_ostream
		<< std::defaultfloat
		<< a_value;

	return l_ostream.str();
}

std::string float_sigfigs::to_string(long double a_value, int a_sigfigs)
{
	std::ostringstream l_ostream{};
	l_ostream.precision(a_sigfigs);
	l_ostream
		<< std::defaultfloat
		<< a_value;

	return l_ostream.str();
}


void float_sigfigs::test()
{
	std::cout << "Float Significant Figures Test" << std::endl << std::endl;

	float l_f{ 1.234567890123456789e5f };
	double l_d{ 1.234567890123456789e5 };
	long double l_ld{ 1.234567890123456789e5l };

	std::cout << "raw = 1.234567890123456789e5" << std::endl;

	std::cout
		<< "default sigfigs: float = " << std::numeric_limits<float>::digits10
		<< " double = " << std::numeric_limits<double>::digits10
		<< " long double = " << std::numeric_limits<long double>::digits10
		<< std::endl;
	std::cout << std::endl;

	std::cout << "Truncated to default figures on output:" << std::endl;
	std::cout << "float:       " << to_string(l_f) << std::endl;
	std::cout << "double:      " << to_string(l_d) << std::endl;
	std::cout << "long double: " << to_string(l_ld) << std::endl;
	std::cout << std::endl;

	std::cout << "Truncated to 4 figures on output:" << std::endl;
	std::cout << "float:       " << to_string(l_f, 4) << std::endl;
	std::cout << "double:      " << to_string(l_d, 4) << std::endl;
	std::cout << "long double: " << to_string(l_ld, 4) << std::endl;
	std::cout << std::endl;

	std::cout << "Truncated to 4 figures by math, then truncated to default figures on output:" << std::endl;
	std::cout << "float:       " << to_string(truncate_sigfigs_by_math(l_f, 4)) << std::endl;
	std::cout << "double:      " << to_string(truncate_sigfigs_by_math(l_d, 4)) << std::endl;
	std::cout << "long double: " << to_string(truncate_sigfigs_by_math(l_ld, 4)) << std::endl;
	std::cout << std::endl;

	std::cout << "Truncated to 4 figures by math, then truncated to 4 figures on output:" << std::endl;
	std::cout << "float:       " << to_string(truncate_sigfigs_by_math(l_f, 4), 4) << std::endl;
	std::cout << "double:      " << to_string(truncate_sigfigs_by_math(l_d, 4), 4) << std::endl;
	std::cout << "long double: " << to_string(truncate_sigfigs_by_math(l_ld, 4), 4) << std::endl;
	std::cout << std::endl;

	{
		float l_f1{ 1e-5f };
		double l_d1{ 1e-5 };
		long double l_ld1{ 1e-5l };

		std::cout << "raw = 1e-5" << std::endl;

		std::cout << "Truncated to default figures on output:" << std::endl;
		std::cout << "float:       " << to_string(l_f1) << std::endl;
		std::cout << "double:      " << to_string(l_d1) << std::endl;
		std::cout << "long double: " << to_string(l_ld1) << std::endl;
		std::cout << std::endl;

		std::cout << "Truncated to 4 figures on output:" << std::endl;
		std::cout << "float:       " << to_string(l_f1, 4) << std::endl;
		std::cout << "double:      " << to_string(l_d1, 4) << std::endl;
		std::cout << "long double: " << to_string(l_ld1, 4) << std::endl;
		std::cout << std::endl;


		std::cout << "Truncated to 4 figures by math, then truncated to default figures on output:" << std::endl;
		std::cout << "float:       " << to_string(truncate_sigfigs_by_math(l_f1, 4)) << std::endl;
		std::cout << "double:      " << to_string(truncate_sigfigs_by_math(l_d1, 4)) << std::endl;
		std::cout << "long double: " << to_string(truncate_sigfigs_by_math(l_ld1, 4)) << std::endl;
		std::cout << std::endl;

		std::cout << "Truncated to 4 figures by math, then truncated to 4 figures on output:" << std::endl;
		std::cout << "float:       " << to_string(truncate_sigfigs_by_math(l_f1, 4), 4) << std::endl;
		std::cout << "double:      " << to_string(truncate_sigfigs_by_math(l_d1, 4), 4) << std::endl;
		std::cout << "long double: " << to_string(truncate_sigfigs_by_math(l_ld1, 4), 4) << std::endl;
		std::cout << std::endl;
	}

	{
		float l_f1{ 1e0f };
		double l_d1{ 1e0 };
		long double l_ld1{ 1e0l };

		std::cout << "raw = 1e0" << std::endl;

		std::cout << "Truncated to default figures on output:" << std::endl;
		std::cout << "float:       " << to_string(l_f1) << std::endl;
		std::cout << "double:      " << to_string(l_d1) << std::endl;
		std::cout << "long double: " << to_string(l_ld1) << std::endl;
		std::cout << std::endl;

		std::cout << "Truncated to 4 figures on output:" << std::endl;
		std::cout << "float:       " << to_string(l_f1, 4) << std::endl;
		std::cout << "double:      " << to_string(l_d1, 4) << std::endl;
		std::cout << "long double: " << to_string(l_ld1, 4) << std::endl;
		std::cout << std::endl;


		std::cout << "Truncated to 4 figures by math, then truncated to default figures on output:" << std::endl;
		std::cout << "float:       " << to_string(truncate_sigfigs_by_math(l_f1, 4)) << std::endl;
		std::cout << "double:      " << to_string(truncate_sigfigs_by_math(l_d1, 4)) << std::endl;
		std::cout << "long double: " << to_string(truncate_sigfigs_by_math(l_ld1, 4)) << std::endl;
		std::cout << std::endl;

		std::cout << "Truncated to 4 figures by math, then truncated to 4 figures on output:" << std::endl;
		std::cout << "float:       " << to_string(truncate_sigfigs_by_math(l_f1, 4), 4) << std::endl;
		std::cout << "double:      " << to_string(truncate_sigfigs_by_math(l_d1, 4), 4) << std::endl;
		std::cout << "long double: " << to_string(truncate_sigfigs_by_math(l_ld1, 4), 4) << std::endl;
		std::cout << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;
}
