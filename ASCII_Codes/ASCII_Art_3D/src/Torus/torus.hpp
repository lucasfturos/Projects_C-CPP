#pragma once

#include "../Point/point.hpp"
#include <vector>

class Torus {
  private:
    std::vector<int> indices;
    std::vector<point3d> vertices;

    void generateIndices();
    void generateVertices();

  public:
    double innerRadius;
    double outterRadius;
    int slices;

    Torus(double innerRadius, double outterRadius, int slices);

    ObjectSource Sources();
};