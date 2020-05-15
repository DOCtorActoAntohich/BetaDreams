// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "utility/Color.h"

#include <limits>

using namespace beta::utility;


const Color Color::m_cornflowerBlue(99, 149, 238);



Color::Color()
	: m_red(0), m_green(0), m_blue(0), m_alpha(0)
{}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: m_red(r), m_green(g), m_blue(b), m_alpha(a)
{}



std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> Color::components() const noexcept {
	return { m_red, m_green, m_blue, m_alpha };
}

std::tuple<float_t, float_t, float_t, float_t> Color::glComponents() const noexcept {
	static const uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();
	float_t r = static_cast<float_t>(m_red)		/ MAX_VALUE;
	float_t g = static_cast<float_t>(m_green)	/ MAX_VALUE;
	float_t b = static_cast<float_t>(m_blue)	/ MAX_VALUE;
	float_t a = static_cast<float_t>(m_alpha)	/ MAX_VALUE;

	return { r, g, b, a };
}



const Color& Color::cornflowerBlue() noexcept {
	return Color::m_cornflowerBlue;
}