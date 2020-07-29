// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Block.h"

#include "engine/VAO.h"
#include "utility/Directions.h"

using namespace beta::block;


Block::Block() {
	/*
	float_t x = static_cast<float_t>(xCenter);
	float_t y = static_cast<float_t>(yCenter);
	float_t z = static_cast<float_t>(zCenter);

	using namespace utility::direction;

	auto getVertex = [](const glm::vec3& first, const glm::vec3& second, const glm::vec3& third) -> glm::vec3 {
		return first * HALF_SIZE + second * HALF_SIZE + third * HALF_SIZE;
	};

	glm::vec3 northWestUp	= getVertex(NORTH, WEST, UP);
	glm::vec3 northWestDown = getVertex(NORTH, WEST, DOWN);
	glm::vec3 northEastUp	= getVertex(NORTH, EAST, UP);
	glm::vec3 northEastDown = getVertex(NORTH, EAST, DOWN);

	glm::vec3 southWestUp	= getVertex(SOUTH, WEST, UP);
	glm::vec3 southWestDown = getVertex(SOUTH, WEST, DOWN);
	glm::vec3 southEastUp	= getVertex(SOUTH, EAST, UP);
	glm::vec3 southEastDown = getVertex(SOUTH, EAST, DOWN);

	m_up.load("resource/texture/up.png");
	m_down.load("resource/texture/down.png");
	m_north.load("resource/texture/north.png");
	m_south.load("resource/texture/south.png");
	m_west.load("resource/texture/west.png");
	m_east.load("resource/texture/east.png");
	*/
}


bool Block::doesBlockSide(uint32_t sides) const noexcept {
	return (this->getBlockedSides() & sides) != BlockedSide::NONE;
}