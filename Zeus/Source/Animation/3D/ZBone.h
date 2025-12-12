#pragma once

struct KeyPosition
{
    glm::vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    glm::quat orientation;
    float timeStamp;
};

struct KeyScale
{
    glm::vec3 scale;
    float timeStamp;
};

class ZBone
{
public:

    ZBone(const std::string& name, int ID, const aiNodeAnim* channel);
        
    void Update(float animationTime);

    glm::mat4 GetLocalTransform() { return z_LocalTransform; }
    std::string GetBoneName() const { return z_Name; }
    int GetBoneID() { return z_ID; }

    int GetPositionIndex(float animationTime);

    int GetRotationIndex(float animationTime);

    int GetScaleIndex(float animationTime);

private:

    float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

    glm::mat4 InterpolatePosition(float animationTime);

    glm::mat4 InterpolateRotation(float animationTime);

    glm::mat4 InterpolateScaling(float animationTime);


private:
    std::vector<KeyPosition> z_Positions;
    std::vector<KeyRotation> z_Rotations;
    std::vector<KeyScale> z_Scales;
    int z_NumPositions;
    int z_NumRotations;
    int z_NumScalings;

    glm::mat4 z_LocalTransform;
    std::string z_Name;
    int z_ID;

};
