#pragma once

#include "Render/ZCamera.h"
#include "Render/ZShader.h"
#include "World/ZMesh.h"
#include "World/ZTransform.h"

#include "Animation/3D/AssimpGLMHelpers.h"

struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};


class ZModel
{
public:
	ZModel(const std::filesystem::path& directory = "", const std::filesystem::path& path = "");

	void Init();

	void Load(const std::filesystem::path& directory, const std::filesystem::path& path);

	void Render(ZShader& shader, ZCamera& activeCamera, ZTransform& transform, bool depthPass = false);

	void Free();

	auto& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }

	/*void SetVertexBoneDataToDefault(Vertex& vertex)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
		{
			vertex.m_BoneIDs[i] = -1;
			vertex.m_Weights[i] = 0.0f;
		}
	}

	void SetVertexBoneData(Vertex& vertex, int boneID, float weight)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
		{
			if (vertex.m_BoneIDs[i] < 0)
			{
				vertex.m_Weights[i] = weight;
				vertex.m_BoneIDs[i] = boneID;
				break;
			}
		}
	}*/


	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
	{
		auto& boneInfoMap = m_BoneInfoMap;
		int& boneCount = m_BoneCounter;

		for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			int boneID = -1;
			std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				BoneInfo newBoneInfo;
				newBoneInfo.id = boneCount;
				newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
				boneInfoMap[boneName] = newBoneInfo;
				boneID = boneCount;
				boneCount++;
			}
			else
			{
				boneID = boneInfoMap[boneName].id;
			}
			assert(boneID != -1);
			auto weights = mesh->mBones[boneIndex]->mWeights;
			int numWeights = mesh->mBones[boneIndex]->mNumWeights;

			for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			{
				int vertexId = weights[weightIndex].mVertexId;
				float weight = weights[weightIndex].mWeight;
				assert(vertexId <= vertices.size());
				//SetVertexBoneData(vertices[vertexId], boneID, weight);
			}
		}
	}

private:
	void ProcessNode(aiNode* node, const aiScene* scene);

	ZMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<ZTexture> LoadTextures(aiMaterial* material, aiTextureType type);

protected:
	std::vector<ZMesh> z_Meshes{};
	std::vector<ZTexture> z_Textures;

	std::filesystem::path z_Directory{};

	std::map<std::string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;

};

