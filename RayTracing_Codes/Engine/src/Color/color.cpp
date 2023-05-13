#include "color.hpp"

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
