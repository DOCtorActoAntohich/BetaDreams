// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Math.h"

int32_t beta::utility::math::mod(int32_t number, int32_t m) {
	return ((number % m) + m) % m;
}

bool beta::utility::math::isPowerOf2(int32_t number) {
	return (number != 0) && ((number & (number - 1)) == 0);
}