//
// Created by William Aey on 7/27/2022.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "stb/stb_image.h"
class texture {
public:
    texture(const char *textureFilePath, int pixelFormat);

    void bind(int slot);
    void unBind(int slot);

private:
    int width, height;
    unsigned int textureID;
};


#endif//OPENGL_TEXTURE_H
