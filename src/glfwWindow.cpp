//
// Created by William Aey on 7/24/2022.
//

#include "glfwWindow.h"
#include "Core_defines.h"

glfwWindow* glfwWindow::s_instance = nullptr;

glfwWindow::glfwWindow(const char *title, int width, int height)
{
    s_instance = this;
    m_windowProps.title = title;
    m_windowProps.width = width;
    m_windowProps.height = height;
    s_instance = this;
    InitGlfwAndGlad();
}
glfwWindow::~glfwWindow()
{
    glfwTerminate();
}
glfwWindow *glfwWindow::CreateWindow(const char *title, int width, int height)
{
    if (s_instance == nullptr)
    {
        s_instance = new glfwWindow(title, width, height);
    }
    return s_instance;
}
void glfwWindow::InitGlfwAndGlad()
{
    //setting flags for glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //setting up our window
    m_window = glfwCreateWindow(m_windowProps.width, m_windowProps.height, m_windowProps.title.c_str(), nullptr, nullptr);
    if (m_window == nullptr)
    {
        LOG("Failed to created window")
        glfwTerminate();
        throw -1;
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        LOG("GLAD failed to init")
        throw -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(m_window, glfwWindow::framebuffer_size_callback);
}
GLFWwindow *glfwWindow::GetWindow()
{
    return m_window;
}
void glfwWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void glfwWindow::processInput()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}
