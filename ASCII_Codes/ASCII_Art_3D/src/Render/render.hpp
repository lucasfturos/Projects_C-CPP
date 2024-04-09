#pragma once

#include "../Point/point.hpp"
#include "../ReadObjectFile/read_object_file.hpp"
// #include "../Torus/torus.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

class Render {
  private:
    // Initialize in constructor
    const int WIDTH = 158; // Max Width 158
    const int HEIGHT = 60;

    std::vector<std::vector<std::string>> camp;

    std::shared_ptr<point3d> p;
    std::shared_ptr<ReadObjectFile> read_object;
    // std::shared_ptr<Torus> torus;

    ObjectSource sources;

    double distance;
    double alpha, beta, theta;

  private:
    void update();
    void clear();
    void draw();

  public:
    Render();
    void run();
};
