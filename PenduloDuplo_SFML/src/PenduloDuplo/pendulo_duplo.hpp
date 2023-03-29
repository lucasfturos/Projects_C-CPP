#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "Particles/particles.hpp"

constexpr int width{1000}, height{1000};
constexpr float fps{60.0f};
constexpr float pi{3.14159265358979323846F};

class PenduloDuplo : public sf::Sprite {
  private:
    static constexpr int trace_size{150};
    static constexpr float g{9.81f};
    static constexpr float dt{1.0f / fps};

    float w1{}, w2{}, O1{}, O2{};
    float m1{}, m2{}, l1{}, l2{};
    float x1{}, x2{}, y1{}, y2{};
    float alpha1{}, alpha2{};

    bool show_length{true};

    sf::RenderTexture texture;
    sf::VertexBuffer ver_buffer;
    sf::CircleShape mass1, mass2;
    sf::Vertex length_verteces[3];
    std::vector<sf::Vertex> traces;

    void updateXY();

  public:
    PenduloDuplo(float, float, float, float, float, float);

    void setupRenderObjects();
    void update();
    void render();
};
