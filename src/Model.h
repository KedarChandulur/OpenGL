#pragma once

#include "Mesh.h"

#include "assimp/scene.h"

#include <string>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(char* path)
	{
		LoadModel(path);
	}
	void Draw(Shader& shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<MeshNameSpace::Texture> textures_loaded;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MeshNameSpace::Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};