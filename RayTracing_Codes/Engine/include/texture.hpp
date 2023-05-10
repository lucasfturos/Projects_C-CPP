#pragma once

#include "constante.hpp"
#include "perlin.hpp"
#include "vec3.hpp"

class texture {
  public:
    virtual color value(double u, double v, const point3 &p) const = 0;
};

class solid_color : public texture {
  public:
    solid_color() {}
    solid_color(color c) : color_value(c) {}

    solid_color(double red, double green, double blue)
        : solid_color(color(red, green, blue)) {}

    virtual color value(double u, double v, const vec3 &p) const override {
        return color_value;
    }

  private:
    color color_value;
};

class checker_texture : public texture {
  public:
    checker_texture() {}
    checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd)
        : even(_even), odd(_odd) {}

    checker_texture(color c1, color c2)
        : even(make_shared<solid_color>(c1)),
          odd(make_shared<solid_color>(c2)) {}

    virtual color value(double u, double v, const point3 &p) const override {
        auto sines{sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z())};
        if (sines < 0) {
            return odd->value(u, v, p);
        } else {
            return even->value(u, v, p);
        }
    }

  public:
    shared_ptr<texture> even;
    shared_ptr<texture> odd;
};

class noise_texture : public texture {
  public:
    noise_texture() {}
    noise_texture(double sc) : scale(sc) {}

    virtual color value(double u, double v, const point3 &p) const override {
        // Textura de Perlin - Interpolação usando vetores aleatórios nos pontos
        // da grade
        // return color(1, 1, 1) * 0.5 * (1.0 + noise.noise(scale *  p));

        // Textura de Perlin - Turbulência
        // return color(1, 1, 1) * noise.turb(scale * p);

        // Textura de Perlin - Turbulência com ajuste da fase
        return color(1, 1, 1) * 0.5 *
               (1 + sin(scale * p.z() + 10 * noise.turb(p)));
    }

  public:
    perlin noise;
    double scale;
};

/* Futuramente vou arrumar
class image_texture : public texture {
  public:
    const static int bytes_per_pixel{3};

    image_texture()
        : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

    image_texture(const char *filename) {
        auto components_per_pixel{bytes_per_pixel};

        data = stbi_load(filename, &width, &height, &components_per_pixel,
                         components_per_pixel);
        if (!data) {
            std::cerr
                << "ERROR: Não foi possível carregar o arquivo da textura '"
                << filename << "'.\n";
            width = height = 0;
        }
        bytes_per_scanline = bytes_per_pixel * width;
    }

    ~image_texture() { delete data; }

    virtual color value(double u, double v, const vec3 &p) const override {
        // Se não tivermos dados de textura, retorna uma cor ciano sólido como
        // um auxílio de depuração.
        if (data == nullptr) {
            return color(0, 1, 1);
        }

        // Define as coordenadas da textura de entrada para [0,1] x [1,0]
        u = clamp(u, 0.0, 1.0);
        v = 1.0 - clamp(v, 0.0, 1.0); // Flip V to image coordinates

        auto i{static_cast<int>(u * width)};
        auto j{static_cast<int>(v * height)};

        // Mapeamento de número inteiro de fixação(clamp), pois as coordenadas
        // reais devem ser menores que 1.0
        if (i >= width) {
            i = width - 1;
        }

        if (j >= height) {
            j = height - 1;
        }

        const auto color_scale{1.0 / 255.0};
        auto pixel{data + j * bytes_per_scanline + i * bytes_per_pixel};

        return color(color_scale * pixel[0], color_scale * pixel[1],
                     color_scale * pixel[2]);
    }

  private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;
};
*/
