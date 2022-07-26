//
// Created by William Aey on 7/26/2022.
//

#include "shader.h"
shader::shader(const char *vertexShader, const char *fragmentShader)
{
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, &vertexShader, NULL);
    glCompileShader(m_vertexShaderID);
    shaderCompileStatus(m_vertexShaderID);

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, &fragmentShader, NULL);
    glCompileShader(m_fragmentShaderID);
    shaderCompileStatus(m_fragmentShaderID);

    m_shaderProgramID = glCreateProgram();

    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
    glLinkProgram(m_shaderProgramID);

    int success;
    char infoLog[512];
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
}
void shader::shaderCompileStatus(unsigned int id)
{
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw "Shader failed to compile";
    }
}
void shader::bind()
{
    glUseProgram(m_shaderProgramID);
}
void shader::unBind()
{
    glUseProgram(0);
}
shader::~shader()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_vertexShaderID);
}
int shader::getUniformLoc(const char *uniform)
{

    int loc = glGetUniformLocation(m_shaderProgramID, uniform);
    if (loc == -1)
        throw "Shader not found";
    return loc;
}
void shader::SetUniform4f(const char *uniform, float x, float y, float z, float w)
{
    glUniform4f(getUniformLoc(uniform), x, y, z, w);
}
