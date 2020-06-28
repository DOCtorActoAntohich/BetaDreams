// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_CHUNK_RENDERER_H_INCLUDED
#define BETA_GRAPHICS_CHUNK_RENDERER_H_INCLUDED

#include <memory>
#include <glm/vec3.hpp>

#include "graphics/VAO.h"
#include "world/Chunk.h"

namespace beta::graphics {
	class ChunkRenderer {
	public:
		ChunkRenderer();

		std::unique_ptr<VAO> makeMesh(const glm::vec3& position, const world::Chunk& chunk);
	private:
		std::vector<float_t> m_vertexBuffer;
		std::vector<float_t> m_textureCoordinatesBuffer;
	};
}

#endif // !BETA_GRAPHICS_CHUNK_RENDERER_H_INCLUDED
