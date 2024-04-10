#pragma once

#include "../Vec3/vec3.hpp"
#include <vector>

class Torus {
  private:
    std::vector<int> indices;
    std::vector<vec3d> vertices;

    void generateIndices();
    void generateVertices();

  public:
    double innerRadius;
    double outterRadius;
    int slices;

    Torus(double innerRadius, double outterRadius, int slices);

    ObjectSource Sources();
};