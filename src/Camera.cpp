//
// Created by William Aey on 8/15/2022.
//

#include "Camera.h"

#include <utility>

float Camera::s_lastX{400.f};
float Camera::s_lastY{300.f};
bool Camera::s_firstMouse{true};
float Camera::s_yaw{-90.f};
float Camera::s_pitch{0.0f};
float Camera::s_fov{45.f};
glm::vec3 Camera::s_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};

Camera::Camera(std::shared_ptr<Shader> shaderObj)
    : m_deltaTime(0.0f), m_lastFrame(0.0f), m_Shader(std::move(shaderObj)), m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

void Camera::onUpdate()
{
    auto currentFrame = (float) glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    m_view = glm::lookAt(m_cameraPos, m_cameraPos + s_cameraFront, m_cameraUp);
    m_projection = glm::perspective(glm::radians(s_fov), 800.0f / 600.0f, 0.1f, 100.0f);
    m_Shader->SetUniformMat4("view", m_view);
    m_Shader->SetUniformMat4("projection", m_projection);
}

void Camera::processInput(GLFWwindow *window)
{
    const float cameraSpeed = 4.5f * m_deltaTime;// adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * s_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * s_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= glm::normalize(glm::cross(s_cameraFront, m_cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += glm::normalize(glm::cross(s_cameraFront, m_cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_cameraPos += m_cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_cameraPos -= m_cameraUp * cameraSpeed;
}
void Camera::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    s_fov -= (float) yoffset;
    if (s_fov < 1.0f)
        s_fov = 1.0f;
    if (s_fov > 45.0f)
        s_fov = 45.0f;
}
void Camera::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (s_firstMouse)// initially set to true
    {
        s_lastX = (float) xpos;
        s_lastY = (float) ypos;
        s_firstMouse = false;
    }

    float xoffset = (float) xpos - s_lastX;
    float yoffset = s_lastY - (float) ypos;// reversed since y-coordinates range from bottom to top
    s_lastX = (float) xpos;
    s_lastY = (float) ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    s_yaw += xoffset;
    s_pitch += yoffset;

    if (s_pitch > 89.0f)
        s_pitch = 89.0f;
    if (s_pitch < -89.0f)
        s_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(s_yaw)) * cos(glm::radians(s_pitch));
    direction.y = sin(glm::radians(s_pitch));
    direction.z = sin(glm::radians(s_yaw)) * cos(glm::radians(s_pitch));
    s_cameraFront = glm::normalize(direction);
}
glm::vec3 Camera::getCameraPos()
{
    return m_cameraPos;
}
