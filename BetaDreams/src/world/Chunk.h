// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_WORLD_CHUNK_H_INCLUDED
#define BETA_WORLD_CHUNK_H_INCLUDED

#include <memory>

#include "block/Blocks.h"
#include "Types.h"

namespace beta::world {
	using block::Block;

	class Chunk {
	public:
		Chunk();
		Chunk(Chunk&& other) noexcept;

		Block& blockAt(uint32_t x, uint32_t y, uint32_t z);
		const Block& blockAt(uint32_t x, uint32_t y, uint32_t z) const;

		Chunk& operator=(Chunk&& other) noexcept;

		static constexpr uint32_t SIZE = 16;
		static constexpr uint32_t MAX_BLOCKS = SIZE * SIZE * SIZE;
	private:
		Array3<std::unique_ptr<Block>, SIZE, SIZE, SIZE> m_blocks;

		std::unique_ptr<Block>& blockPtrAt(uint32_t x, uint32_t y, uint32_t z);
	};
}

#endif // !BETA_WORLD_CHUNK_H_INCLUDED
