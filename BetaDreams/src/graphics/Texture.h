// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_TEXTURE_H_INCLUDED
#define BETA_GRAPHICS_TEXTURE_H_INCLUDED

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

		void load(const std::string& filename);

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
}

#endif // !BETA_GRAPHICS_TEXTURE_H_INCLUDED
