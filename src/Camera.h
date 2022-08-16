//
// Created by William Aey on 8/15/2022.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H
#include "Core_defines.h"
#include "shader.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera {
public:
    Camera(shader &shaderObj);


    void processInput(GLFWwindow *window);
    void onUpdate();
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

private:
    static float s_lastX, s_lastY;
    static bool s_firstMouse;
    static float s_yaw;
    static float s_pitch;
    static float s_fov;
    static glm::vec3 s_cameraFront;
    float m_deltaTime;
    float m_lastFrame;
    shader &m_Shader;
    glm::mat4 m_projection;
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraUp;
    glm::mat4 m_view;
};


#endif//OPENGL_CAMERA_H
