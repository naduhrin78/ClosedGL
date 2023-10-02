#pragma once

#ifndef VertexArray_h
#define VertexArray_h

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>

struct Vertex {
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};

class VertexArray {
private:
    unsigned int id;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
public:
    VertexBufferLayout layout;

    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

    void setVertices(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};

#endif /* VertexArray_h */