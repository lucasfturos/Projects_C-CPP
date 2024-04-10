#include "torus.hpp"

Torus::Torus(double innerRadius, double outterRadius, int slices)
    : innerRadius(innerRadius), outterRadius(outterRadius), slices(slices) {
    generateIndices();
    generateVertices();
}

void Torus::generateIndices() {
    for (int i = 0; i < slices; ++i) {
        for (int j = 0; j < slices; ++j) {
            int p0 = i * (slices + 1) + j;
            int p1 = p0 + slices + 1;
            int p2 = p0 + 1;
            int p3 = p1 + 1;

            indices.push_back(p0);
            indices.push_back(p1);
            indices.push_back(p2);
            indices.push_back(p2);
            indices.push_back(p1);
            indices.push_back(p3);
        }
    }
}

void Torus::generateVertices() {
    for (int i = 0; i <= slices; ++i) {
        double u = (static_cast<double>(i) / slices) * 2 * M_PI;
        double cosU = cos(u);
        double sinU = sin(u);
        for (int j = 0; j <= slices; ++j) {
            double v = (static_cast<double>(j) / slices) * 2 * M_PI;
            double cosV = cos(v);
            double sinV = sin(v);

            double x = (outterRadius + innerRadius * cosV) * cosU;
            double y = (outterRadius + innerRadius * cosV) * sinU;
            double z = innerRadius * sinV;

            vertices.push_back(vec3d(x, y, z));
        }
    }
}

ObjectSource Torus::Sources() {
    return {
        .indices = indices,
        .vertices = vertices,
    };
}