// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_DIRECTIONS_H_INCLUDED
#define BETA_UTILITY_DIRECTIONS_H_INCLUDED

#include <glm/glm.hpp>

namespace beta::utility::direction {
	constexpr glm::vec3 NORTH(0, 0, -1);
	constexpr glm::vec3 SOUTH(0, 0,  1);

	constexpr glm::vec3 WEST(-1, 0, 0);
	constexpr glm::vec3 EAST( 1, 0, 0);

	constexpr glm::vec3 UP(0, 1, 0);
	constexpr glm::vec3 DOWN(0, -1, 0);

	constexpr glm::vec3 NORTH_WEST = NORTH + WEST;
	constexpr glm::vec3 NORTH_EAST = NORTH + EAST;
	constexpr glm::vec3 SOUTH_WEST = SOUTH + WEST;
	constexpr glm::vec3 SOUTH_EAST = SOUTH + EAST;

	constexpr glm::vec3 NORTH_WEST_UP	= NORTH_WEST + UP;
	constexpr glm::vec3 NORTH_EAST_UP	= NORTH_EAST + UP;
	constexpr glm::vec3 SOUTH_WEST_UP	= SOUTH_WEST + UP;
	constexpr glm::vec3 SOUTH_EAST_UP	= SOUTH_EAST + UP;
	constexpr glm::vec3 NORTH_WEST_DOWN = NORTH_WEST + DOWN;
	constexpr glm::vec3 NORTH_EAST_DOWN = NORTH_EAST + DOWN;
	constexpr glm::vec3 SOUTH_WEST_DOWN = SOUTH_WEST + DOWN;
	constexpr glm::vec3 SOUTH_EAST_DOWN = SOUTH_EAST + DOWN;
}

#endif // !BETA_UTILITY_DIRECTIONS_H_INCLUDED
