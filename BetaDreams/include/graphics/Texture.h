#ifndef _BETA_GRAPHICS_TEXTURE_H
#define _BETA_GRAPHICS_TEXTURE_H

#include <string>

namespace beta::graphics {
	class Texture {
	public:
		Texture(uint32_t id, uint32_t width, uint32_t height);
		~Texture();

		void bind();

		static Texture* load(std::string file);
	private:
		uint32_t m_id;

		uint32_t m_width;
		uint32_t m_height;
	};


	extern int32_t _png_load(std::string file, uint32_t& width, uint32_t& height);
}

#endif // !_BETA_GRAPHICS_TEXTURE_H
