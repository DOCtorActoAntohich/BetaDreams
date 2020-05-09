#include "graphics/Texture.h"

#include <iostream>

#include <GL/glew.h>
#include <png.h>

#include "exception/Exceptions.hpp"

using namespace beta::graphics;



Texture::Texture(uint32_t id, uint32_t width, uint32_t height) {
	m_id = id;

    m_width = width;
    m_height = height;
}



Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}



void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}


int32_t beta::graphics::_png_load(std::string filename, uint32_t& width_out, uint32_t& height_out) {
    using beta::PngLoadException;

    // Open file.
    FILE* file;
    fopen_s(&file, filename.c_str(), "rb");
    if (file == nullptr) {
        throw PngLoadException("Cannot open file: " + filename);
    }

    // Check PNG signature.
    const int32_t HEADER_SIZE = 8;
    png_byte header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, file);
    int32_t is_png = png_sig_cmp(header, 0, HEADER_SIZE);
    if (is_png != 0) {
        fclose(file);
        throw PngLoadException("The file does not have PNG signature: " + filename);
    }

    // Pre-initialize.
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == nullptr) {
        fclose(file);
        throw PngLoadException("Not enough memory to initialize PNG basic structure(s)");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr) {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(file);
        throw PngLoadException("Not enough memory to initialize PNG info structure(s)");
    }
    
    // Go here if somethging after it goes wrong.
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        throw PngLoadException("Error reading file info: " + filename);
    }

    // Read PNG info.
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, HEADER_SIZE);
    png_read_info(png_ptr, info_ptr);

    // Get attributes.
    width_out = png_get_image_width(png_ptr, info_ptr);
    height_out = png_get_image_height(png_ptr, info_ptr);

    int32_t color_type = png_get_color_type(png_ptr, info_ptr);
    int32_t bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    
    int32_t alpha;
    switch (color_type) {
    case PNG_COLOR_TYPE_RGBA:
        alpha = GL_RGBA;
        break;
    case PNG_COLOR_TYPE_RGB:
        alpha = GL_RGB;
        break;
    default:
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        throw PngLoadException("Unsupported color type: " + color_type);
    }




    double_t LUT_exponent;

#if defined(NeXT)
    LUT_exponent = 1.0 / 2.2;

#elif defined(sgi)
    LUT_exponent = 1.0 / 1.7;

    FILE* infile;
    fopen_s(&infile, "/etc/config/system.glGammaVal", "r");
    if (infile != nullptr) {
        const uint32_t BUFFER_MAX_SIZE = 80;
        char fooline[BUFFER_MAX_SIZE];
        fgets(fooline, BUFFER_MAX_SIZE, infile);
        fclose(infile);

        double_t sgi_gamma = atof(fooline);
        if (sgi_gamma > 0.0) {
            LUT_exponent = 1.0 / sgi_gamma;
        }
    }

#elif defined(Macintosh)
    LUT_exponent = 1.8 / 2.61;

#else
    // Assume no LUT (most PCs).
    LUT_exponent = 1.0;
#endif

    double_t CRT_exponent = 2.2;
    double_t display_exponent = LUT_exponent * CRT_exponent;







    // Expand PNG.
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png_ptr);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    }
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }

    // Shrink wide image data.
    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }
    // Expand gray to RGB.
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png_ptr);
    }

    double_t gamma;
    uint32_t gAMA_correctness = png_get_gAMA(png_ptr, info_ptr, &gamma);
    if (gAMA_correctness != 0) {
        png_set_gamma(png_ptr, display_exponent, gamma);
    }

    png_read_update_info(png_ptr, info_ptr);






    //int32_t channels = png_get_channels(png_ptr, info_ptr);
    uint32_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    png_bytep image_data = new png_byte[rowbytes * height_out];
    if (image_data == nullptr) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        return 0;
    }

    png_bytep* row_pointers = new png_bytep[height_out];
    if (row_pointers == nullptr) {
        delete[] image_data;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        return 0;
    }

    for (uint32_t i = 0; i < height_out; ++i) {
        //row_pointers[i] = image_data + i * rowbytes;
        row_pointers[height_out - 1 - i] = image_data + i * rowbytes;
    }
    
    png_read_image(png_ptr, row_pointers);

    png_read_end(png_ptr, NULL);

    // Reading finished here.



    


    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_out, height_out,
        0, alpha, GL_UNSIGNED_BYTE, static_cast<void*>(image_data));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    


    delete[] image_data;
    delete[] row_pointers;

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(file);

    return textureId;
}



Texture* Texture::load(std::string file) {
    uint32_t width = 0;
    uint32_t height = 0;

    try {
        GLuint textureId = beta::graphics::_png_load(file, width, height);
        if (textureId == 0) {
            std::cerr << "Could not load texture: " << file << std::endl;
            return nullptr;
        }
        return new Texture(textureId, width, height);
    }
    catch (PngLoadException ex) {
        std::cerr << ex.what() << std::endl;
        return nullptr;
    }
}
