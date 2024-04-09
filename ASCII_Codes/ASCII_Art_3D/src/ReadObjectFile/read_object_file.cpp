#include "read_object_file.hpp"

ReadObjectFile::ReadObjectFile(const std::string &filePath) {
    loadFile(filePath);
}

void ReadObjectFile::reset() {
    faces.clear();
    vertices.clear();
}

void ReadObjectFile::parseLine(const std::string &line) {
    if (line.empty()) {
        return;
    }

    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "v") {
        point3d vertex;
        iss >> vertex.x >> vertex.y >> vertex.z;
        vertices.push_back(vertex);
    } else if (type == "f") {
        point3i face;
        char slash;
        if (line.find('/') != std::string::npos) {
            iss >> face.x >> slash >> face.y >> slash >> face.z;
        } else if (line.find("//") != std::string::npos) {
            iss >> face.x >> slash >> slash >> face.y >> slash >> slash >>
                face.z;
        } else {
            iss >> face.x >> face.y >> face.z;
            face.x--;
            face.y--;
            face.z--;
        }
        faces.push_back(face.x);
        faces.push_back(face.y);
        faces.push_back(face.z);
    }
}

void ReadObjectFile::loadFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::invalid_argument(
            std::string("Failed to open file: " + filePath));
        return;
    }

    reset();

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }

    file.close();
}

ObjectSource ReadObjectFile::Sources() {
    return {
        .indices = faces,
        .vertices = vertices,
    };
}
