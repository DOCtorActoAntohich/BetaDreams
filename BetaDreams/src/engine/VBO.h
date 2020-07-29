// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_VBO_H_INCLUDED
#define BETA_GRAPHICS_VBO_H_INCLUDED

#include <vector>

namespace beta::engine {
	class VBO {
	public:
		VBO();
		VBO(const std::vector<float_t>& data, uint32_t objectComponents);
		VBO(const VBO& copy) = delete;
		VBO(VBO&& other) noexcept;
		~VBO() noexcept;

		void bind() noexcept;
		void unbind() noexcept;
		bool isBound() const noexcept;

		uint32_t objectComponents() const noexcept;
		uint32_t objects() const noexcept;

		void setData(const std::vector<float_t>& data, uint32_t objectComponents);

		VBO& operator=(const VBO& copy) = delete;
		VBO& operator=(VBO&& other) noexcept;
		
	private:
		uint32_t m_id;

		std::vector<float_t> m_data;
		uint32_t m_objectComponents;

		bool m_isBound;
	};
}

#endif // !BETA_GRAPHICS_VBO_H_INCLUDED
