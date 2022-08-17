
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
    //Lighting scene;

    std::shared_ptr<Shader> lightingShader = std::make_shared<Shader>("shaders/lighting/1.colors.vs", "shaders/lighting/1.colors.fs");
    std::shared_ptr<Shader> lightCubeShader = std::make_shared<Shader>("shaders/lighting/1.light_cube.vs", "shaders/lighting/1.light_cube.fs");
    Camera camera(lightingShader);
    Camera camera1(lightCubeShader);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,

            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,

            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,

            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        window->processInput();
        camera.processInput(window->GetWindow());
        camera1.processInput(window->GetWindow());
        //scene.OnUpdate(window);
        //glClearColor(0.29f, 0.38f, 0.61f, 1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //scene.OnRender();
        lightingShader->bind();
        lightingShader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        camera.onUpdate();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
        lightingShader->SetUniformMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightCubeShader->bind();
        camera1.onUpdate();
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, -1.5f));
        lightCubeShader->SetUniformMat4("model", model);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete window;
    return 0;
}
