#pragma once

#ifndef VertexBuffer_h
#define VertexBuffer_h

class VertexBuffer {
private:
    unsigned int id;
public:
    VertexBuffer(const void* data, unsigned int count);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif /* VertexBuffer_h */