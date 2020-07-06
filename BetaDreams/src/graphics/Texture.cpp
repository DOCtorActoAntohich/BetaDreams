// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Texture.h"

#include <iostream>

#include <GL/glew.h>
#include <png++/png.hpp>

#include "Log.h"

using namespace beta::graphics;


PngLoadException::PngLoadException(std::string message)
    : BetaException(message) {}



Texture::Texture()
    : m_id(0), m_width(0), m_height(0)
{}

Texture::Texture(const std::string& filename) : Texture() {
    this->load(filename);
}

Texture::Texture(Texture&& other) noexcept {
    *this = std::move(other);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}



void Texture::load(const std::string& filename) {
    // Unfortunately, png++ can't provide me with one-dimensional pixel buffer.
    static auto getOneDimBuffer = [](const png::image<png::rgba_pixel>& image) {
        std::vector<png::rgba_pixel> buffer;
        buffer.reserve(image.get_width() * image.get_height());
        for (uint32_t y = 0; y < image.get_height(); ++y) {
            for (uint32_t x = 0; x < image.get_width(); ++x) {
                buffer.emplace_back(image.get_pixel(x, y));
            }
        }
        return buffer;
    };

    png::image<png::rgba_pixel> image(filename);

    glGenTextures(1, &m_id);
    if (m_id == 0) {
        throw PngLoadException("Could not load texture: " + filename);
    }

    glBindTexture(GL_TEXTURE_2D, m_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    std::vector<png::rgba_pixel> buffer = std::move(getOneDimBuffer(image));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.get_width(), image.get_height(),
        0, GL_RGBA, GL_UNSIGNED_BYTE, static_cast<void*>(buffer.data()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    Log::debug("File loaded: {0}.", filename);
}



void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}



Texture& Texture::operator=(Texture&& other) noexcept {
    this->m_id = other.m_id;
    this->m_width = other.m_width;
    this->m_height = other.m_height;

    other.m_id = 0;
    other.m_width = 0;
    other.m_height = 0;

    return *this;
}



uint32_t Texture::id() const noexcept {
    return m_id;
}

uint32_t Texture::width() const noexcept {
    return m_width;
}

uint32_t Texture::height() const noexcept {
    return m_height;
}
