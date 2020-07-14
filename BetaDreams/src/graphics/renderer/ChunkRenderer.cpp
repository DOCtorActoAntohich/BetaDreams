// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkRenderer.h"

#include <vector>
#include <glm/vec2.hpp>

#include "world/World.h"
#include "utility/Math.h"
#include "utility/Directions.h"

using namespace beta::graphics;

std::unique_ptr<VAO> renderer::ChunkRenderer::makeMesh(const glm::vec3& position, const world::Chunk& chunk) {
	using world::Chunk;
	using block::Block;

	static constexpr uint32_t MAX_CUBE_SIDES = world::Chunk::MAX_BLOCKS * 6;
	static constexpr uint32_t VERTICES_PER_SIDE = 6;

	static constexpr uint32_t VERTEX_SIZE = 3;
	static constexpr uint32_t MAX_VERTICES = MAX_CUBE_SIDES * VERTEX_SIZE * VERTICES_PER_SIDE;

	static constexpr uint32_t TEXTURE_COORDINATE_SIZE = 2;
	static constexpr uint32_t MAX_TEXTURE_COORDINATES = MAX_CUBE_SIDES * TEXTURE_COORDINATE_SIZE * VERTICES_PER_SIDE;

	std::vector<float_t> vertexBuffer;
	std::vector<float_t> textureCoordinatesBuffer;

	vertexBuffer.reserve(MAX_VERTICES);
	textureCoordinatesBuffer.reserve(MAX_TEXTURE_COORDINATES);

	auto isBlocked = [&chunk](uint32_t x, uint32_t y, uint32_t z) -> bool {
		auto isInside = [](uint32_t x, uint32_t y, uint32_t z) -> bool {
			return (x < Chunk::SIZE) && (y < Chunk::SIZE) && (z < Chunk::SIZE);
		};

		return isInside(x, y, z) && !chunk.blockAt(x, y, z).isTransparent();
	};


	glm::vec3 blocksOffset = world::World::chunkToBlockPosition(position);

	auto addToMesh = [&](glm::vec3 vertex, glm::vec2 textureCoordinates) -> void {
		vertexBuffer.push_back(vertex.x);
		vertexBuffer.push_back(vertex.y);
		vertexBuffer.push_back(vertex.z);

		textureCoordinatesBuffer.push_back(textureCoordinates.x);
		textureCoordinatesBuffer.push_back(textureCoordinates.y);
	};


	for (uint32_t y = 0; y < world::Chunk::SIZE; ++y) {
		for (uint32_t z = 0; z < world::Chunk::SIZE; ++z) {
			for (uint32_t x = 0; x < world::Chunk::SIZE; ++x) {
				const Block& block = chunk.blockAt(x, y, z);

				if (block.isTransparent()) {
					continue;
				}

				glm::vec blockCenter = blocksOffset + glm::vec3(x, y, z);

				using namespace beta::utility::direction;
				if (!isBlocked(x, y - 1, z)) {
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_DOWN, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_DOWN, { 0, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_DOWN, { 1, 1 });

					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_DOWN, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_DOWN, { 1, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_DOWN, { 1, 0 });
				}
				if (!isBlocked(x, y + 1, z)) {
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_UP, { 0, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_UP, { 1, 1 });

					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_UP, { 1, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_UP, { 1, 0 });
				}

				if (!isBlocked(x, y, z - 1)) {
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_DOWN, { 0, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_DOWN, { 1, 1 });

					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_DOWN, { 1, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_UP, { 1, 0 });
				}
				if (!isBlocked(x, y, z + 1)) {
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_DOWN, { 0, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_DOWN, { 1, 1 });

					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_DOWN, { 1, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_UP, { 1, 0 });
				}

				if (!isBlocked(x - 1, y, z)) {
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_DOWN, { 0, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_DOWN, { 1, 1 });

					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_WEST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_DOWN, { 1, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_WEST_UP, { 1, 0 });
				}
				if (!isBlocked(x + 1, y, z)) {
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_DOWN, { 0, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_DOWN, { 1, 1 });

					addToMesh(blockCenter + Block::HALF_SIZE * SOUTH_EAST_UP, { 0, 0 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_DOWN, { 1, 1 });
					addToMesh(blockCenter + Block::HALF_SIZE * NORTH_EAST_UP, { 1, 0 });
				}
			}
		}
	}

	auto mesh = std::make_unique<VAO>();
	mesh->attach({ vertexBuffer, 3 })
		 .attach({ textureCoordinatesBuffer, 2 });

	return mesh;
}