// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_TEXTURE_ATLAS_H_INCLUDED
#define BETA_GRAPHICS_TEXTURE_ATLAS_H_INCLUDED

#include <cstdint>

#pragma warning(push, 0)
#pragma warning( disable : 26812 6289)
#include <png++/png.hpp>
#pragma warning(pop)

#include "Types.h"

namespace beta::graphics {
	class TextureAtlas {
	public:
		TextureAtlas(uint32_t x, uint32_t y);

		std::pair<uint32_t, uint32_t> add(const png::image<png::rgba_pixel>& texture);

		const png::image<png::rgba_pixel>& getResult() const noexcept;
	private:
		void sortSpots() noexcept;

		png::image<png::rgba_pixel> m_finalImage;
		std::vector<Rectangle> m_freeSpots;
		DynamicArray2<bool> m_filledPixels;
	};
}

#endif // !BETA_GRAPHICS_TEXTURE_ATLAS_H_INCLUDED