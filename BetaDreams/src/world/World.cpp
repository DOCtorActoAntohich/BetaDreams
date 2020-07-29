// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "World.h"

#include "graphics/renderer/ChunkRenderer.h"
#include "engine/VAO.h"
#include "utility/Math.h"

using namespace beta::world;

void World::addEmptyChunk(const glm::vec3& position) {
	m_chunks[position] = Chunk();
}

void World::moveChunk(const glm::vec3& position, Chunk& chunk) {
	m_chunks[position] = std::move(chunk);
}

const Chunk& World::getChunk(const glm::vec3& position) const {
	return m_chunks.at(position);
}

void World::deleteChunk(const glm::vec3& position) {

}



Block& World::blockAt(const glm::vec3& position) {
	glm::vec3 chunkPos = World::blockToChunkPosition(position);
	Chunk& chunk = m_chunks.at(chunkPos);

	glm::vec<3, uint32_t> offset = position - World::chunkToBlockPosition(chunkPos);
	return chunk.blockAt(offset.x, offset.y, offset.z);
}

const Block& World::blockAt(const glm::vec3& position) const {
	glm::vec3 chunkPos = World::blockToChunkPosition(position);
	const Chunk& chunk = m_chunks.at(chunkPos);

	glm::vec<3, uint32_t> offset = position - World::chunkToBlockPosition(chunkPos);
	return chunk.blockAt(offset.x, offset.y, offset.z);
}



void World::renderAll() {
	m_chunkMeshes.clear();
	for (auto& [position, _] : m_chunks) {
		this->renderChunk(position);
	}
}

void World::renderChunk(const glm::vec3& position) {
	static auto getChunksNeighborhood = [&](const glm::vec3& position) {
		graphics::renderer::ChunkRenderer::ChunkNeighborhood neighborhood;
		for (int32_t y = -1; y <= 1; ++y) {
			for (int32_t z = -1; z <= 1; ++z) {
				for (int32_t x = -1; x <= 1; ++x) {
					auto newPos = position + glm::vec3(x, y, z);

					neighborhood.at(x + 1, y + 1, z + 1) = nullptr;
					if (m_chunks.count(newPos) != 0) {
						neighborhood.at(x + 1, y + 1, z + 1) = &m_chunks[newPos];
					}
				}
			}
		}
		return neighborhood;
	};

	using graphics::renderer::ChunkRenderer;
	auto neighborhood = getChunksNeighborhood(position);
	m_chunkMeshes[position] = ChunkRenderer::makeMesh(position, neighborhood);
}

void World::draw() const {
	for (auto& [_, mesh] : m_chunkMeshes) {
		mesh->draw();
	}
}



glm::vec3 World::chunkToBlockPosition(const glm::vec3& chunkCenter) {
	// Some examples of chunk positions and blocks offsets for chunk size 16.
	// 0.5	=> 0.5.
	// 1.5	=> 16.5.
	// 2.5	=> 32.5.
	// -0.5 => -15.5.
	// -1.5 => -31.5.
	return glm::vec3{
		(chunkCenter.x - Block::HALF_SIZE) * Chunk::SIZE + Block::HALF_SIZE,
		(chunkCenter.y - Block::HALF_SIZE) * Chunk::SIZE + Block::HALF_SIZE,
		(chunkCenter.z - Block::HALF_SIZE) * Chunk::SIZE + Block::HALF_SIZE
	};
}

glm::vec3 World::blockToChunkPosition(const glm::vec3& blockCenter) {
	// Formula comes from chunk to block position formula.
	return glm::vec3{
		static_cast<int32_t>(blockCenter.x - Block::HALF_SIZE) / Chunk::SIZE + Block::HALF_SIZE,
		static_cast<int32_t>(blockCenter.y - Block::HALF_SIZE) / Chunk::SIZE + Block::HALF_SIZE,
		static_cast<int32_t>(blockCenter.z - Block::HALF_SIZE) / Chunk::SIZE + Block::HALF_SIZE
	};
}

bool World::isValidPos(const glm::vec3& position) {
	[[maybe_unused]] float_t intpart;
	float_t x = std::modf(std::abs(position.x), &intpart);
	float_t y = std::modf(std::abs(position.y), &intpart);
	float_t z = std::modf(std::abs(position.z), &intpart);
	return x == y && y == z && z == 0.5f; //-V550
}