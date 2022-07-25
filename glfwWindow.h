//
// Created by William Aey on 7/24/2022.
//

#ifndef OPENGL_GLFWWINDOW_H
#define OPENGL_GLFWWINDOW_H

//Glad must be included first
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>
class glfwWindow {
    glfwWindow(const char *title, unsigned int width, unsigned int height);

public:
    virtual ~glfwWindow();
    void InitGlfwAndGlad();
    GLFWwindow* GetWindow();

    [[nodiscard]] static glfwWindow *CreateWindow(const char *title, unsigned int width, unsigned int height);
private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    struct windowAtrributes {
        std::string title;
        unsigned int width;
        unsigned int height;
    };

    windowAtrributes m_windowProps;
    GLFWwindow *m_window;
private:
    static glfwWindow *s_instance;
};


#endif//OPENGL_GLFWWINDOW_H
