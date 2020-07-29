// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_VAO_H_INCLUDED
#define BETA_GRAPHICS_VAO_H_INCLUDED

#include "engine/VBO.h"

namespace beta::engine {
	class VAO {
	public:
		VAO();
		VAO(const VAO& copy) = delete;
		VAO(VAO&& other) noexcept;
		~VAO() noexcept;

		void bind() noexcept;
		void unbind() noexcept;
		bool isBound() const noexcept;

		VAO& attach(VBO&& vbo);

		void draw();

		VAO& operator=(VAO&& other) noexcept;
	private:
		uint32_t m_id;
		std::vector<VBO> m_vbos;

		uint32_t m_objects;

		bool m_isBound;
	};
}

#endif // !BETA_GRAPHICS_VAO_H_INCLUDED
