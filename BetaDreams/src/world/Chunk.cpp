// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Chunk.h"

using namespace beta::world;

Chunk::Chunk() {
	for (uint32_t y = 0; y < SIZE; ++y) {
		for (uint32_t z = 0; z < SIZE; ++z) {
			for (uint32_t x = 0; x < SIZE; ++x) {
				this->blockPtrAt(x, y, z) = std::make_unique<block::Air>();
			}
		}
	}
	this->blockPtrAt(1, 1, 2) = std::make_unique<block::Stone>();
	this->blockPtrAt(1, 1, 0) = std::make_unique<block::Stone>();
	this->blockPtrAt(1, 2, 1) = std::make_unique<block::Stone>();
	this->blockPtrAt(1, 0, 1) = std::make_unique<block::Stone>();
	this->blockPtrAt(2, 1, 1) = std::make_unique<block::Stone>();
	this->blockPtrAt(0, 1, 1) = std::make_unique<block::Stone>();

	this->blockPtrAt(5, 5, 5) = std::make_unique<block::Stone>();
	this->blockPtrAt(5, 6, 5) = std::make_unique<block::Stone>();
	this->blockPtrAt(5, 6, 6) = std::make_unique<block::Stone>();
	this->blockPtrAt(5, 7, 6) = std::make_unique<block::Stone>();
}

Chunk::Chunk(Chunk&& other) noexcept {
	*this = std::move(other);
}



Block& Chunk::blockAt(uint32_t x, uint32_t y, uint32_t z) {
	return *m_blocks[(y * SIZE + z) * SIZE + x];
}

const Block& Chunk::blockAt(uint32_t x, uint32_t y, uint32_t z) const {
	return *m_blocks[(y * SIZE + z) * SIZE + x];
}

std::unique_ptr<Block>& Chunk::blockPtrAt(uint32_t x, uint32_t y, uint32_t z) {
	return m_blocks[(y * SIZE + z) * SIZE + x];
}



Chunk& Chunk::operator=(Chunk&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	this->m_blocks = std::move(other.m_blocks);
}