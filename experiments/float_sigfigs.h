#ifndef FLOAT_SIGFIGS_H
#define FLOAT_SIGFIGS_H

#include <string>

namespace float_sigfigs
{
	// Determine a reliable way of limiting the number of significant figures in a floating point type

	// e.g. 1.23456e5, 4 -> 1.234e5
	float truncate_sigfigs_by_math(float a_value, int a_sigfigs);
	float truncate_sigfigs_by_string(float a_value, int a_sigfigs);

	double truncate_sigfigs_by_math(double a_value, int a_sigfigs);
	double truncate_sigfigs_by_string(double a_value, int a_sigfigs);
	
	long double truncate_sigfigs_by_math(long double a_value, int a_sigfigs);
	long double truncate_sigfigs_by_string(long double a_value, int a_sigfigs);

	// Output a float to a string with this many sigfigs

	std::string to_string(float a_value);
	std::string to_string(double a_value);
	std::string to_string(long double a_value);

	std::string to_string(float a_value, int a_sigfigs);
	std::string to_string(double a_value, int a_sigfigs);
	std::string to_string(long double a_value, int a_sigfigs);

	void test();

} // float_sigfigs


#endif // FLOAT_SIGFIGS_H
