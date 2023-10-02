#pragma once

#ifndef Texture_h
#define Texture_h

#include <string>

#include <glad/glad.h>
#include "stb_image/stb_image.h"

class Texture {
private:
    unsigned int id;
    std::string filepath;
    unsigned char* localBuffer;
    int width, height, bpp;

    void load();
    void unload();

public:
    Texture(const std::string& filepath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
};

#endif /* Texture_h */