#pragma once

#ifndef Model_h
#define Model_h

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "AssimpGLMHelpers.h"
#include "AnimData.h"

class Model
{
public:
    // model data
    std::vector<MeshTexture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    // draws the model, and thus all its meshes
    void Draw(Shader& shader);

    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; }

private:
    std::map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;

    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    void SetVertexBoneDataToDefault(MeshVertex& vertex);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(MeshVertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<MeshVertex>& vertices, aiMesh* mesh, const aiScene* scene);
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
    std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif /* Model_h */