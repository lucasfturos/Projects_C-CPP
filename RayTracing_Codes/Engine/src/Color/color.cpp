#include "color.hpp"

int Color::distance_hsl(int i, int h, int s, int l) {
    int dh{h - table_hsl[i][0]};
    int ds{s - table_hsl[i][1]};
    int dl{l - table_hsl[i][2]};
    return dh * dh + ds * ds + dl * dl;
}

int Color::find_ansi_hsl(int h, int s, int l) {
    int index{0};

    for (int i{}; i < 256; ++i) {
        if (distance_hsl(i, h, s, l) < distance_hsl(index, h, s, l)) {
            index = i;
        }
    }
    return index;
}

void Color::rgb_to_hsl(int r, int g, int b, int *h, int *s, int *l) {
    float r_{r / 255.0f};
    float g_{g / 255.0f};
    float b_{b / 255.0f};

    float epsilon{1e-6};
    float cmax{r_};

    if (g_ > cmax) {
        cmax = g_;
    }
    if (b_ > cmax) {
        cmax = b_;
    }

    float cmin{r_};
    if (g_ < cmin) {
        cmin = g_;
    }
    if (b_ < cmin) {
        cmin = b_;
    }

    float delta{cmax - cmin};

    // H
    float hf{0};
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

    float lf{(cmax + cmin) / 2.0f}; // L

    // S
    float sf{0};
    if (delta < epsilon) {
        sf = 0.0;
    } else {
        sf = delta / (1 - fabsf(2 * lf - 1));
    }

    *h = fmodf(fmodf(hf, 360.0f) + 360.0f, 360.0f);
    *s = (sf * 100.0f);
    *l = (lf * 100.0f);
}

void Color::run_color(std::ostream &out, color pixel_color,
                      int samples_per_pixel) {
    for (int i{0}; i < 256; ++i) {
        auto r{table_rgb[i][0]};
        auto g{table_rgb[i][1]};
        auto b{table_rgb[i][2]};
        // Divide a cor pelo número de amostras.
        auto scale{1.0 / samples_per_pixel};
        r *= scale;
        g *= scale;
        b *= scale;
        int h = table_hsl[i][0];
        int s = table_hsl[i][1];
        int l = table_hsl[i][2];
        rgb_to_hsl(r, g, b, &h, &s, &l);
    }

    auto r{pixel_color.x()};
    auto g{pixel_color.y()};
    auto b{pixel_color.z()};
    // Divide a cor pelo número de amostras.
    auto scale{1.0 / samples_per_pixel};
    r *= scale;
    g *= scale;
    b *= scale;

    int h, s, l;
    rgb_to_hsl(static_cast<int>(255 * clamp(r, 0.0, 0.999)),
               static_cast<int>(255 * clamp(g, 0.0, 0.999)),
               static_cast<int>(255 * clamp(b, 0.0, 0.999)), &h, &s, &l);
    out << "\e[48;5;" << find_ansi_hsl(h, s, l) << "m  ";
}

void Color::write_color(std::ostream &out, color pixel_color,
                        int samples_per_pixel) {
    auto r{pixel_color.x()};
    auto g{pixel_color.y()};
    auto b{pixel_color.z()};
    // Divide a cor pelo número de amostras.
    auto scale{1.0 / samples_per_pixel};
    r *= scale;
    g *= scale;
    b *= scale;
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(b, 0.0, 0.999)) << '\n';
}
