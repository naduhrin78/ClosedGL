#pragma once

#ifndef VertexObject_h
#define VertexObject_h

#include <stdio.h>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class VertexObject {
private:
    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;
public:
    VertexBufferLayout vbl;

    VertexObject();
    ~VertexObject();

    void bind() const;
    void unbind() const;
};

#endif /* VertexObject_h */