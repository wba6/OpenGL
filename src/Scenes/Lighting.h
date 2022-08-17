//
// Created by William Aey on 8/16/2022.
//

#pragma once
#define OPENGL_LIGHTING_H
#include "../Camera.h"
#include "../Core_defines.h"
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
        // first, configure the cube's VAO (and VBO)

        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(cubeVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)

        glGenVertexArrays(1, &lightCubeVAO);
        glBindVertexArray(lightCubeVAO);

        // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        //lightshaderObj = std::make_shared<Shader>("shaders/lighting/vertexLighting.Shader","shaders/lighting/fragmentLighting.Shader");
        lightshaderObj = std::make_shared<Shader>("shaders/vertexShader.Shader", "shaders/fragmentShader.Shader");
        cubeshaderObj = std::make_shared<Shader>("shaders/lighting/fragmentBlank.Shader", "shaders/lighting/fragmentBlank.Shader");
        //lightshaderObj->bind();
        //lightshaderObj->SetUniform3f("objectColor", 1.0f,0.5f,0.31f);
        //lightshaderObj->SetUniform3f("lightColor", 1.0f,1.0f,1.0f);

        camera = std::make_unique<Camera>(lightshaderObj);
    };
    void OnUpdate(glfwWindow *&window) override
    {
        camera->processInput(window->GetWindow());
    }
    void OnRender() override
    {
        lightshaderObj->bind();
        //lightshaderObj->SetUniform3f("objectColor", 1.0f,0.5f,0.31f);
        //lightshaderObj->SetUniform3f("lightColor", 1.0f,1.0f,1.0f);
        camera->onUpdate();
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //        cubeshaderObj->bind();
        //        glBindVertexArray(lightCubeVAO);
        //        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

private:
    unsigned int cubeVAO;
    unsigned int lightCubeVAO;
    std::unique_ptr<Camera> camera;
    std::shared_ptr<Shader> lightshaderObj;
    std::shared_ptr<Shader> cubeshaderObj;
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