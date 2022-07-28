//
// Created by William Aey on 7/27/2022.
//
#include "texture.h"
#include "../vender/stb/stb_image.h"
#include "Core_defines.h"
#include "glad/glad.h"

texture::texture(const char *textureFilePath, int pixelFormat)
    : width(0), height(0)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int nrChannels{0};
    unsigned char *data = stbi_load(textureFilePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOG("Failed to load texture");
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void texture::bind(int slot = 0)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
void texture::unBind(int slot = 0)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
