#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

color image_texture::value(double u, double v, const vec3 &p) const {
    // Se não tivermos dados de textura, retorna uma cor ciano sólido como
    // um auxílio de depuração.
    if (data == nullptr) {
        return color(0, 1, 1);
    }

    // Define as coordenadas da textura de entrada para [0,1] x [1,0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0); // Flip V to image coordinates

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    // Mapeamento de número inteiro de fixação(clamp), pois as coordenadas
    // reais devem ser menores que 1.0
    if (i >= width) {
        i = width - 1;
    }

    if (j >= height) {
        j = height - 1;
    }

    const auto color_scale{1.0 / 255.0};
    auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

    return color(color_scale * pixel[0], color_scale * pixel[1],
                 color_scale * pixel[2]);
}

image_texture::image_texture(const char *filename) {
    auto components_per_pixel = bytes_per_pixel;

    data = stbi_load(filename, &width, &height, &components_per_pixel,
                     components_per_pixel);

    if (data == NULL) {
        std::cerr << "ERROR: Não foi possível carregar o arquivo da textura '"
                  << filename << "'.\n";
        width = height = 0;
    }
    bytes_per_scanline = bytes_per_pixel * width;
}

image_texture::~image_texture() { STBI_FREE(data); }
