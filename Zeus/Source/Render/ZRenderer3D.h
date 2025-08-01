#pragma once

#include "Render/ZCamera.h"
#include "Render/ZSkybox.h"
#include "World/ZLevel.h"

class ZRenderer3D
{
public:
	ZRenderer3D();
	~ZRenderer3D();

	void Update(ZLevel& level, ZCamera& activeCamera, ZSkybox& skybox);
};

