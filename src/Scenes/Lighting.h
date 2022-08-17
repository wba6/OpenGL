//
// Created by William Aey on 8/16/2022.
//

#pragma once
#include "../Camera.h"
#include "../Common_defines.h"
#include "../Scene.h"
#include "../glfwWindow.h"
#include "../texture.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Lighting : public Scene {
public:
    Lighting()
    {

        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(cubeVAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);


        glGenVertexArrays(1, &lightCubeVAO);
        glBindVertexArray(lightCubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        lightingShader = std::make_shared<Shader>("shaders/lighting/1.colors.vs", "shaders/lighting/1.colors.fs");
        lightCubeShader = std::make_shared<Shader>("shaders/lighting/1.light_cube.vs", "shaders/lighting/1.light_cube.fs");
        cameraLight = std::make_unique<Camera>(lightingShader);
        cameraCube = std::make_unique<Camera>(lightCubeShader);
    };
    void OnUpdate(glfwWindow *&window) override
    {
        cameraLight->processInput(window->GetWindow());
        cameraCube->processInput(window->GetWindow());
    }
    void OnRender() override
    {
        lightingShader->bind();
        lightingShader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        cameraLight->onUpdate();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
        lightingShader->SetUniformMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightCubeShader->bind();
        cameraCube->onUpdate();
        model = glm::translate(model, glm::vec3(3.5f, 2.5f, -5.5f));
        lightCubeShader->SetUniformMat4("model", model);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

private:
    unsigned int cubeVAO;
    unsigned int lightCubeVAO;
    std::unique_ptr<Camera> cameraLight;
    std::unique_ptr<Camera> cameraCube;
    std::shared_ptr<Shader> lightingShader;
    std::shared_ptr<Shader> lightCubeShader;
    float vertices[108]{
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f};
};