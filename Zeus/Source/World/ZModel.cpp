#include "Core/CoreLibrary.h"
#include "ZModel.h"
#include "Core/Error.h"
#include "Windows/ZWindow.h"

ZModel::ZModel()
{
}

ZModel::ZModel(const ZTransform& transform) : z_Transform(transform)
{
}

void ZModel::Init()
{
}

void ZModel::Load(const std::filesystem::path& directory, const std::filesystem::path& path)
{
	z_Directory = directory;
	Assimp::Importer import{};
	const aiScene* scene = import.ReadFile((directory.string() + "/" + path.string()).c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		auto string = "Assimp failed to load model | " + path.string() + " " + import.GetErrorString();
		Error error(string);
	}

	ProcessNode(scene->mRootNode, scene);
}

void ZModel::Render(ZShader& shader, ZCamera& activeCamera)
{
	Mat4 model = Mat4(1.0);
	Mat4 view = Mat4(1.0);
	Mat4 projection = Mat4(1.0);

	projection = glm::perspective(glm::radians(45.0f), (float)ZWindow::GetSize().Width / (float)ZWindow::GetSize().Height, 0.1f, 100.0f);
	view = activeCamera.GetViewMatrix();

	model = glm::translate(model, z_Transform.GetPosition());
	if (z_Transform.GetRotation() != Vec3(0.0))
	{
		model = glm::rotate(model, static_cast<float>(45.0f * glfwGetTime() * 0.01), Vec3(1, 1, 0));
	}
	model = glm::scale(model, z_Transform.GetScale());

	shader.Attach();
	shader.SetMat4("Model", model);
	shader.SetMat4("View", view);
	shader.SetMat4("Projection", projection);

	for (auto& zMesh : z_Meshes)
	{
		zMesh.Render(shader);
	}
}

void ZModel::Free()
{
	for (auto& zMesh : z_Meshes)
	{
		zMesh.Free();
	}
}

void ZModel::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		z_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

ZMesh ZModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<ZTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.Position = glm::vec3
		(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);


		vertex.Normal = glm::vec3
		(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		if (mesh->mTextureCoords[0]) // Only load in the first texture
		{
			vertex.TextureCoordinate = glm::vec2
			(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.TextureCoordinate = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<ZTexture> diffuse = LoadTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuse.begin(), diffuse.end());

		std::vector<ZTexture> specular = LoadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specular.begin(), specular.end());
	}

	return ZMesh(vertices, indices, textures);
}

std::vector<ZTexture> ZModel::LoadTextures(aiMaterial* material, aiTextureType type)
{
	std::vector<ZTexture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString string;
		material->GetTexture(type, i, &string);
		Log::Info(string.C_Str());

		bool skip = false;

		for (size_t j = 0; j < z_Textures.size(); j++)
		{
			if (std::strcmp(z_Textures[j].GetPath().string().data(), string.C_Str()) == 0)
			{
				textures.push_back(z_Textures[j]);
				skip = true;
			}
		}

		if (!skip)
		{
			ZTexture texture = ZTexture(z_Directory, string.C_Str(), type);
			textures.push_back(texture);
			z_Textures.push_back(texture);
		}
	}

	return textures;
}
