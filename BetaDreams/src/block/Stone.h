// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_BLOCK_STONE_H_INCLUDED
#define BETA_BLOCK_STONE_H_INCLUDED

#include "Block.h"

namespace beta::block {
	class Stone : public Block {
	public:
		Stone();

		const std::string& ingameId() const override;
		bool isTransparent() const override;
	private:
	};
}

#endif // !BETA_BLOCK_STONE_H_INCLUDED
