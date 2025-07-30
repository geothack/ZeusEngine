#pragma once

#include "Render/ZShader.h"
#include "World/ZMesh.h"
#include "World/ZTransform.h"


class ZModel
{
public:
	ZModel();
	ZModel(const ZTransform& transform);

	void Init();

	void Load(const std::filesystem::path& directory, const std::filesystem::path& path);

	void Render(ZShader& shader);

	void Free();

private:
	void ProcessNode(aiNode* node, const aiScene* scene);

	ZMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<ZTexture> LoadTextures(aiMaterial* material, aiTextureType type);

protected:
	std::vector<ZMesh> z_Meshes{};
	std::vector<ZTexture> z_Textures;

	std::filesystem::path z_Directory{};

	ZTransform z_Transform;

};

