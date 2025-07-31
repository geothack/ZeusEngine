#include "Core\CoreLibrary.h"
#include "PhysicsBody2D.h"

PhysicsBody2D::PhysicsBody2D(PhysicsWorld2D& world, const BodyShape& body) : z_Body(body)
{
	z_BodyDef.type = z_Body.Type;
    z_BodyDef.position = b2Vec2(z_Body.X, z_Body.Y);
    z_BodyDef.fixedRotation = z_Body.FixedRotation;
    z_BodyDef.enableSleep = z_Body.CanSleep;
    z_BodyDef.gravityScale = z_Body.Gravity;
    z_BodyDef.isEnabled = z_Body.Enabled;
    //z_BodyDef.linearDamping = 0.0f;
    //z_BodyDef.angularDamping = 0.01f;
    z_BodyId = b2CreateBody(world.GetId(), &z_BodyDef);

    b2Polygon dynamicBox = b2MakeBox(z_Body.Width, z_Body.Height);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;

    b2CreatePolygonShape(z_BodyId, &shapeDef, &dynamicBox);
}

void PhysicsBody2D::Destroy()
{
    b2DestroyBody(z_BodyId);
}

void PhysicsBody2D::Sleep(bool set)
{
    b2Body_SetAwake(z_BodyId, set);
}
