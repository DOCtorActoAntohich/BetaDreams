// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkRenderer.h"

#include <vector>
#include <glm/vec2.hpp>

#include "graphics/renderer/SimpleBlockRenderer.h"
#include "utility/Directions.h"
#include "utility/Math.h"
#include "world/World.h"

using namespace beta::graphics;

std::unique_ptr<VAO> renderer::ChunkRenderer::makeMesh(const glm::vec3& position, const ChunkNeighborhood& chunks) {
	using world::Chunk;
	using block::Block;

	static constexpr uint32_t PRIMITIVE_CUBE_SIDES = world::Chunk::MAX_BLOCKS * 6;
	static constexpr uint32_t VERTICES_PER_SIDE = 6;

	static constexpr uint32_t VERTEX_SIZE = 3;
	static constexpr uint32_t CUBE_VERTICES = PRIMITIVE_CUBE_SIDES * VERTEX_SIZE * VERTICES_PER_SIDE;

	static constexpr uint32_t TEXTURE_COORDINATE_SIZE = 2;
	static constexpr uint32_t CUBE_TEXTURE_COORDINATES = PRIMITIVE_CUBE_SIDES * TEXTURE_COORDINATE_SIZE * VERTICES_PER_SIDE;

	std::vector<float_t> vertexBuffer;
	std::vector<float_t> textureCoordinatesBuffer;

	vertexBuffer.reserve(CUBE_VERTICES);
	textureCoordinatesBuffer.reserve(CUBE_TEXTURE_COORDINATES);


	static auto getBlockNeighborhood = [&](int32_t x, int32_t y, int32_t z) {
		static auto getChunkPos = [](int32_t blockpos) {
			static constexpr int32_t CENTER = 1;
			if (blockpos < 0) {
				return CENTER - 1;
			}
			if (blockpos >= Chunk::SIZE) {
				return CENTER + 1;
			}
			return CENTER;
		};

		SimpleBlockRenderer::BlockNeighborhood neighborhood;
		for (int32_t yi = -1; yi <= 1; ++yi) {
			for (int32_t zi = -1; zi <= 1; ++zi) {
				for (int32_t xi = -1; xi <= 1; ++xi) {
					int32_t xres = x + xi, yres = y + yi, zres = z + zi;

					int32_t xchunk = getChunkPos(xres),
							ychunk = getChunkPos(yres),
							zchunk = getChunkPos(zres);

					neighborhood.at(xi + 1, yi + 1, zi + 1) = nullptr;  

					if (chunks.at(xchunk, ychunk, zchunk) == nullptr) {
						continue;
					}

					const Chunk& chunk = *chunks.at(xchunk, ychunk, zchunk);

					xres = utility::math::mod(xres, Chunk::SIZE);
					yres = utility::math::mod(yres, Chunk::SIZE);
					zres = utility::math::mod(zres, Chunk::SIZE);

					neighborhood.at(xi + 1, yi + 1, zi + 1) = &chunk.blockAt(xres, yres, zres);
				}
			}
		}
		return neighborhood;
	};


	static constexpr glm::vec3 center = { 1, 1, 1 };

	static auto getCentralChunk = [&]() -> const Chunk& {
		return *chunks.at(static_cast<uint32_t>(center.x),
						 static_cast<uint32_t>(center.y),
						 static_cast<uint32_t>(center.z));
	};

	glm::vec3 blocksOffset = world::World::chunkToBlockPosition(position);
	const Chunk& chunk = getCentralChunk();

	for (int32_t y = 0; y < world::Chunk::SIZE; ++y) {
		for (int32_t z = 0; z < world::Chunk::SIZE; ++z) {
			for (int32_t x = 0; x < world::Chunk::SIZE; ++x) {
				if (dynamic_cast<const block::Air*>(&chunk.blockAt(x, y, z))) {
					continue;
				}

				glm::vec blockCenter = blocksOffset + glm::vec3(x, y, z);
				auto neighborhood = getBlockNeighborhood(x, y, z);

				auto [vertices, texCoords] = SimpleBlockRenderer::getRenderData(blockCenter, neighborhood);
				std::move(vertices.begin(), vertices.end(), std::back_inserter(vertexBuffer));
				std::move(texCoords.begin(), texCoords.end(), std::back_inserter(textureCoordinatesBuffer));
			}
		}
	}

	vertexBuffer.shrink_to_fit();
	textureCoordinatesBuffer.shrink_to_fit();

	auto mesh = std::make_unique<VAO>();
	mesh->attach({ vertexBuffer, 3 })
		 .attach({ textureCoordinatesBuffer, 2 });

	return mesh;
}
