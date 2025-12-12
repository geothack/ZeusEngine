#pragma once

#include "Animation/3D/ZAnimation.h"

class ZAnimator
{
public:
    ZAnimator() = default;

    ZAnimator(ZAnimation* Animation);

    void UpdateAnimation(float dt);

    void PlayAnimation(ZAnimation* pAnimation);

    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

    std::vector<glm::mat4> GetFinalBoneMatrices()
    {
        return z_FinalBoneMatrices;
    }

private:
    std::vector<glm::mat4> z_FinalBoneMatrices;
    ZAnimation* z_CurrentAnimation;
    float z_CurrentTime;
    float z_DeltaTime;

};

