// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TextureAtlas.h"

#include <deque>

using namespace beta::graphics;

TextureAtlas::TextureAtlas(uint32_t x, uint32_t y) : m_finalImage(x, y), m_filledPixels(x, y) {
	m_freeSpots.emplace_back(0, 0, x, y);
}

std::pair<uint32_t, uint32_t> TextureAtlas::add(const png::image<png::rgba_pixel>& texture) {
	static auto fill = [&](const Rectangle& textureRect) -> void {
		for (uint32_t y = textureRect.y; y < textureRect.y + textureRect.h; ++y) {
			for (uint32_t x = textureRect.x; x < textureRect.x + textureRect.w; ++x) {
				auto pixel = texture.get_pixel(x - textureRect.x, y - textureRect.y);
				m_finalImage.set_pixel(x, y, pixel);
				m_filledPixels.at(x, y) = true;
			}
		}
	};

	static auto shiftToUpperLeft = [&](uint32_t xstart, uint32_t ystart) {
		uint32_t x = xstart, y = ystart;
		while (true) {
			bool moved = false;
			if (x != 0 && !m_filledPixels.at(x - 1, y)) {
				--x;
				moved = true;
			}
			if (y != 0 && !m_filledPixels.at(x, y - 1)) {
				--y;
				moved = true;
			}

			if (!moved) {
				break;
			}
		}
		return std::make_pair(x, y);
	};

	static auto isIn = [&](uint32_t x, uint32_t y) -> bool {
		return x < m_finalImage.get_width() && y < m_finalImage.get_height();
	};

	static auto findFreeRect = [&](uint32_t xstart, uint32_t ystart) -> Rectangle {
		uint32_t yborder = m_finalImage.get_height();
		for (uint32_t y = ystart; y < yborder; ++y) {
			if (isIn(xstart, y + 1) && m_filledPixels.at(xstart, y + 1)) {
				yborder = y + 1;
			}
		}

		uint32_t xborder = m_finalImage.get_width();
		for (uint32_t x = xstart; x < xborder; ++x) {
			if (isIn(x + 1, ystart) && m_filledPixels.at(x + 1, ystart)) {
				xborder = x + 1;
			}
		}

		return { static_cast<int32_t>(xstart), static_cast<int32_t>(ystart), xborder - xstart, yborder - ystart };
	};

	static auto addFreeSpotFrom = [&](uint32_t x, uint32_t y) -> void {
		if (isIn(x, y)) {
			auto [xnew, ynew] = shiftToUpperLeft(x, y);
			auto freeSpot = findFreeRect(xnew, ynew);
			if (std::find(m_freeSpots.begin(), m_freeSpots.end(), freeSpot) == m_freeSpots.end()) {
				m_freeSpots.push_back(freeSpot);
			}
		}
	};


	Rectangle freeSpot;
	for (auto it = m_freeSpots.begin(); it != m_freeSpots.end(); ++it) {
		auto& spot = *it;
		if (spot.w >= texture.get_width() && spot.h >= texture.get_height()) {
			freeSpot = spot;
			m_freeSpots.erase(it);
			break;
		}
	}

	if (freeSpot.isEmpty()) {
		throw std::domain_error("Can't add texture to the atlas");
	}


	Rectangle textureRect = { freeSpot.x, freeSpot.y, texture.get_width(), texture.get_height() };
	fill(textureRect);

	uint32_t xdown = textureRect.x, ydown = textureRect.y + textureRect.h;
	uint32_t xright = textureRect.x + textureRect.w, yright = textureRect.y;

	addFreeSpotFrom(xdown, ydown);
	addFreeSpotFrom(xright, yright);

	this->sortSpots();

	return { freeSpot.x, freeSpot.y };
}



const png::image<png::rgba_pixel>& TextureAtlas::getResult() const noexcept {
	return m_finalImage;
}



void TextureAtlas::sortSpots() noexcept {
	static auto lessThan = [](Rectangle l, Rectangle r) -> bool {
		return l.y < r.y && l.x < r.x;
	};

	std::stable_sort(m_freeSpots.begin(), m_freeSpots.end(), lessThan);
}