//
// Created by William Aey on 7/26/2022.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include "Core_defines.h";
#include "glad/glad.h"

class shader {

public:
    shader(const char *vertexShader, const char *fragmentShader);
    virtual ~shader();


    void bind();
    void unBind();

    void SetUniform4f(const char *uniform, float x, float y, float z, float w);

private:
    int getUniformLoc(const char *uniform);
    void shaderCompileStatus(unsigned int id);

    int m_shaderProgramID;
    unsigned int m_fragmentShaderID;
    unsigned int m_vertexShaderID;
};


#endif//OPENGL_SHADER_H
