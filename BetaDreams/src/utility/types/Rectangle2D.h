// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_TYPES_RECTANGLE_2D_H_INCLUDED
#define BETA_UTILITY_TYPES_RECTANGLE_2D_H_INCLUDED

#include <cstdint>

namespace beta::utility::types {
	struct Rectangle2D {
	public:
		int32_t	 x, y;
		uint32_t w, h;

		Rectangle2D();
		Rectangle2D(int32_t x, int32_t y, uint32_t w, uint32_t h);

		bool isEmpty() const noexcept;

		uint32_t volume() const noexcept;

		bool operator==(const Rectangle2D& other);
		bool operator!=(const Rectangle2D& other);
	};
}

#endif // !BETA_UTILITY_TYPES_RECTANGLE_2D_H_INCLUDED