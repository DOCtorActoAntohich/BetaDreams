// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_BLOCK_BLOCK_H_INCLUDED
#define BETA_BLOCK_BLOCK_H_INCLUDED

#include <string>

#include "graphics/Texture.h"

namespace beta::block {
	class Block {
	public:
		Block();

		static constexpr float_t SIZE = 1.0f;
		static constexpr float_t HALF_SIZE = SIZE / 2.0f;

		virtual const std::string& ingameId() const = 0;
		virtual bool isTransparent() const = 0;
	private:
	};
}

#endif // !BETA_BLOCK_BLOCK_H_INCLUDED
