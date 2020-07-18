// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Chunk.h"

#include <cmath>

using namespace beta::world;

Chunk::Chunk() {
	for (uint32_t y = 0; y < SIZE; ++y) {
		for (uint32_t z = 0; z < SIZE; ++z) {
			for (uint32_t x = 0; x < SIZE; ++x) {
				if (y < 8 * (std::sin(x) + std::cos(z) + 1)) {
					this->blockPtrAt(x, y, z) = std::make_unique<block::Stone>();
				}
				else {
					this->blockPtrAt(x, y, z) = std::make_unique<block::Air>();
				}
			}
		}
	}
}

Chunk::Chunk(Chunk&& other) noexcept {
	*this = std::move(other);
}



Block& Chunk::blockAt(uint32_t x, uint32_t y, uint32_t z) {
	return *m_blocks.at(x, y, z);
}

const Block& Chunk::blockAt(uint32_t x, uint32_t y, uint32_t z) const {
	return *m_blocks.at(x, y, z);
}

std::unique_ptr<Block>& Chunk::blockPtrAt(uint32_t x, uint32_t y, uint32_t z) {
	return m_blocks.at(x, y, z);
}



Chunk& Chunk::operator=(Chunk&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	this->m_blocks = std::move(other.m_blocks);

	return *this;
}