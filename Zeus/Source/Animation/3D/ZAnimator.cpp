#include "Core/CoreLibrary.h"
#include "ZAnimator.h"

ZAnimator::ZAnimator(ZAnimation* Animation)
{
    z_CurrentTime = 0.0;
    z_CurrentAnimation = Animation;

    z_FinalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        z_FinalBoneMatrices.push_back(glm::mat4(1.0f));
}

void ZAnimator::UpdateAnimation(float dt)
{
    z_DeltaTime = dt;
    if (z_CurrentAnimation)
    {
        z_CurrentTime += z_CurrentAnimation->GetTicksPerSecond() * dt;
        z_CurrentTime = fmod(z_CurrentTime, z_CurrentAnimation->GetDuration());
        CalculateBoneTransform(&z_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
    }
}

void ZAnimator::PlayAnimation(ZAnimation* pAnimation)
{
    z_CurrentAnimation = pAnimation;
    z_CurrentTime = 0.0f;
}

void ZAnimator::CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
{
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;

    ZBone* Bone = z_CurrentAnimation->FindZBone(nodeName);

    if (Bone)
    {
        Bone->Update(z_CurrentTime);
        nodeTransform = Bone->GetLocalTransform();
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    auto boneInfoMap = z_CurrentAnimation->GetZBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        z_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}
