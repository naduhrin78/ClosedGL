#include "Texture.h"

Texture::Texture(const std::string& filepath)
    : id(0), filepath(filepath), localBuffer(nullptr), width(0), height(0), bpp(0)
{
    load();
}

Texture::~Texture()
{
    unload();
}
void Texture::load() {
    stbi_set_flip_vertically_on_load(true);
    localBuffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 0);

    if (!localBuffer)
    {
        fprintf(stderr, "Failed to load texture\n");
        exit(1);
    }

    GLenum format;
    if (bpp == 1)
        format = GL_RED;
    else if (bpp == 4)
        format = GL_RGBA;
    else
        format = GL_RGB;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (localBuffer) {
        stbi_image_free(localBuffer);
    }
}

void Texture::unload()
{
    glDeleteTextures(1, &id);
    id = 0;
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}