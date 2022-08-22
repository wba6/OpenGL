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
class RoomOfBoxs : public Scene {
public:
    RoomOfBoxs()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        texture tex1("textures/container.jpg", GL_RGB);
        texture tex2("textures/awesomeface.png", GL_RGBA);
        tex1.bind(0);
        tex2.bind(1);

        m_shaderObj = std::make_shared<Shader>("shaders/vertexShader.Shader", "shaders/fragmentShader.Shader");
        m_camera = std::make_unique<Camera>(m_shaderObj);

        m_shaderObj->bind();
        m_shaderObj->SetUniform1i("ourTexture", 0);
        m_shaderObj->SetUniform1i("texture2", 1);
    }

    void OnUpdate(glfwWindow *&window) override
    {
        m_camera->processInput(window->GetWindow());
    }

    void OnRender() override
    {
        m_camera->onUpdate();

        m_shaderObj->bind();
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_cubePositions[i]);
            float angle = 20.0f * (float) i;
            if (angle == 0)
                angle = 40.0f;
            model = glm::rotate(model, (float) glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_shaderObj->SetUniformMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

private:
    float m_vertices[180] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                             0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                             -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                             -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                           -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                           -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                           -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                           -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                           -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                           -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                           -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                           0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                           0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                           0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                           0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                           0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                           0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                           -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                           0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                           0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                             -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
    const float m_texCoords[6] = {
            0.0f, 0.0f,// lower-left corner
            1.0f, 0.0f,// lower-right corner
            0.5f, 1.0f // top-center corner
    };
    glm::vec3 m_cubePositions[10] = {
            glm::vec3(0.0f, 0.0f, -1.5f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)};

    std::unique_ptr<Camera> m_camera;
    std::shared_ptr<Shader> m_shaderObj;
};