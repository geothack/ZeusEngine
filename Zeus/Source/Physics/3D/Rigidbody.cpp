#include "Core/CoreLibrary.h"
#include "Rigidbody.h"

Rigidbody::Rigidbody(std::string_view modelId, const ZTransform& transform, float mass) : z_ModelId(modelId.data()), z_Transform(transform), z_Mass(mass), z_Velocity(0.0f), z_Acceleration(0.0f), z_State(0),
	z_LastCollision(0.05f), z_LastCollisionID("")
{
	Update(0.0f);
}

void Rigidbody::Update(float dt)
{
    z_Transform.SetPosition(z_Transform.GetPosition() += z_Velocity * dt + 0.5f * z_Acceleration * (dt * dt));
    z_Velocity += z_Acceleration * dt;

    glm::mat4 rotMat = glm::toMat4(glm::quat(z_Transform.GetRotation()));
    
    z_Model = glm::translate(glm::mat4(1.0f), z_Transform.GetPosition());
    z_Model = z_Model * rotMat; 
    z_Model = glm::scale(z_Model, z_Transform.GetScale());
    
    z_NormalModel = glm::transpose(glm::inverse(glm::mat3(z_Model)));
    
    z_LastCollision += dt;
}

void Rigidbody::ApplyForce(Vec3 force)
{
    z_Acceleration += force / z_Mass;
}

void Rigidbody::ApplyForce(Vec3 direction, float magnitude)
{
    ApplyForce(direction * magnitude);
}

void Rigidbody::ApplyAcceleration(Vec3 a)
{
    z_Acceleration += a;
}

void Rigidbody::ApplyAcceleration(Vec3 direction, float magnitude)
{
    ApplyAcceleration(direction * magnitude);
}

void Rigidbody::ApplyImpulse(Vec3 force, float dt)
{
    z_Velocity += force / z_Mass * dt;
}

void Rigidbody::ApplyImpulse(Vec3 direction, float magnitude, float dt) 
{
    ApplyImpulse(direction * magnitude, dt);
}

void Rigidbody::TransferEnergy(float joules, Vec3 direction)
{
    if (joules == 0) 
    {
        return;
    }

    glm::vec3 deltaV = sqrt(2 * abs(joules) / z_Mass) * direction;

    z_Velocity += joules > 0 ? deltaV : -deltaV;
}


void Rigidbody::HandleCollision(const Rigidbody* inst, Vec3 norm)
{
    if (z_LastCollision >= 0.05f || z_LastCollisionID != inst->z_InstanceId) 
    {
        z_Velocity = glm::reflect(z_Velocity, glm::normalize(norm)); 
        z_LastCollision = 0.0f; 
    }

    z_LastCollisionID = inst->z_InstanceId;
}
