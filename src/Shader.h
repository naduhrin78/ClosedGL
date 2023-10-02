#pragma once

#ifndef Shader_h
#define Shader_h

#include <string>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>

struct ShaderSource {
    std::string Vertex;
    std::string Fragment;
};

class Shader {
private:
    unsigned int id;
    std::unordered_map <std::string, int> uniformLocationCache;

    ShaderSource parseShader(const std::string& filePath);
    unsigned int compileShader(int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

    int getUniformLocation(const std::string& name);
public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1f(const std::string& name, float v1);
    void setUniform1i(const std::string& name, int v1);
    void setUniform3f(const std::string& name, float v1, float v2, float v3);
    void setUniform3f(const std::string& name, glm::vec3 v1);
    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void setUniformMat4f(const std::string& name, glm::mat4 v1);
};

#endif /* Shader_h */