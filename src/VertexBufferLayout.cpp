#include "VertexBufferLayout.h"

void VertexBufferLayout::apply() const {
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, stride, (const void*)(size_t)offset);

        offset += elements[i].size();
    }

}