// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_WORLD_CHUNK_H_INCLUDED
#define BETA_WORLD_CHUNK_H_INCLUDED

#include <array>
#include <memory>

#include "block/Blocks.h"

namespace beta::world {
	using block::Block;

	class Chunk {
	public:
		Chunk();
		Chunk(Chunk&& other) noexcept;

		Block& blockAt(uint32_t x, uint32_t y, uint32_t z);
		const Block& blockAt(uint32_t x, uint32_t y, uint32_t z) const;

		template<class T_Block>
		void setBlock(uint32_t x, uint32_t y, uint32_t z) {
			m_blocks[(y * SIZE + z) * SIZE + x] = std::unique_ptr<T_Block>();
		}

		Chunk& operator=(Chunk&& other) noexcept;

		static constexpr uint32_t SIZE = 16;
		static constexpr uint32_t MAX_BLOCKS = SIZE * SIZE * SIZE;
	private:
		std::array<std::unique_ptr<Block>, MAX_BLOCKS> m_blocks;

		std::unique_ptr<Block>& blockPtrAt(uint32_t x, uint32_t y, uint32_t z);
	};
}

#endif // !BETA_WORLD_CHUNK_H_INCLUDED
