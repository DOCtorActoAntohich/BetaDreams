// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_BLOCK_AIR_H_INCLUDED
#define BETA_BLOCK_AIR_H_INCLUDED

#include "Block.h"

namespace beta::block {
	class Air : public Block {
	public:
		Air();

		const std::string& ingameId() const noexcept override;
		bool isTransparent() const noexcept override;
		uint32_t getBlockedSides() const noexcept override;
	private:
	};
}

#endif // !BETA_BLOCK_AIR_H_INCLUDED
