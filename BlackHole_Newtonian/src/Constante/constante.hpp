#pragma once

namespace Constantes {
constexpr int width{1300}, height{1080};
constexpr float fps{300.0f};
constexpr float pi{3.14159265358979323846F};
constexpr float M_SOL{1.989E30}; // Massa do Sol em quilograma
constexpr float mass_bh{M_SOL * 5};
constexpr float c{299792458.0f};
constexpr float G{6.6743E-11};
constexpr float radius{2 * G * mass_bh / (c * c)};
constexpr float F_Gravity{G * (mass_bh / (radius * radius))};
} // namespace Constantes
