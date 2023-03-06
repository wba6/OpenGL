//
// Created by TANK1_41 on 3/6/2023.
//

#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H
#include "../Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
class Model {
public:
    Model(char *path)
    {
        loadModel(path);
    }
    void Draw(Shader &shader);

private:
    //model data
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType *type, std::string typeName);
};


#endif//OPENGL_MODEL_H
