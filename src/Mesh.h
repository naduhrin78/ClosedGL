#pragma once

#ifndef Mesh_h
#define Mesh_h

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

struct MeshVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct MeshTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();

public:
    // mesh data
    std::vector<MeshVertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshTexture>      textures;

    Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices,
        std::vector<MeshTexture> textures);
    void Draw(Shader& shader);
};

#endif /* Mesh_h */