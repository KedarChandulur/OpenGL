#include "Mesh.h"

#include <GL/glew.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshNameSpace::Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + i));

        std::string number;
        std::string name = textures[i].type;

        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        GLCall(shader.SetUniform1i((name + number).c_str(), i));
        GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].rendererID));
    }

    GLCall(glBindVertexArray(vertexArrayObject));
    GLCall(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, (void *)0));

    GLCall(glBindVertexArray(0));
    GLCall(glActiveTexture(GL_TEXTURE0));
}

void Mesh::SetupMesh()
{
    GLCall(glGenVertexArrays(1, &vertexArrayObject));
    GLCall(glGenBuffers(1, &vertexBufferObject));
    GLCall(glGenBuffers(1, &elementBufferObject));

    GLCall(glBindVertexArray(vertexArrayObject));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject));
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::position)));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal)));

    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texCoords)));

    GLCall(glEnableVertexAttribArray(3));
    GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::tangent)));

    GLCall(glEnableVertexAttribArray(4));
    GLCall(glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::bitangent)));

    GLCall(glEnableVertexAttribArray(5));
    GLCall(glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs)));

    GLCall(glEnableVertexAttribArray(6));
    GLCall(glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights)));

    GLCall(glBindVertexArray(0));
}