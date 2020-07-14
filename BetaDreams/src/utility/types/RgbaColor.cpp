// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RgbaColor.h"

#include <limits>

using namespace beta::utility::types;

RgbaColor::RgbaColor()
	: m_red(0), m_green(0), m_blue(0), m_alpha(0)
{}

RgbaColor::RgbaColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: m_red(r), m_green(g), m_blue(b), m_alpha(a)
{}



std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> RgbaColor::components() const noexcept {
	return { m_red, m_green, m_blue, m_alpha };
}

std::tuple<float_t, float_t, float_t, float_t> RgbaColor::glComponents() const noexcept {
	static constexpr uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();
	float_t r = static_cast<float_t>(m_red)		/ MAX_VALUE;
	float_t g = static_cast<float_t>(m_green)	/ MAX_VALUE;
	float_t b = static_cast<float_t>(m_blue)	/ MAX_VALUE;
	float_t a = static_cast<float_t>(m_alpha)	/ MAX_VALUE;

	return { r, g, b, a };
}



const RgbaColor& RgbaColor::cornflowerBlue() noexcept {
	static RgbaColor cornflowerBlueColor = { 99, 149, 238 };
	return cornflowerBlueColor;
}