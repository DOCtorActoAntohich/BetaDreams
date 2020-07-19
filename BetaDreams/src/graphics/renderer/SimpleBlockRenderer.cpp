// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SimpleBlockRenderer.h"

#include "block/Blocks.h"
#include "utility/Directions.h"

using namespace beta::graphics::renderer;

SimpleBlockRenderer::BlockRenderData SimpleBlockRenderer::getRenderData(const glm::vec3& position, const BlockNeighborhood& blocks) {
	using namespace block;
	using namespace beta::utility::direction;
	
	static constexpr glm::vec3 center = { 1, 1, 1 };

	auto getCentralBlock = [&]() {
		return blocks.at(static_cast<uint32_t>(center.x),
						 static_cast<uint32_t>(center.y),
						 static_cast<uint32_t>(center.z));
	};

	if (dynamic_cast<const block::Air*>(getCentralBlock())) {
		return { {}, {} };
	}

	std::vector<float_t> vertices;
	std::vector<float_t> textureCoordinates;

	

	static auto canRenderSide = [&](const glm::vec3& neighborOffset, uint32_t blockedSide) -> bool {
		auto pos = center + neighborOffset;
		uint32_t	x = static_cast<uint32_t>(pos.x),
					y = static_cast<uint32_t>(pos.y),
					z = static_cast<uint32_t>(pos.z);

		if (blocks.at(x, y, z) == nullptr) {
			return true;
		}

		const Block& block = *blocks.at(x, y, z);
		return block.isTransparent() || !block.doesBlockSide(blockedSide);
	};


	static auto addVertexData = [&](const glm::vec3& vertexOffset, const glm::vec2& texCoords) {
		auto vertex = position + Block::HALF_SIZE * vertexOffset;

		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);

		textureCoordinates.push_back(texCoords.x);
		textureCoordinates.push_back(texCoords.y);
	};
	


	if (canRenderSide(NORTH, BlockedSide::NORTH)) {
		addVertexData(NORTH_EAST_UP,   { 0, 0 });
		addVertexData(NORTH_EAST_DOWN, { 0, 1 });
		addVertexData(NORTH_WEST_DOWN, { 1, 1 });

		addVertexData(NORTH_EAST_UP,   { 0, 0 });
		addVertexData(NORTH_WEST_DOWN, { 1, 1 });
		addVertexData(NORTH_WEST_UP,   { 1, 0 });
	}
	if (canRenderSide(SOUTH, BlockedSide::SOUTH)) {
		addVertexData(SOUTH_WEST_UP, { 0, 0 });
		addVertexData(SOUTH_WEST_DOWN, { 0, 1 });
		addVertexData(SOUTH_EAST_DOWN, { 1, 1 });

		addVertexData(SOUTH_WEST_UP, { 0, 0 });
		addVertexData(SOUTH_EAST_DOWN, { 1, 1 });
		addVertexData(SOUTH_EAST_UP, { 1, 0 });
	}

	if (canRenderSide(WEST, BlockedSide::WEST)) {
		addVertexData(NORTH_WEST_UP, { 0, 0 });
		addVertexData(NORTH_WEST_DOWN, { 0, 1 });
		addVertexData(SOUTH_WEST_DOWN, { 1, 1 });

		addVertexData(NORTH_WEST_UP, { 0, 0 });
		addVertexData(SOUTH_WEST_DOWN, { 1, 1 });
		addVertexData(SOUTH_WEST_UP, { 1, 0 });
	}
	if (canRenderSide(EAST, BlockedSide::EAST)) {
		addVertexData(SOUTH_EAST_UP, { 0, 0 });
		addVertexData(SOUTH_EAST_DOWN, { 0, 1 });
		addVertexData(NORTH_EAST_DOWN, { 1, 1 });

		addVertexData(SOUTH_EAST_UP, { 0, 0 });
		addVertexData(NORTH_EAST_DOWN, { 1, 1 });
		addVertexData(NORTH_EAST_UP, { 1, 0 });
	}

	if (canRenderSide(UP, BlockedSide::UP)) {
		addVertexData(NORTH_WEST_UP, { 0, 0 });
		addVertexData(SOUTH_WEST_UP, { 0, 1 });
		addVertexData(SOUTH_EAST_UP, { 1, 1 });

		addVertexData(NORTH_WEST_UP, { 0, 0 });
		addVertexData(SOUTH_EAST_UP, { 1, 1 });
		addVertexData(NORTH_EAST_UP, { 1, 0 });
	}
	if (canRenderSide(DOWN, BlockedSide::DOWN)) {
		addVertexData(NORTH_EAST_DOWN, { 0, 0 });
		addVertexData(SOUTH_EAST_DOWN, { 0, 1 });
		addVertexData(SOUTH_WEST_DOWN, { 1, 1 });

		addVertexData(NORTH_EAST_DOWN, { 0, 0 });
		addVertexData(SOUTH_WEST_DOWN, { 1, 1 });
		addVertexData(NORTH_WEST_DOWN, { 1, 0 });
	}

	return { vertices, textureCoordinates };
}