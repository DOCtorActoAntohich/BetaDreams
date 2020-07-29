// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Rectangle2D.h"

using namespace beta::utility::types;

Rectangle2D::Rectangle2D() : Rectangle2D(0, 0, 0, 0)
{	}

Rectangle2D::Rectangle2D(int32_t x, int32_t y, uint32_t w, uint32_t h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool Rectangle2D::isEmpty() const noexcept {
	return x == y && y == 0 && w == h && h == 0;
}

uint32_t Rectangle2D::volume() const noexcept {
	return this->w * this->h;
}

bool Rectangle2D::operator==(const Rectangle2D& other) {
	return this->x == other.x &&
		this->y == other.y &&
		this->w == other.w &&
		this->h == other.h;
}

bool Rectangle2D::operator!=(const Rectangle2D& other) {
	return this->x != other.x ||
		this->y != other.y ||
		this->w != other.w ||
		this->h != other.h;
}