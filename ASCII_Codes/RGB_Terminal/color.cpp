#include "color.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image_resize.h>

int Color::find_ansi_rgb(int r, int g, int b) {
    int index = 0;
    int dr = r - table_rgb[index][0];
    int dg = g - table_rgb[index][1];
    int db = b - table_rgb[index][2];
    int d = dr * dr + dg * dg + db * db;
    for (int i = 0; i < 256; ++i) {
        dr = r - table_rgb[i][0];
        dg = g - table_rgb[i][1];
        db = b - table_rgb[i][2];
        int dd = dr * dr + dg * dg + db * db;
        if (dd < d) {
            index = i;
            d = dd;
        }
    }
    return index;
}

int Color::distance_hsl(int i, int h, int s, int l) {
    int dh = h - table_hsl[i][0];
    int ds = s - table_hsl[i][1];
    int dl = l - table_hsl[i][2];
    return dh * dh + ds * ds + dl * dl;
}

int Color::find_ansi_hsl(int h, int s, int l) {
    int index = 0;

    for (int i = 0; i < 256; i++) {
        if (distance_hsl(i, h, s, l) < distance_hsl(index, h, s, l)) {
            index = i;
        }
    }
    return index;
}

void Color::rgb_to_hsl(int r, int g, int b, int *h, int *s, int *l) {
    float r_ = r / 255.0f;
    float g_ = g / 255.0f;
    float b_ = b / 255.0f;

    float epsilon = 1e-6;
    float cmax = r_;

    if (g_ > cmax) {
        cmax = g_;
    }
    if (b_ > cmax) {
        cmax = b_;
    }

    float cmin = r_;
    if (g_ < cmin) {
        cmin = g_;
    }
    if (b_ < cmin) {
        cmin = b_;
    }

    float delta = cmax - cmin;
    // H
    float hf = 0;
    if (delta < epsilon) {
        hf = 0;
    } else if (cmax == r_) {
        hf = 60 * fmodf((g_ - b_) / delta, 6.0f);
    } else if (cmax == g_) {
        hf = 60 * ((b_ - r_) / delta + 2);
    } else if (cmax == b_) {
        hf = 60 * ((r_ - g_) / delta + 4);
    } else {
        assert(0 && "Inacessivel");
    }
    // S
    float lf = (cmax + cmin) / 2.0f; // L
    float sf = 0;
    if (delta < epsilon) {
        sf = 0.0;
    } else {
        sf = delta / (1 - fabsf(2 * lf - 1));
    }

    *h = fmodf(fmodf(hf, 360.0f) + 360.0f, 360.0f);
    *s = (sf * 100.0f);
    *l = (lf * 100.0f);
}

void Color::run_color() {
    for (int r{0}; r < 5; ++r) {
        for (int g{0}; g < 5; ++g) {
            for (int b{0}; b < 5; ++b) {
                std::cout << "\e[48;5;"
                          << find_ansi_rgb(255 * r / 5, 255 * g / 5,
                                           255 * b / 5)
                          << "m  ";
            }
            std::cout << "\e[0m" << '\n';
        }
    }

    for (int r{0}; r < 5; ++r) {
        for (int g{0}; g < 5; ++g) {
            for (int b{0}; b < 5; ++b) {
                int h, s, l;
                rgb_to_hsl(r, g, b, &h, &s, &l);
                std::cout << "\e[48;5;" << find_ansi_hsl(h, s, l) << "m  ";
            }
            std::cout << "\e[0m" << '\n';
        }
    }
}

void Color::run_image(int argc, char *argv[]) {
    int width, height;

    if (argc < 2) {
        fprintf(stderr, "Error: Nenhuma entrada foi inserida!!");
        exit(1);
    }

    const char *filename = argv[1];

    uint32_t *pixels =
        (uint32_t *)stbi_load(filename, &width, &height, NULL, 4);

    if (pixels == NULL) {
        fprintf(stderr, "Error: Não foi possível ler o arquivo %s\n", filename);
        exit(1);
    }

    int resize_width = 128;
    int resize_height = height * resize_width / width;
    uint32_t *resize_pixels = static_cast<uint32_t *>(
        malloc(sizeof(uint32_t) * resize_width * resize_height));
    assert(resize_pixels != NULL);

    stbir_resize_uint8(reinterpret_cast<unsigned char *>(pixels), width, height,
                       sizeof(uint32_t) * width,
                       reinterpret_cast<unsigned char *>(resize_pixels),
                       resize_width, resize_height,
                       sizeof(uint32_t) * resize_width, 4);

    for (int i{0}; i < 256; ++i) {
        int r = table_rgb[i][0];
        int g = table_rgb[i][1];
        int b = table_rgb[i][2];
        int h = table_hsl[i][0];
        int s = table_hsl[i][1];
        int l = table_hsl[i][2];
        rgb_to_hsl(r, g, b, &h, &s, &l);
    }

    for (int y{0}; y < resize_height; y++) {
        for (int x{0}; x < resize_width; x++) {
            uint32_t pixel = resize_pixels[y * resize_width + x];
            int r = (pixel >> 8 * 0) & 0xFF;
            int g = (pixel >> 8 * 1) & 0xFF;
            int b = (pixel >> 8 * 2) & 0xFF;
            int a = (pixel >> 8 * 3) & 0xFF;
            r = a * r / 255;
            g = a * g / 255;
            b = a * b / 255;
            int h, s, l;
            rgb_to_hsl(r, g, b, &h, &s, &l);
            std::cout << "\e[48;5;" << find_ansi_hsl(h, s, l) << "m  ";
        }
        std::cout << "\e[0m" << '\n';
    }
}
