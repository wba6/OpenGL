#include <iostream>


#include "glfwWindow.h"
#include "Core_defines.h"


int main()
{
    glfwWindow* window = glfwWindow::CreateWindow("glfw window", 800,600);

    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        glfwSwapBuffers(window->GetWindow());


        glfwPollEvents();
    }

    delete window;
    return 0;
}

