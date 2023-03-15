//
// Created by TANK1_41 on 3/6/2023.
//

#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H
#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>

#include "../Shader.h"
#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
class Model {
public:
    Model(std::string path)
    {
        loadModel(path);
    }
    void Draw(std::shared_ptr<Shader> shader);

private:
    //model data
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};


#endif//OPENGL_MODEL_H
