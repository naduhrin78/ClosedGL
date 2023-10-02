#pragma once

#ifndef VertexBufferLayout_h
#define VertexBufferLayout_h

#include <glad/glad.h>
#include <vector>

struct VertexBufferElement {
    int count;
    unsigned int type;
    unsigned char normalized;

    int size() const {
        int unitSize = 0;

        switch (type) {
        case GL_FLOAT:
            unitSize = sizeof(GLfloat);
            break;
        case GL_UNSIGNED_INT:
            unitSize = sizeof(GLuint);
            break;
        case GL_BYTE:
            unitSize = sizeof(GLbyte);
            break;
        default:
            break;
        }

        return unitSize * count;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    int stride;
public:
    VertexBufferLayout() : stride(0) {};
    void apply() const;

    template<typename T>
    void push(int count) {
        assert(false);
    }

    template<>
    void push<float>(int count) {
        elements.push_back({ count, GL_FLOAT, GL_FALSE });
        stride += (count * sizeof(GLfloat));
    }

    template<>
    void push<unsigned int>(int count) {
        elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
        stride += (count * sizeof(GLuint));
    }

    template<>
    void push<unsigned char>(int count) {
        elements.push_back({ count, GL_BYTE, GL_FALSE });
        stride += (count * sizeof(GLbyte));
    }

    inline const std::vector<VertexBufferElement> getElements() const& {
        return elements;
    }

    inline int getStride() const {
        return stride;
    }
};

#endif /* VertexBufferLayout_h */