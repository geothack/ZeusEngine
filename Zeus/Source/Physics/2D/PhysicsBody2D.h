#pragma once

#include "Physics/2D/PhysicsWorld2D.h"

struct BodyShape
{
	float X = 0;
	float Y = 0;
	float Width = 50;
	float Height = 50;
	float Gravity = 1.0f;

	b2BodyType Type = b2_dynamicBody;
	bool FixedRotation = true;
	bool CanSleep = true;
	bool Enabled = true;
};

class PhysicsBody2D
{
public:
	PhysicsBody2D(PhysicsWorld2D& world, const BodyShape& body);

	void Destroy();

	void Sleep(bool set);

	inline b2BodyDef& GetBodyDef() { return z_BodyDef; }
	inline const b2BodyId& const GetBodyId() const { return z_BodyId; }
	inline const float GetWidth() const { return z_Body.Width; }
	inline const float GetHeight() const { return z_Body.Height; }

private:
	b2BodyDef z_BodyDef = b2DefaultBodyDef();
	b2BodyId z_BodyId;

	BodyShape z_Body;
	//PhysicsWorld2D& z_World;
};

