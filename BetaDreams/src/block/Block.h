// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_BLOCK_BLOCK_H_INCLUDED
#define BETA_BLOCK_BLOCK_H_INCLUDED

#include <string>

#include "graphics/Texture.h"

namespace beta::block {
	namespace BlockedSide {
		enum : uint32_t {
			NONE	= 0,
			NORTH	= 1 << 0,
			SOUTH	= 1 << 1,
			WEST	= 1 << 2,
			EAST	= 1 << 3,
			UP		= 1 << 4,
			DOWN	= 1 << 5,
		};
	}


	class Block {
	public:
		Block();

		static constexpr float_t SIZE = 1.0f;
		static constexpr float_t HALF_SIZE = SIZE / 2.0f;

		virtual const std::string& ingameId() const noexcept = 0;
		virtual bool isTransparent() const noexcept = 0;

		virtual uint32_t getBlockedSides() const noexcept = 0;
		bool doesBlockSide(uint32_t sides) const noexcept;
	private:
	};
}

#endif // !BETA_BLOCK_BLOCK_H_INCLUDED
