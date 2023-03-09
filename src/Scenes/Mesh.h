//
// Created by TANK1_41 on 3/1/2023.
//

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H
#include "../Shader.h"
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <vector>
struct Vertex {
    glm::vec3 Positions;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    //mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);

private:
    //render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif//OPENGL_MESH_H
