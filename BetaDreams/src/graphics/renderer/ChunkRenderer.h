// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_RENDERER_CHUNK_RENDERER_H_INCLUDED
#define BETA_GRAPHICS_RENDERER_CHUNK_RENDERER_H_INCLUDED

#include <memory>
#include <glm/vec3.hpp>

#include "engine/VAO.h"
#include "world/Chunk.h"

#include <Types.h>

namespace beta::graphics::renderer {
	class ChunkRenderer {
	public:
		using ChunkNeighborhood = Array3<const world::Chunk*, 3, 3, 3>;
		static std::unique_ptr<engine::VAO> makeMesh(const glm::vec3& position, const ChunkNeighborhood& chunks);
	};
}

#endif // !BETA_GRAPHICS_RENDERER_CHUNK_RENDERER_H_INCLUDED
