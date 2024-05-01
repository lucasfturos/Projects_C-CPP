#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

using std::shared_ptr;

const float pi = M_PI;

class Render {
  private:
    const int WIDTH = 1080;
    const int HEIGHT = 720;
    const int SLIDER_WIDTH = 200;
    const int SLIDER_HEIGHT = 15;
    const int SLIDER_MAX_VALUE = SLIDER_HEIGHT;

    int depth;
    int sliderValue;
    bool isDragging;

  private:
    shared_ptr<sf::RenderWindow> window;
    shared_ptr<sf::VideoMode> desktop;

    sf::RectangleShape sliderBar;
    sf::RectangleShape sliderObject;

  private:
    void draw();
    void handleEvents();
    void initializeSlider();
    void updateSliderPosition();
    void drawTree(int n, float x1, float y1, float x2, float y2, float angle);

  public:
    void run();
    Render();
};
