#pragma once

#ifndef Mesh_h
#define Mesh_h

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

#define MAX_BONE_INFLUENCE 4

struct MeshVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
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