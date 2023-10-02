#pragma once

#ifndef IndexBuffer_h
#define IndexBuffer_h
#include <glad/glad.h>

class IndexBuffer {
private:
    unsigned int id;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* indices, unsigned int size);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
};

#endif /* IndexBuffer_h */