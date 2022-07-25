#include <iostream>


#include "glfwWindow.h"
#include "Core_defines.h"



int main()
{
    glfwWindow* window = glfwWindow::CreateWindow("glfw window", 800,600);

    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        window->processInput();

        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete window;
    return 0;
}



