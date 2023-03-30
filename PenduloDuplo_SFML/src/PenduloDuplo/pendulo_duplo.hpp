#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <tuple>
#include <vector>

#include <Particles/particles.hpp>

constexpr int width{1300}, height{1080};
constexpr float fps{300.0f};
constexpr float pi{3.14159265358979323846F};

class PenduloDuplo : public sf::Sprite {
  private:
    static constexpr int trace_size{250};
    static constexpr float g{9.81f};
    static constexpr float dt{1.0f / fps};

    float alpha1{}, alpha2{};
    float pos_x2{}, pos_y2{};
    float w1{}, w2{}, O1{}, O2{};
    float m1{}, m2{}, l1{}, l2{};
    float x1{}, x2{}, y1{}, y2{};

    bool show_length{true};

    sf::RenderTexture texture;
    sf::VertexBuffer ver_buffer;
    sf::CircleShape base, mass1, mass2;
    sf::Vertex length_vertices[3];
    std::vector<sf::Vertex> traces;

    void updateXY();

  public:
    sf::Vector2f end_pos1{}, end_pos2{};

    void setupRenderObjects();
    void update();
    void render();

    PenduloDuplo(float, float, float, float, float, float);
};
