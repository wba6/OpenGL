//
// Created by TANK1_41 on 3/1/2023.
//

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H
#include "../Shader.h"
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <vector>

#define MAX_BONE_INFLUENCE 4
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
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
    void Draw(std::shared_ptr<Shader> shader);

private:
    //render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif//OPENGL_MESH_H
