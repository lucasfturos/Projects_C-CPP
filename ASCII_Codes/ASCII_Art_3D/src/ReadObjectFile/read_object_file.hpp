#pragma once

#include "../Vec3/vec3.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ReadObjectFile {
  private:
    std::vector<int> faces;
    std::vector<point3d> vertices;

    void reset();
    void parseLine(const std::string &line);
    void loadFile(const std::string &filePath);

  public:
    ReadObjectFile(const std::string &filePath);

    ObjectSource Sources();
};