
#include "Camera.h"
#include "Core_defines.h"
#include "Scenes/Lighting.h"
#include "Scenes/RoomOfBoxes.h"
#include "Shader.h"
#include "glfwWindow.h"
#include "stb/stb_image.h"
#include "texture.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    glfwWindow *window = glfwWindow::CreateWindow("glfw window", 800, 600);
    Lighting scene;


    //wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        window->processInput();
        scene.OnUpdate(window);
        glClearColor(0.29f, 0.38f, 0.61f, 1.0f);// ----sky blue
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // ----Dark gray
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.OnRender();


        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete window;
    return 0;
}
