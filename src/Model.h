#pragma once

#ifndef Model_h
#define Model_h

#include "Mesh.h"

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<MeshTexture> textures_loaded;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

public:
    Model(char* path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);
};

#endif /* Model_h */