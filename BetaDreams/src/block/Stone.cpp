// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Stone.h"

using namespace beta::block;

Stone::Stone()
{	}



const std::string& Stone::ingameId() const noexcept {
	static const std::string id = "beta_stone";
	return id;
}

bool Stone::isTransparent() const noexcept {
	return false;
}

uint32_t Stone::getBlockedSides() const noexcept {
	return	BlockedSide::UP		| BlockedSide::DOWN |
			BlockedSide::WEST	| BlockedSide::EAST |
			BlockedSide::NORTH	| BlockedSide::SOUTH;
}