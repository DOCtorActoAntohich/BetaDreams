// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_GRAPHICS_TEXTURE_H
#define _BETA_GRAPHICS_TEXTURE_H

#include <string>

#include "exception/BetaException.h"

namespace beta::graphics {
	class Texture {
	public:
		Texture();
		Texture(const std::string& filename);
		Texture(Texture& copy) = delete;
		Texture(Texture&& other) noexcept;
		~Texture();

		uint32_t id() const noexcept;
		uint32_t width() const noexcept;
		uint32_t height() const noexcept;

		void bind();

		Texture& operator=(Texture& copy) = delete;
		Texture& operator=(Texture&& other) noexcept;
	private:
		uint32_t m_id;

		uint32_t m_width;
		uint32_t m_height;
	};


	class PngLoadException : public BetaException {
	public:
		PngLoadException(std::string message);
	};

	extern double_t getDisplayExponent();
	extern int32_t _png_load(const std::string& file, uint32_t& width, uint32_t& height);
}

#endif // !_BETA_GRAPHICS_TEXTURE_H
