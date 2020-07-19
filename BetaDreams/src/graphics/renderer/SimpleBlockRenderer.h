// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_RENDERER_SIMPLE_BLOCK_RENDERER_H_INCLUDED
#define BETA_GRAPHICS_RENDERER_SIMPLE_BLOCK_RENDERER_H_INCLUDED

#include <vector>
#include <glm/vec3.hpp>

#include "block/Block.h"
#include "Types.h"

namespace beta::graphics::renderer {
	class SimpleBlockRenderer {
	public:
		using BlockNeighborhood = Array3<const block::Block*, 3, 3, 3>;
		using BlockRenderData = std::pair<std::vector<float_t>, std::vector<float_t>>;

		static BlockRenderData getRenderData(const glm::vec3& position, const BlockNeighborhood& blocks);
	private:
	};
}

#endif // !BETA_GRAPHICS_RENDERER_SIMPLE_BLOCK_RENDERER_H_INCLUDED