//
// Created by TANK1_41 on 3/6/2023.
//

#include "Model.h"
void Model::Draw(Shader &shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }
}
void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
{

    //proccess all node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    //same for all of the children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        //process vertex positions, normals, and texture cords
        //....
        vertices.push_back(vertex);
    }
    //process indecices
    //...

    //process material
    if (mesh->mMaterialIndex >= 0)
    {
    }
    return Mesh(vertices, indices, textures)
}
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType *type, std::string typeName)
{
    return std::vector<Texture>();
}
