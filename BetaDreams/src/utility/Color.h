// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_COLOR_H_INCLUDED
#define BETA_UTILITY_COLOR_H_INCLUDED

#include <cstdint>
#include <tuple>

namespace beta::utility {
	class Color final {
	public:
		Color();
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> components() const noexcept;
		std::tuple<float_t, float_t, float_t, float_t> glComponents() const noexcept;
		
		static const Color& cornflowerBlue() noexcept;

	private:
		uint8_t m_red;
		uint8_t m_green;
		uint8_t m_blue;
		uint8_t m_alpha;
	};
}

#endif // !BETA_UTILITY_COLOR_H_INCLUDED
