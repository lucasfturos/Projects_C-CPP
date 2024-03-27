#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "../Constante/constante.hpp"

using namespace Constantes;

class PenduloDuplo {
  private:
    // Constantes
    static constexpr int trace_size = 150;
    static constexpr float g = 9.81f;
    static constexpr float dt = 1.0f / fps;

  private:
    // Variáveis de inicialização no construtor
    float m_l1, m_l2;
    float m_m1, m_m2;
    float m_O1, m_O2;
    float alpha1, alpha2;
    float w1, w2;

    bool paused;
    bool show_length;

    std::vector<sf::Vertex> length_vertices;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;

  private:
    // Variáveis privadas
    float frame_start;
    float accumulator;
    float current_time;
    float x1, x2;
    float y1, y2;
    float pos_x2, pos_y2;
    float half_width, half_height;

    std::size_t traces_size;

    // Variáveis da biblioteca
    sf::Clock clock;
    sf::VertexBuffer vertex_buffer;
    std::vector<sf::Vertex> traces;
    sf::CircleShape base, mass1, mass2;
    sf::Vector2f end_pos1, end_pos2;
    sf::Color start_color = sf::Color::Magenta;
    sf::Color end_color = sf::Color::Cyan;

    // Funções
    void update();
    void render();
    void updateXY();
    void togglePause();
    void setupRenderObjects();

  public:
    void run();

    PenduloDuplo(float l1, float l2, float m1, float m2, float O1, float O2);
};
