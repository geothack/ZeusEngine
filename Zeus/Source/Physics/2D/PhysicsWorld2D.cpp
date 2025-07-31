#include "Core\CoreLibrary.h"
#include "PhysicsWorld2D.h"
#include "Physics/2D/PhysicsBody2D.h"
#include "World/ZTransform.h"

PhysicsWorld2D::PhysicsWorld2D()
{
    z_WorldDef.gravity = b2Vec2(0.0f, 10.0f);

    z_WorldId = b2CreateWorld(&z_WorldDef);
}

PhysicsWorld2D::~PhysicsWorld2D()
{
    b2DestroyWorld(z_WorldId);
}

void PhysicsWorld2D::Update(float timeStep,ZLevel& level)
{
    b2World_Step(z_WorldId, timeStep, 4);

    /*for (auto& entity : mActiveLevel->GetHandle().view<entt::entity>())
    {
        if (mActiveLevel->GetHandle().any_of<PhysicsBody2D>(entity))
        {
            b2Vec2 position = b2Body_GetPosition(mActiveLevel->GetHandle().get<PhysicsBody2D>(entity).GetBodyId());

            mActiveLevel->GetHandle().get<Transform>(entity).UpdatePosition(glm::vec2(position.x, position.y));
        }
    }*/
}
