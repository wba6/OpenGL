//
// Created by William Aey on 7/26/2022.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include "Common_defines.h"
#include <glm/glm.hpp>
class Shader {

public:
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    virtual ~Shader();


    void bind();
    void unBind();

    void SetUniform4f(const char *uniform, float x, float y, float z, float w);
    void SetUniform3f(const char *uniform, float x, float y, float z);
    void SetUniformMat4(const char *uniform, glm::mat4 trans);
    void SetUniform1i(const char *uniform, int value);

private:
    int getUniformLoc(const char *uniform) const;
    void shaderCompileStatus(unsigned int id);

    int m_shaderProgramID;
    unsigned int m_fragmentShaderID;
    unsigned int m_vertexShaderID;
};


#endif//OPENGL_SHADER_H
