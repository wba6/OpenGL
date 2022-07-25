//
// Created by William Aey on 7/24/2022.
//

#ifndef OPENGL_GLFWWINDOW_H
#define OPENGL_GLFWWINDOW_H

//Glad must be included first
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include <string>
class glfwWindow {
    glfwWindow(const char *title, int width, int height);

public:
    virtual ~glfwWindow();
    void InitGlfwAndGlad();
    GLFWwindow* GetWindow();
    void processInput();

    [[nodiscard]] static glfwWindow *CreateWindow(const char *title, int width, int height);

private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    struct windowAtrributes {
        std::string title;
        int width;
        int height;
    };

    windowAtrributes m_windowProps;
    GLFWwindow *m_window;
private:
    static glfwWindow *s_instance;
};


#endif//OPENGL_GLFWWINDOW_H
