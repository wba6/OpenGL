
#include "Camera.h"
#include "Scenes/Lighting.h"
#include "Scenes/Model.h"
#include "Scenes/RoomOfBoxes.h"
#include "glfwWindow.h"
#include <glad/glad.h>

int main()
{
    glfwWindow *window = glfwWindow::CreateWindow("glfw window", 800, 600);
    Lighting scene;

    // build and compile shaders
    // -------------------------
    std::shared_ptr<Shader> ourShader = std::make_shared<Shader>("shaders/model.vs.shader", "shaders/model.fg.shader");

    // load models
    // -----------
    Model ourModel("shaders/backpack/backpack.obj");
    Camera camera(ourShader);
    //wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        window->processInput();
        //scene.OnUpdate(window);
        //glClearColor(0.29f, 0.38f, 0.61f, 1.0f);// ----sky blue
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);// ----Dark gray
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader->bind();

        // view/projection transformations
        camera.processInput(window->GetWindow());
        camera.onUpdate();

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));// translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));    // it's a bit too big for our scene, so scale it down
        ourShader->SetUniformMat4("model", model);
        ourModel.Draw(ourShader);
        //scene.OnRender();

        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete window;
    return 0;
}
