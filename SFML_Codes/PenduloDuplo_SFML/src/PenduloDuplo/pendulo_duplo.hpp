#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "../Constante/constante.hpp"

using namespace Constantes;

class PenduloDuplo {
  private:
    static constexpr int trace_size = 150;
    static constexpr float g = 9.81f;
    static constexpr float dt = 1.0f / fps;

    int trace1_s, trace2_s;

    sf::Clock clock;

    float frame_start;
    float accumulator;
    float current_time;
    float w1, w2;
    float x1, x2;
    float y1, y2;
    float m_O1, m_O2;
    float m_m1, m_m2;
    float m_l1, m_l2;
    float alpha1, alpha2;
    float pos_x2, pos_y2;
    float half_width, half_height;

    bool show_length = true;

    sf::Color color_trace;
    sf::VertexBuffer vertex_buffer;
    std::vector<sf::Vertex> length_vertices;
    std::vector<sf::Vertex> traces1, traces2;
    sf::CircleShape base, mass1, mass2;
    sf::Vector2f end_pos1, end_pos2;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;

    void updateXY();

  public:
    void setupRenderObjects();
    void update();
    void render();
    void run();

    PenduloDuplo(float, float, float, float, float, float);
};
