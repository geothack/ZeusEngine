#include "Core/CoreLibrary.h"
#include "ZBone.h"

ZBone::ZBone(const std::string& name, int ID, const aiNodeAnim* channel) : z_Name(name), z_ID(ID), z_LocalTransform(1.0f)
{
    z_NumPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < z_NumPositions; ++positionIndex)
    {
        aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float timeStamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
        data.timeStamp = timeStamp;
        z_Positions.push_back(data);
    }

    z_NumRotations = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < z_NumRotations; ++rotationIndex)
    {
        aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
        data.timeStamp = timeStamp;
        z_Rotations.push_back(data);
    }

    z_NumScalings = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < z_NumScalings; ++keyIndex)
    {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = AssimpGLMHelpers::GetGLMVec(scale);
        data.timeStamp = timeStamp;
        z_Scales.push_back(data);
    }
}

void ZBone::Update(float animationTime)
{
    glm::mat4 translation = InterpolatePosition(animationTime);
    glm::mat4 rotation = InterpolateRotation(animationTime);
    glm::mat4 scale = InterpolateScaling(animationTime);
    z_LocalTransform = translation * rotation * scale;
}

int ZBone::GetPositionIndex(float animationTime)
{
    for (int index = 0; index < z_NumPositions - 1; ++index)
    {
        if (animationTime < z_Positions[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

int ZBone::GetRotationIndex(float animationTime)
{
    for (int index = 0; index < z_NumRotations - 1; ++index)
    {
        if (animationTime < z_Rotations[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

int ZBone::GetScaleIndex(float animationTime)
{
    for (int index = 0; index < z_NumScalings - 1; ++index)
    {
        if (animationTime < z_Scales[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

float ZBone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}

glm::mat4 ZBone::InterpolatePosition(float animationTime)
{
    if (1 == z_NumPositions)
        return glm::translate(glm::mat4(1.0f), z_Positions[0].position);

    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(z_Positions[p0Index].timeStamp,
        z_Positions[p1Index].timeStamp, animationTime);
    glm::vec3 finalPosition = glm::mix(z_Positions[p0Index].position,
        z_Positions[p1Index].position, scaleFactor);
    return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 ZBone::InterpolateRotation(float animationTime)
{
    if (1 == z_NumRotations)
    {
        auto rotation = glm::normalize(z_Rotations[0].orientation);
        return glm::toMat4(rotation);
    }

    int p0Index = GetRotationIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(z_Rotations[p0Index].timeStamp,
        z_Rotations[p1Index].timeStamp, animationTime);
    glm::quat finalRotation = glm::slerp(z_Rotations[p0Index].orientation,
        z_Rotations[p1Index].orientation, scaleFactor);
    finalRotation = glm::normalize(finalRotation);
    return glm::toMat4(finalRotation);
}

glm::mat4 ZBone::InterpolateScaling(float animationTime)
{
    if (1 == z_NumScalings)
        return glm::scale(glm::mat4(1.0f), z_Scales[0].scale);

    int p0Index = GetScaleIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(z_Scales[p0Index].timeStamp,
        z_Scales[p1Index].timeStamp, animationTime);
    glm::vec3 finalScale = glm::mix(z_Scales[p0Index].scale, z_Scales[p1Index].scale
        , scaleFactor);
    return glm::scale(glm::mat4(1.0f), finalScale);
}
