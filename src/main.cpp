
#include "Core_defines.h"
#include "glfwWindow.h"
#include "shader.h"
#include "stb/stb_image.h"
#include "texture.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "layout (location = 2) in vec2 aTexCoord;\n"
                                 "out vec3 ourColorPass;\n"
                                 "out vec2 TexCord;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   ourColorPass = aColor;\n"
                                 "   TexCord = aTexCoord;\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColorPass;\n"
                                   "in vec2 TexCord;\n"
                                   "uniform sampler2D ourTexture;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = texture(ourTexture, TexCord) * vec4(ourColorPass,1.0f);\n"
                                   "}\n\0";

int main()
{
    glfwWindow *window = glfwWindow::CreateWindow("glfw window", 800, 600);

    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    float texCoords[] = {
            0.0f, 0.0f,// lower-left corner
            1.0f, 0.0f,// lower-right corner
            0.5f, 1.0f // top-center corner
    };

    unsigned int indecies[]{
            0, 1, 3,// first triangle
            1, 2, 3 // second triangle
    };


    texture tex1("textures/container.jpg", GL_RGB);
    texture tex2("textures/awesomeface.png", GL_RGBA);
    tex1.bind(0);
    tex2.bind(1);

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    shader shaderObj("shaders/vertexShader.shader", "shaders/fragmentShader.shader");

    shaderObj.bind();

    shaderObj.SetUniform1i("ourTexture", 0);
    shaderObj.SetUniform1i("texture2", 1);
    //wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        window->processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        shaderObj.SetUniformMat4("transform", trans);
        shaderObj.bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //identity matrix
        trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f,0.5f,0.0f));
        //moves up and down on y axis
        trans = glm::translate(trans, glm::vec3(0.0f, (cos(glfwGetTime())) / 2, 0.0f));
        //rotates on x, y and z
        trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));

        shaderObj.SetUniformMat4("transform", trans);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete window;
    return 0;
}
