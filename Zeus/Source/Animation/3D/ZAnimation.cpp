#include <Core/CoreLibrary.h>
#include "ZAnimation.h"

ZAnimation::ZAnimation(const std::string& animationPath, ZModel* model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	auto animation = scene->mAnimations[0];
	z_Duration = animation->mDuration;
	z_TicksPerSecond = animation->mTicksPerSecond;
	aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
	globalTransformation = globalTransformation.Inverse();
	ReadHierarchyData(z_RootNode, scene->mRootNode);
	ReadMissingZBones(animation, *model);
}

ZBone* ZAnimation::FindZBone(const std::string& name)
{
	auto iter = std::find_if(z_ZBones.begin(), z_ZBones.end(),
		[&](const ZBone& ZBone)
		{
			return ZBone.GetBoneName() == name;
		}
	);
	if (iter == z_ZBones.end()) return nullptr;
	else return &(*iter);
}

void ZAnimation::ReadMissingZBones(const aiAnimation* animation, ZModel& model)
{
	int size = animation->mNumChannels;

	auto& ZBoneInfoMap = model.GetBoneInfoMap();//getting z_ZBoneInfoMap from Model class
	int& ZBoneCount = model.GetBoneCount(); //getting the z_ZBoneCounter from Model class

	//reading channels(ZBones engaged in an animation and their keyframes)
	for (int i = 0; i < size; i++)
	{
		auto channel = animation->mChannels[i];
		std::string ZBoneName = channel->mNodeName.data;

		if (ZBoneInfoMap.find(ZBoneName) == ZBoneInfoMap.end())
		{
			ZBoneInfoMap[ZBoneName].id = ZBoneCount;
			ZBoneCount++;
		}
		z_ZBones.push_back(ZBone(channel->mNodeName.data,
			ZBoneInfoMap[channel->mNodeName.data].id, channel));
	}

	z_ZBoneInfoMap = ZBoneInfoMap;
}

void ZAnimation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
	assert(src);

	dest.name = src->mName.data;
	dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
	dest.childrenCount = src->mNumChildren;

	for (int i = 0; i < src->mNumChildren; i++)
	{
		AssimpNodeData newData;
		ReadHierarchyData(newData, src->mChildren[i]);
		dest.children.push_back(newData);
	}
}
