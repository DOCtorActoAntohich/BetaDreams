// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_MATH_H_INCLUDED
#define BETA_UTILITY_MATH_H_INCLUDED

#include <cstdint>

namespace beta::utility::math {
	template <typename T> int32_t sign(T number) {
		// Source:
		// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
		return (T(0) < number) - (number < T(0));
	}
}

#endif // !BETA_UTILITY_MATH_H_INCLUDED
