#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

constexpr int trace_size{100};
constexpr int dW{8}, dH{16};
constexpr int width{900}, height{900};

constexpr float g{9.81f};
constexpr float pi{3.14159265358979323846F};
constexpr float fps{60.0f};

class PenduloDuplo : public sf::Sprite {
  private:
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
    PenduloDuplo(float l1, float l2, float m1, float m2, float O1, float O2);

    void setupRenderObjects();
    void update();
    void render();
};
