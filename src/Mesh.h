#pragma once

#include "OpenGLErrorHandler.h"
#include "Shader.h"

#include <string>
#include <vector>

//#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    glm::vec3 tangent;
    glm::vec3 bitangent;

    //int boneIDs[MAX_BONE_INFLUENCE];
    //float weights[MAX_BONE_INFLUENCE];
};

/// <summary>
/// Adding MeshNameSpace to avoid conflict with Main Texture Class.
/// </summary>
namespace MeshNameSpace
{
    struct Texture
    {
        unsigned int rendererID;
        std::string type;
        std::string path;
    };
}

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshNameSpace::Texture> textures;

    //unsigned int vertexArrayObject;

    //Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshNameSpace::Texture> textures);
    void Draw(Shader& shader);
private:
    unsigned int vertexBufferObject, elementBufferObject, vertexArrayObject;
    void SetupMesh();
};