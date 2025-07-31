#pragma once


#include "World/ZTransform.h"

class Rigidbody
{
public:
    Rigidbody(std::string_view modelId = "", const ZTransform& transform = {}, float mass = 1.0f);

    void Update(float dt);

    void ApplyForce(Vec3 force);
    void ApplyForce(Vec3 direction, float magnitude);

    void ApplyAcceleration(Vec3 acceleration);
    void ApplyAcceleration(Vec3 direction, float magnitude);

    void ApplyImpulse(Vec3 force, float dt);
    void ApplyImpulse(Vec3 direction, float magnitude, float dt);

    void TransferEnergy(float joules, Vec3 direction);

    void HandleCollision(const Rigidbody* inst, Vec3 norm);

    ZTransform& GetTransform() { return z_Transform; }

    Vec3 GetAcceleration() { return z_Acceleration; }

private:
    unsigned char z_State;

    float z_Mass;

    ZTransform z_Transform;
    Vec3 z_Velocity;
    Vec3 z_Acceleration;


    Mat4 z_Model;
    Mat3 z_NormalModel;

    std::string z_ModelId;
    std::string z_InstanceId;

    float z_LastCollision;
    std::string z_LastCollisionID;

    bool operator==(Rigidbody rb);
    bool operator==(std::string id);
};

