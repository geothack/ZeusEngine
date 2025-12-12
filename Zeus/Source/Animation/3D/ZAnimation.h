#pragma once

#include "World/ZModel.h"
#include "Animation/3D/ZBone.h"

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class ZAnimation
{
public:
	ZAnimation() = default;

	ZAnimation(const std::string& animationPath, ZModel* model);

	~ZAnimation() = default;

	ZBone* FindZBone(const std::string& name);

	inline float GetTicksPerSecond() { return z_TicksPerSecond; }
	inline float GetDuration() { return z_Duration; }
	inline const AssimpNodeData& GetRootNode() { return z_RootNode; }
	inline const std::map<std::string, BoneInfo>& GetZBoneIDMap()
	{
		return z_ZBoneInfoMap;
	}

private:
	void ReadMissingZBones(const aiAnimation* animation, ZModel& model);

	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);

private:
	float z_Duration;
	int z_TicksPerSecond;
	std::vector<ZBone> z_ZBones;
	AssimpNodeData z_RootNode;
	std::map<std::string, BoneInfo> z_ZBoneInfoMap;

};