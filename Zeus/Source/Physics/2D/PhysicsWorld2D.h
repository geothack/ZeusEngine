#pragma once

#include "World/ZLevel.h"

class PhysicsWorld2D
{
public:
	PhysicsWorld2D();
	~PhysicsWorld2D();

	void Update(float timeStep, ZLevel& level);

	inline b2WorldId& GetId() { return z_WorldId; }

private:
	b2WorldDef z_WorldDef = b2DefaultWorldDef();
	b2WorldId z_WorldId;
};

