// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_WORLD_WORLD_H_INCLUDED
#define BETA_WORLD_WORLD_H_INCLUDED

#include <unordered_map>
#include <glm/vec3.hpp>

#include "graphics/VAO.h"
#include "world/Chunk.h"
#include "utility/Types.h"

namespace beta::world {
	class World {
	public:
		void addEmptyChunk(const glm::vec3& position);
		void moveChunk(const glm::vec3& position, Chunk& chunk);
		const Chunk& getChunk(const glm::vec3& position) const;
		void deleteChunk(const glm::vec3& position);

		Block& blockAt(const glm::vec3& position);
		const Block& blockAt(const glm::vec3& position) const;

		void draw() const;

		static glm::vec3 chunkToBlockPosition(const glm::vec3& chunkCenter);
		static glm::vec3 blockToChunkPosition(const glm::vec3& blockCenter);
	private:
		static bool isValidPos(const glm::vec3& position);

		void renderChunk(const glm::vec3& position);

		std::unordered_map<glm::vec3, Chunk, HashVec3f> m_chunks;
		std::unordered_map<glm::vec3, std::unique_ptr<graphics::VAO>, HashVec3f> m_chunkMeshes;
	};
}

#endif // !BETA_WORLD_WORLD_H_INCLUDED