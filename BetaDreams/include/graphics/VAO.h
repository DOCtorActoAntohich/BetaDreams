// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_GRAPHICS_VAO_H
#define _BETA_GRAPHICS_VAO_H

#include "graphics/VBO.h"

namespace beta::graphics {
	class VAO {
	public:
		VAO();
		VAO(const VAO& copy) = delete;
		~VAO() noexcept;

		void bind() noexcept;
		void unbind() noexcept;
		bool isBound() const noexcept;

		VAO& attach(VBO&& vbo);

		void draw();
	private:
		uint32_t m_id;
		std::vector<VBO> m_vbos;

		uint32_t m_objects;

		bool m_isBound;
	};
}

#endif // !_BETA_GRAPHICS_VAO_H
